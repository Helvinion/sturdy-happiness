#include <common.h>

#define TILE_UPDATE_BUFFER (struct tile_to_update**)0x32
#define TILE_UPDATE_SIZE   (unsigned char*)0x34
#define TILE_GROUP         (struct tiles_goup**)0x36 
#define TILE_GROUP_SIZE    (unsigned char*)0x38

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

static const unsigned short int NAMETABLES[4] = {0x2000, 0x2400, 0x2800, 0x2C00};
static struct tile_to_update update_buffer[10]; // On interdit de modifier plus de 10 éléments en une frame
static struct tiles_group    group_updates[2];  // On interdit de modifier plus d'une ligne complète en une seule frame
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
}

void tiles_commit_groups()
{
	(*TILE_GROUP_SIZE) = size_groups;
}

void tiles_add_change(unsigned char nametable, unsigned char l, unsigned char c, unsigned char data)
{
	if (size < 32)
	{
		update_buffer[size].ppu_addr = TO_PPU_ADDR(NAMETABLES[nametable], l, c);
		update_buffer[size].ppu_data = data;
		size++;
	}
}

void tiles_add_group_vertical(unsigned char nametable, unsigned char l, unsigned char c, unsigned int step, const char* buffer)
{
	int i = 0;
	group_updates[size_groups].ppu_addr = TO_PPU_ADDR(NAMETABLES[nametable], l, c);
	group_updates[size_groups].options = 1; // Vertical (todo : a améliorer)
	
	while (i != 16)
	{
		group_updates[size_groups].tiles[i] = buffer[i * step];
		i++;
	}
	size_groups++;
}

void tiles_add_group_horizontal(unsigned char nametable, unsigned char l, unsigned char c, const char* buffer)
{
	unsigned int i = 0;
	group_updates[size_groups].ppu_addr = TO_PPU_ADDR(NAMETABLES[nametable], l, c);
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
