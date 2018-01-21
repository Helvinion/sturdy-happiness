#include <tiles.h>
#include <niveau.h>

#define PPU_CTRL_VAR  (unsigned char*)(0x30) // Nametable pour le scrolling (aussi géré en VBlank)
#define PPUSTAT (unsigned char*)0x2002


struct niveau
{
	const unsigned int   taille_x;
	const unsigned int   taille_y;
	const unsigned char* addr; 
};

typedef struct niveau niveau;

static const niveau niveau_1 =
{
	74,
	32,
	"                                                                          "
	" +----------------------------------------------------------------------+ "
	" |                                                                      | "
	" |                                                                      | "
	" |                                                                      | "
	" |                                                                      | "
	" |                                                                      | "
	" |                                                                      | "
	" |                                                                      | "
	" |                                                                      | "
	" |                                                                      | "
	" |                                                                      | "
	" |                                                                      | "
	" |                                                                      | "
	" |                                                                      | "
	" |                                            ---+---                   | "
	" |                                               |                      | "
	" |                                               |                      | "
	" |                                               |                      | "
	" |                                     ---+---   |                      | "
	" |                                        |      |                      | "
	" |                                        |      |                      | "
	" |                                        |      |                      | "
	" |                                        |      |                      | "
	" |                             ---+---    |      |                      | "
	" |                                |       |      |                      | "
	" |                                |       |      |                      | "
	" |                   ---+----     |       |      |                      | "
	" |                      |         |       |      |                      | "
	" |                      |         |       |      |                      | "
	" +----------------------+---------+-------+------+----------------------+ "
	"                                                                          "
};

static const niveau *niveau_courant;

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
	return niveau_courant->taille_x;
}

unsigned int taille_y_niveau_courant()
{
	return niveau_courant->taille_y;
}

void changer_niveau(unsigned char niveau_n)
{
	if (niveau_n == 1)
		niveau_courant = &niveau_1;
}

// Pour charger un niveau :
// On lit les octets du niveau
// On les place dans la nametable indiquée.
// On switch sur cete nametable
// N.B. : Cette fonction garde le controle du programme tant que la nametable n'a pas été remplie 
// En principe, cela dure 32 frames.
void charger_niveau(unsigned char nametable, unsigned int position_x, unsigned int position_y)
{
	unsigned int ligne;
	
	for (ligne = 0; ligne < 30; ligne++)
	{
		// Charger la ligne du niveau située en (position_x, position_y + ligne sur l'écran à la ligne l
		charger_ligne_horizontale(nametable, ligne, position_x, position_y + ligne);	

		attendre_VBlank();
		tiles_update();
	}
}

void charger_ligne_verticale(unsigned char nametable, unsigned char c, unsigned int position_x, unsigned int position_y)
{
	tiles_add_group_vertical(nametable, 0,  c, niveau_courant->taille_x, niveau_courant->addr + (position_y        * niveau_courant->taille_x + position_x));
	tiles_add_group_vertical(nametable, 16, c, niveau_courant->taille_x, niveau_courant->addr + ((position_y + 16) * niveau_courant->taille_x + position_x));
	tiles_commit_groups();
}

void charger_ligne_horizontale(unsigned char nametable, unsigned char l, unsigned int position_x, unsigned int position_y)
{
	
	tiles_add_group_horizontal(nametable, l, 0,  niveau_courant->addr + (position_y * niveau_courant->taille_x + position_x));
	tiles_add_group_horizontal(nametable, l, 16, niveau_courant->addr + (position_y * niveau_courant->taille_x + position_x + 16));
	tiles_commit_groups();

}

int camera_dans_niveau(unsigned int x, unsigned int y)
{
	unsigned int x_est_bon = (x > 0 && x + 256 < niveau_courant->taille_x);
	unsigned int y_est_bon = (y > 0 && y + 240 < niveau_courant->taille_y);
	return (x_est_bon && y_est_bon);
}
