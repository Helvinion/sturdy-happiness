#include <tiles.h>
#include <messages.h>
#include <sprites.h>
#include <manette.h>
#include <palette.h>
#include <avatar.h>
#include <musique.h>
#include <physique.h>
#include <niveau.h>
#include <ecran.h>
#include <liste_animations.h>

#define PPUCTRL (unsigned char*)0x2000
#define PPUMASK (unsigned char*)0x2001
#define PPUSTAT (unsigned char*)0x2002
#define PPUADDR (unsigned char*)0x2006
#define PPUDATA (unsigned char*)0x2007

#define FRAME_COUNT (unsigned char*)0x00

/*
static struct element_physique *elements[10];
static unsigned char nombre_elements;
*/

static struct element_physique *joueur;
static struct element_physique elements[10];

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

static void traiter_animations()
{
	static unsigned char compteur = 0;

	if (compteur++ == 8)
	{
		// Rustique. Animer tous les 8 frames.
		animer(joueur->dessin);
		compteur = 0;
	}
}

static void debut_boucle()
{
	update_manettes(); // 289 cycles
	tiles_update();    // 21 cycles
	sprites_begin();   // 23 cycles
	jouer_musique(); // 250 cycles en général, 2450 cycles aux changements de note
	ligne_chargee = 0;
}

static void fin_boucle()
{
	int i = 0;

	traiter_animations(); // 36 cycles quand rien à animer
//	while (i++ < nombre_elements)
	{
		// appliquer_physique(joueur); // 12948 cycles quand rien ne se passe !
		 afficher_personnage(joueur->dessin); // 8591 cycles
	}
	sprites_end(); // 70 cycles
	
	attendre_VBlank();
}

void initialiser()
{
	int i = 0;

	static struct avatar G_Jolivet = {40, 40, &G_Jolivet_pack, 0, 0};
	static struct element_physique G_Jolivet_phys = {&G_Jolivet, 40,50, 0,0, 0,0, 0};
	joueur = &G_Jolivet_phys;
	
	(*PPUCTRL) = (unsigned char)0x90;

    // changer les palettes pendant un vblank
    attendre_VBlank();

	changer_palette(4, get_palette(PALETTE_CURSEURS));
	changer_palette(5, get_palette(PALETTE_VISAGE_JOLIVET));
	changer_palette(6, get_palette(PALETTE_JOLIVET));
	changer_palette(7, get_palette(PALETTE_JOLIVET));

	// Activer le rendu de l'écran
    (*PPUMASK) = (unsigned char)0x18;

    tiles_init();

	changer_niveau(0);
	fixer_position_camera(0, 0);
	init_musique();
	attendre_VBlank();
}

void moteur_mode_jeu()
{
	// OK alors à partir d'ici, on a le droit de
	// n'utiliser que 28000 cycles CPU pour faire
	// tout ce qu'on a à faire. TOUT compte !	
	debut_boucle();
	
	if (bouton_presse_manette_1(BOUTON_DROITE))
	{
		bouger_camera_x(1);
		joueur->dessin->x++;
	}
	if (bouton_presse_manette_1(BOUTON_GAUCHE))
	{
		bouger_camera_x(-1);
		joueur->dessin->x--;
	}
	if (bouton_presse_manette_1(BOUTON_HAUT))
	{
		bouger_camera_y(-1);
		joueur->dessin->y--;
	}
	if (bouton_presse_manette_1(BOUTON_BAS))
	{
		bouger_camera_y(1);
		joueur->dessin->y++;
	}

	fin_boucle();
}
