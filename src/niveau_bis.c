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
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

static const niveau niveau_0 = 
{
	0,
	16,
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
	return 0;
}

unsigned int taille_y_niveau_courant()
{
	return 0;
}

void changer_niveau(unsigned char niveau_n)
{
	return;
}

void charger_niveau(unsigned char nametable, unsigned int position_x, unsigned int position_y)
{
	unsigned char ligne = 0;
	unsigned char colonne = 0;
	const unsigned char* addr = niveau_0.addr;
	unsigned char* tile = 0;
		
	while (ligne < 15)
	{
		colonne = 0;
		while (colonne < 16)
		{
			tiles_add_change(nametable, ligne * 2,     colonne * 2,     GET_TILE(*addr)[0]);
			tiles_add_change(nametable, ligne * 2,     colonne * 2 + 1, GET_TILE(*addr)[1]);
			tiles_add_change(nametable, ligne * 2 + 1, colonne * 2,     GET_TILE(*addr)[2]);
			tiles_add_change(nametable, ligne * 2 + 1, colonne * 2 + 1, GET_TILE(*addr)[3]);
			
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
	}
	
	return;
}

void charger_ligne_verticale(unsigned char nametable, unsigned char c, unsigned int position_x, unsigned int position_y)
{
	return;
}

void charger_ligne_horizontale(unsigned char nametable, unsigned char l, unsigned int position_x, unsigned int position_y)
{
	return;
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
