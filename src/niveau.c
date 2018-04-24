#include <tiles.h>
#include <niveau.h>
#include <physique.h>
#include <hitbox.h>

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

static const niveau niveau_0 =
{
	0,
	74,
	30,
	0,
	0,
	"D                             "
	" +||||||||||||||||||||||||||+ "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                       -  - "
	" -                       -  - "
	" -                       -  - "
	" -                       +||+ "
	" -                       -  - "
	" -                       -  - "
	" -                       -  - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                    -     - "
	" -                    -     - "
	" -                    -     - "
	" -                    +|||||+ "
	" -                    -     - "
	" -                    -     - "
	" -                    -     - "
	" -                          - "
	" -               -          - "
	" -               -          - "
	" -               -          - "
	" -               +||||||||||+ "
	" -               -          - "
	" -               -          - "
	" -               -          - "
	" -           -              - "
	" -           -              - "
	" -           -              - "
	" -           +||||||||||||||+ "
	" -           -              - "
	" -           -              - "
	" -           -              - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" -                          - "
	" +||||||||||||||||||||||||||+ "
	"                             F"
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
	if (niveau_n == 0)
		niveau_courant = &niveau_0;
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

static const unsigned char *conversion_coordonnees_adresse(unsigned int x, unsigned int y)
{
	static const niveau *niveau_courant_sav = 0;
	static const char   *fin_buffer_sav = 0;
	static unsigned int x_sav;
	static unsigned int mul_sav; /* sauvegarde de la position x * la taille y */

	/* Les données du niveau le représentent tourné à 90 degrés
	   Il faut donc appliquer une formule différente de d'habitude
	   pour trouver où commencer à lire les données :
	   DEBUT + (TAILLE_X * TAILLE_Y) - TAILLE_Y - (TAILLE_Y * POSITION_X) + POSITION_Y */
	
	if (niveau_courant != niveau_courant_sav)
	{
		/* Optimisation : on garde une trace de la taille du niveau courant */
		niveau_courant_sav = niveau_courant;
		fin_buffer_sav = niveau_courant->addr + (niveau_courant->taille_y * niveau_courant->taille_x);
		x_sav = x;
	}
	
	/* Optimisation : si x changé de 1 par rapport à la dernière fois,
	   Pas besoin de refaire la multiplication */
	if (x == x_sav + 1)
		mul_sav += niveau_courant->taille_y;
	else if (x == x_sav - 1)
		mul_sav -= niveau_courant->taille_y;
	else if (x != x_sav)
		mul_sav = niveau_courant->taille_y * (x);

	x_sav = x;
	
	return (fin_buffer_sav - mul_sav + y);
}

void charger_ligne_verticale(unsigned char nametable, unsigned char colonne_ecran, unsigned int position_x, unsigned int position_y)
{
	static unsigned char colonne_sav = 0;
	static unsigned int x_sav = 0;
	static unsigned int y_sav = 0;
	
	if (colonne_sav == colonne_ecran && x_sav == position_x && y_sav == position_y)
		return;
	
	tiles_add_group_vertical(nametable, colonne_ecran, conversion_coordonnees_adresse(position_x, position_y));
	tiles_commit_groups();
	
	colonne_sav = colonne_ecran;
	x_sav = position_x;
	y_sav = position_y;
}

void charger_ligne_horizontale(unsigned char nametable, unsigned char ligne_ecran, unsigned int position_x, unsigned int position_y)
{
	static unsigned char ligne_sav = 0;
	static unsigned int x_sav = 0;
	static unsigned int y_sav = 0;

	if (ligne_sav == ligne_ecran && x_sav == position_x && y_sav == position_y)
		return;

	tiles_add_group_horizontal(nametable, ligne_ecran, niveau_courant->taille_y, conversion_coordonnees_adresse(position_x, position_y));
	tiles_commit_groups();

	ligne_sav = ligne_ecran;
	x_sav = position_x;
	y_sav = position_y;
}

int camera_dans_niveau(unsigned int x, unsigned int y)
{
	unsigned int x_est_bon = (x > 0 && x + 256 < niveau_courant->taille_x);
	unsigned int y_est_bon = (y > 0 && y + 240 < niveau_courant->taille_y);
	return (x_est_bon && y_est_bon);
}

unsigned char get_tile(signed int x, signed int y)
{
	unsigned int tile_x = (unsigned int)(x / 8 + niveau_courant->x0);
	unsigned int tile_y = (unsigned int)(y / 8 + niveau_courant->y0);

	return *conversion_coordonnees_adresse(tile_x, tile_y);
}

#if 0
signed int detecter_future_collision_bas(const struct element_physique *element, const struct hitline *ligne)
{
	/* Calcul du début et de la fin du trait de collision à tester */
	const signed int position_x_debut = element->coordonnee_x + element->vitesse_x + ligne->diff_x;
	const signed int position_x_fin = position_x_debut + ligne->taille;

	/* Calcul de la hauteur initiale et finale de ce trait */
	const signed int position_y_debut = element->coordonnee_y + ligne->diff_y;
	const signed int position_y_fin = position_y_debut + element->vitesse_y;
	
	/* Variables d'itération */
	signed int       position_y = position_y_debut;
	signed int       position_x = position_x_debut;
	unsigned char    tile;
	
	while (position_y < position_y_fin)
	{
		position_x = position_x_debut;
		while (position_x < position_x_fin)
		{
			tile = get_tile(position_x, position_y);
			
			/* Si une tile intraversable est détéctée, renvoyer le nombre de pixels autorisés à parcourir sans la toucher */
			if (tile == '-')
				return position_y_fin - position_y - 2; /* Pourquoi ce -2 (et pas -1), je ne sais pas */

			/* Incrémente position_x de ce qu'il faut pour atteindre la prochaine huitaine */
			position_x += (8 - (position_x % 8));
		}
		position_y+=8;
	}
	return element->vitesse_y;
}
#endif

signed int detecter_future_collision_bas(const struct element_physique *element, const struct hitbox *box)
{
	/* Calcul du début et de la fin du trait de collision à tester */
	const signed int position_x_debut = element->coordonnee_x + element->vitesse_x + box->diff_x;
	const signed int position_x_fin = position_x_debut + box->taille_x;

	const signed int position_y = element->coordonnee_y + (box->diff_y + box->taille_y) + element->vitesse_y;

	/* Variables d'itération */
	signed int       position_x = position_x_debut;
	unsigned char    tile;

	for (position_x = position_x_debut; position_x < position_x_fin; position_x += 8)
	{
		tile = get_tile(position_x, position_y);
		if (tile == '-')
		{
			return (element->vitesse_y - position_y % 8 - 1);
		}
	}

	return element->vitesse_y;
}
