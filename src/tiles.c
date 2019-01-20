#include <common.h>
#include <utile.h>
#include <tiles.h>
#include <zeropage.h>

#define TILE_UPDATE_BUFFER 0x32
#define TILE_UPDATE_SIZE   0x34
#define TILE_GROUP         0x36
#define TILE_GROUP_SIZE    0x38

struct tile_to_update
{
    unsigned short int ppu_addr;
    unsigned char      ppu_data;
};

struct tiles_group
{
	unsigned short int ppu_addr;
	unsigned char      options;
	unsigned char      *tiles;
};

const unsigned short int NAMETABLES[4] = {0x2000, 0x2400, 0x2800, 0x2C00};
static struct tile_to_update update_buffer[10]; // On interdit de modifier plus de 10 éléments en une frame
static struct tiles_group    group_updates;  // On interdit de modifier plus d'une ligne complète en une seule frame
static unsigned char size;


void tiles_init()
{
	ecrire_zeropage_addr(TILE_UPDATE_BUFFER, (unsigned char*)update_buffer);
	ecrire_zeropage_addr(TILE_GROUP, (unsigned char*)(&group_updates));
	group_updates.tiles = (unsigned char*)(TILES_GROUP_BUF);
	ecrire_zeropage(TILE_UPDATE_SIZE, 0);
	ecrire_zeropage(TILE_GROUP_SIZE, 0);
    size                  = 0;
}

void tiles_commit_changes()
{
    // Notifier la procédure NMI qu'il y a des updates à faire.
    // Pour cela, on charge le nombre d'updates dans NAME_UDP_LEN
	ecrire_zeropage(TILE_UPDATE_SIZE, size);
}

void tiles_commit_groups()
{
	ecrire_zeropage(TILE_GROUP_SIZE, 1);
}

void tiles_set_change(unsigned short addr, unsigned char data)
{
	if (size < 10)
	{
		update_buffer[size].ppu_addr = addr;
		update_buffer[size].ppu_data = data;
		size++;
	}
}

void tiles_add_change(unsigned char nametable, unsigned char l, unsigned char c, unsigned char data)
{
	tiles_set_change(TO_PPU_ADDR(NAMETABLES[nametable], l, c), data);
}

void tiles_add_group_vertical(unsigned char nametable, unsigned char c, const char *source)
{
	unsigned int i = 0;
	char*        dst = group_updates.tiles;

	while (i != 32)
	{
		*dst = *source;
		dst++;
		source++;
		i++;
	}

	tiles_set_group_vertical(nametable, 0, c);
}

void tiles_add_group_horizontal(unsigned char nametable, unsigned char l, unsigned int step, const char* source)
{
	unsigned int i = 0;
	char*        dst = group_updates.tiles;

	while (i != 32)
	{
		*dst = *source;
		dst++;
		source -= step;
		i++;
	}
	
	tiles_set_group_horizontal(nametable, l, 0);
}

void tiles_update()
{
    // Si NMI a lu les données, cette case mémoire contient un 0.
    // Donc on oublie exprès les données en question.
    if ((*((unsigned char*)TILE_UPDATE_SIZE)) == 0)
        size = 0;
	//size_groups = (*TILE_GROUP_SIZE);
}

unsigned char *tiles_get_buffer()
{
	return group_updates.tiles;
}

void tiles_set_group_vertical(unsigned char nametable, unsigned char l, unsigned char c)
{
	group_updates.ppu_addr = TO_PPU_ADDR(NAMETABLES[nametable], l, c);
	group_updates.options = 1; // Vertical (todo : a améliorer)
}

void tiles_set_group_horizontal(unsigned char nametable, unsigned char l, unsigned char c)
{
	group_updates.ppu_addr = TO_PPU_ADDR(NAMETABLES[nametable], l, c);
	group_updates.options = 0; // Horizontal (todo : a améliorer)
}
