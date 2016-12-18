#include <common.h>

#define TILE_UPDATE_BUFFER (struct tile_to_update**)0x12
#define TILE_UBDATE_SIZE (unsigned char*)0x14

#define UPDATE_SCREEN   (unsigned char*)0x03

struct tile_to_update
{
    unsigned short int ppu_addr;
    unsigned char      ppu_data;
};

static struct tile_to_update update_buffer_0[32]; // 32 éléments : On ne peux en gérer plus de 41 pendant un VBlank mais on la joue sécure
static char size_0;

void tiles_init()
{
    (*TILE_UPDATE_BUFFER) = update_buffer_0; // Indique à la procédure NMI où se trouve le buffer d'update
    (*TILE_UBDATE_SIZE) = 0;
    size_0 = 0;
}

void tiles_commit_changes()
{
    // Notifier la procédure NMI qu'il y a des updates à faire.
    // Pour cela, on charge le nombre d'updates dans NAME_UDP_LEN
    (*TILE_UBDATE_SIZE) = size_0;
	if (size_0 < 25)
		(*UPDATE_SCREEN) += 4; // Si on a plus de 25 éléments, la PPU ne pourra pas tout faire et on force la MaJ des tiles
	else
		(*UPDATE_SCREEN) = 4;
}

void tiles_add_change(unsigned char l, unsigned char c, unsigned char data)
{
	if (size_0 < 32)
	{
		update_buffer_0[size_0].ppu_addr = TO_PPU_ADDR(l, c);
		update_buffer_0[size_0].ppu_data = data;
		size_0++;
	}
}

void tiles_update()
{
    // Si NMI a lu les données, cette case mémoire contient un 0.
    // Donc on oublie exprès les données en question.
    if ((*TILE_UBDATE_SIZE) == 0)
        size_0 = 0;
}
