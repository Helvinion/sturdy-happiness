#include "niveau.h"
#include "tileset.h"
#include "tiles.h"

#define PPU_CTRL_VAR  (unsigned char*)(0x30) // Nametable pour le scrolling (aussi géré en VBlank)
#define PPUSTAT (unsigned char*)0x2002

struct niveau
{
	const unsigned char  numero;
	const unsigned int   taille_x;
	const unsigned int   taille_y;
	const unsigned int   x0;
	const unsigned int   y0;
	const unsigned char* addr;
};
typedef struct niveau niveau;

static const unsigned char niveau_0_tiles[] = 
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 10,1,11, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 3, 9, 6, 9, 6, 9, 6, 9, 6, 9, 6, 9, 6, 7, 2, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0, 0, 0, 0, 0,
	0, 0, 0, 3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0, 0, 0, 0,
	0, 0, 3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0, 0, 0,
	0, 3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0, 0,
	3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
};

static const niveau niveau_0 = 
{
	0,
	32,
	16,
	0,
	0,
	niveau_0_tiles
};

static void attendre_VBlank(void)
{
   for ( ; ; )
   {
      if ((*PPUSTAT) & 0x80)
      {
         break;
      }
   }
   return;
}

unsigned int taille_x_niveau_courant()
{
	return niveau_0.taille_x * 2;
}

unsigned int taille_y_niveau_courant()
{
	return niveau_0.taille_y * 2;
}

void changer_niveau(unsigned char niveau_n)
{
	return;
}

void charger_brique(unsigned char nametable, unsigned char ligne, unsigned char colonne, unsigned char brique)
{
	tiles_add_change(nametable, ligne * 2,     colonne * 2,     GET_TILE(brique)[0]);
	tiles_add_change(nametable, ligne * 2,     colonne * 2 + 1, GET_TILE(brique)[1]);
	tiles_add_change(nametable, ligne * 2 + 1, colonne * 2,     GET_TILE(brique)[2]);
	tiles_add_change(nametable, ligne * 2 + 1, colonne * 2 + 1, GET_TILE(brique)[3]);
}

void charger_niveau(unsigned char nametable, unsigned int position_x, unsigned int position_y)
{
	unsigned char ligne = 0;
	unsigned char colonne = 0;
	const unsigned char* addr = niveau_0.addr;
	unsigned char* tile = 0;
		
	while (ligne < 16)
	{
		colonne = 0;
		while (colonne < 16)
		{
			charger_brique(nametable, ligne, colonne, *addr);
			
			if (colonne % 2 == 1)
			{
				tiles_commit_changes();
				attendre_VBlank();
				tiles_update();
			}
			addr++;
			colonne++;
		}
		ligne++;
		addr = addr - 16 + niveau_0.taille_x;
	}
	
	return;
}

void charger_ligne_verticale(unsigned char nametable, unsigned char c, unsigned int position_x, unsigned int position_y)
{
	unsigned char *buffer = tiles_get_buffer();
	unsigned char i = 0;
	const unsigned char* addr = niveau_0.addr;
	unsigned char brique;
	
	addr += (position_y / 2) * niveau_0.taille_x + (position_x / 2);

	while (i < 16)
	{
		brique = *addr;
		
		*buffer = GET_TILE(brique)[0 + position_x % 2];
		buffer++;
		*buffer = GET_TILE(brique)[2 + position_x % 2];
		buffer++;
		
		addr += niveau_0.taille_x;
		i++;
	}
	
	tiles_set_group_vertical(nametable, c);
	tiles_commit_groups();
}

void charger_ligne_horizontale(unsigned char nametable, unsigned char l, unsigned int position_x, unsigned int position_y)
{
	unsigned char *buffer = tiles_get_buffer();
	unsigned char i = 0;
	const unsigned char* addr = niveau_0.addr;
	unsigned char brique;
	
	addr += (position_y / 2) * niveau_0.taille_x + (position_x / 2);

	while (i < 16)
	{
		brique = *addr;
		
		*buffer = GET_TILE(brique)[0 + position_x % 2];
		buffer++;
		*buffer = GET_TILE(brique)[1 + position_x % 2];
		buffer++;
		
		addr++;
		i++;
	}
	
	tiles_set_group_horizontal(nametable, l);
	tiles_commit_groups();
}

int camera_dans_niveau(unsigned int x, unsigned int y)
{
	return 0;
}

signed int detecter_future_collision_bas(const struct element_physique *element, const struct hitbox *ligne)
{
	return 0;
}

signed int detecter_future_collision_haut(const struct element_physique *element, const struct hitbox *ligne)
{	
	return 0;
}

signed int detecter_future_collision_gauche(const struct element_physique *element, const struct hitbox *ligne)
{
	return 0;
}

signed int detecter_future_collision_droite(const struct element_physique *element, const struct hitbox *ligne)
{
	return 0;
}
