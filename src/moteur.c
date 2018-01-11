#include <tiles.h>
#include <messages.h>
#include <sprites.h>
#include <manette.h>
#include <palette.h>
#include <avatar.h>
#include <musique.h>
#include <physique.h>

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

void attendre_VBlank(void)
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
	
	if (compteur++ == 32)
	{
		// Rustique. Animer tous les 8 frames.
		animer(joueur->dessin);
		compteur = 0;
	}
}

static void debut_boucle()
{
	update_manettes();
	tiles_update();
	sprites_begin();	
}

static void fin_boucle()
{
	int i = 0;

	traiter_animations();
//	while (i++ < nombre_elements)
	{
		appliquer_physique(joueur);
		//afficher_personnage(joueur->dessin);
	}
	sprites_end();
	attendre_VBlank();
}

void initialiser()
{
	int i = 0;
	static struct element_physique G_Jolivet_phys = {&G_Jolivet, 15,150, 0,0, 0,0, 0};

	(*PPUCTRL) = (unsigned char)0x90;
   
    // changer les palettes pendant un vblank
    attendre_VBlank();

    for (i = 0; i < 4; i++)
    {
 	   changer_palette(i, get_palette(PALETTE_CURSEURS));
    }

	changer_palette(4, get_palette(PALETTE_CURSEURS));
	changer_palette(5, get_palette(PALETTE_VISAGE_JOLIVET));
	changer_palette(6, get_palette(PALETTE_JOLIVET));
	changer_palette(7, get_palette(PALETTE_JOLIVET));
    
	// Activer le rendu de l'écran
    (*PPUMASK) = (unsigned char)0x18; 
   
    tiles_init();
	
	joueur = &G_Jolivet_phys;
	
	attendre_VBlank();
}

void moteur_mode_jeu()
{
	debut_boucle();
	
	tiles_add_change(5, 5, 'Q');
	tiles_commit_changes();
	/*
	if (bouton_presse_manette_1(BOUTON_DROITE))
	{
		changer_animation(joueur->dessin, 1);
		joueur->vitesse_x = 1;
	}
	else if (bouton_presse_manette_1(BOUTON_GAUCHE))
	{
		changer_animation(joueur->dessin, 1);
		joueur->vitesse_x = -1;
	}
	else
	{
		changer_animation(joueur->dessin, 0);
		joueur->vitesse_x = 0;
	}
	
	if (nouveau_bouton_presse_manette_1(BOUTON_A))
	{
		saut(joueur);
	}
*/
	fin_boucle();
}