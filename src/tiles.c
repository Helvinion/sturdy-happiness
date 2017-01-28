#include <common.h>

#define TILE_UPDATE_BUFFER (struct tile_to_update**)0x12
#define TILE_UPDATE_SIZE   (unsigned char*)0x14
#define TILE_GROUP         (struct tiles_goup**)0x16 
#define TILE_GROUP_SIZE    (unsigned char*)0x18

#define UPDATE_SCREEN   (unsigned char*)0x03

struct tile_to_update
{
    unsigned short int ppu_addr;
    unsigned char      ppu_data;
};

struct tiles_group
{
	unsigned short int ppu_addr;
	unsigned char      options;
	unsigned char      tiles[16];
};

static struct tile_to_update update_buffer[32]; // 32 éléments : On ne peux en gérer plus de 41 pendant un VBlank mais on la joue sécure
static struct tiles_group    group_updates[4];
static unsigned char size_groups;
static unsigned char size;

void tiles_init()
{
    (*TILE_UPDATE_BUFFER) = (struct tile_to_update*)update_buffer; // Indique à la procédure NMI où se trouve le buffer d'update
    (*TILE_GROUP)         = (struct tiles_goup*)group_updates;
	(*TILE_UPDATE_SIZE)   = 0;
	(*TILE_GROUP_SIZE)    = 0;
    size                  = 0;
	size_groups           = 0;
}

void tiles_commit_changes()
{
    // Notifier la procédure NMI qu'il y a des updates à faire.
    // Pour cela, on charge le nombre d'updates dans NAME_UDP_LEN
    (*TILE_UPDATE_SIZE) = size;

	if (size < 25)
		(*UPDATE_SCREEN) += 4; // Si on a plus de 25 éléments, la PPU ne pourra pas tout faire et on force la MaJ des tiles
	else
		(*UPDATE_SCREEN) = 4;
}

void tiles_commit_groups()
{
	(*TILE_GROUP_SIZE) = size_groups;
	(*UPDATE_SCREEN) += 8;
}

void tiles_add_change(unsigned char l, unsigned char c, unsigned char data)
{
	if (size < 32)
	{
		update_buffer[size].ppu_addr = TO_PPU_ADDR(l, c);
		update_buffer[size].ppu_data = data;
		size++;
	}
}

void tiles_add_group_vertical(unsigned char l, unsigned char c, const char* buffer)
{
	int i = 0;
	group_updates[size_groups].ppu_addr = TO_PPU_ADDR(l, c);
	group_updates[size_groups].options = 1; // Vertical (todo : a améliorer)
	
	while (i != 16)
	{
		group_updates[size_groups].tiles[i] = buffer[i];
		i++;
	}
	size_groups++;
}

void tiles_add_group_horizontal(unsigned char l, unsigned char c, const char* buffer)
{
	int i = 0;
	group_updates[size_groups].ppu_addr = TO_PPU_ADDR(l, c);
	group_updates[size_groups].options = 0; // Horizontal (todo : a améliorer)
	
	while (i != 16)
	{
		group_updates[size_groups].tiles[i] = buffer[i];
		i++;
	}
	size_groups++;
}

void tiles_update()
{
    // Si NMI a lu les données, cette case mémoire contient un 0.
    // Donc on oublie exprès les données en question.
    if ((*TILE_UPDATE_SIZE) == 0)
        size = 0;
	size_groups = (*TILE_GROUP_SIZE);
}
