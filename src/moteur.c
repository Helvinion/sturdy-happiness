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
static struct element_physique G_Jolivet_phys = {&G_Jolivet, 15,150, 0,0, 0,0, 0};


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

static void debut_boucle()
{
	update_manettes();
	tiles_update();
	sprites_begin();	
}

static void fin_boucle()
{
	int i = 0;
	
//	while (i++ < nombre_elements)
	{
		appliquer_physique(&G_Jolivet_phys);
		afficher_personnage(G_Jolivet_phys.dessin);
	}
	sprites_end();	
}

void initialiser()
{
	int i = 0;
		
	(*PPUCTRL) = (unsigned char)0x90;
   
    // change palette during vblank
    attendre_VBlank();

    for (i = 0; i < 8; i++)
    {
 	   changer_palette(i, get_palette(PALETTE_BASE));
    }
    
    // Activer le rendu de l'écran
    (*PPUMASK) = (unsigned char)0x18; 
   
    tiles_init();
	
	attendre_VBlank();
}

void moteur_mode_jeu()
{
	static unsigned char i = 0;
	debut_boucle();
	
	if (bouton_presse_manette_1(BOUTON_DROITE))
	{
		i++;
		changer_animation(&G_Jolivet, 1);
		G_Jolivet_phys.vitesse_x = 2;
	}
	else if (bouton_presse_manette_1(BOUTON_GAUCHE))
	{
		i++;
		changer_animation(&G_Jolivet, 1);
		G_Jolivet_phys.vitesse_x = -2;
	}
	else
	{
		i = 0;
		changer_animation(&G_Jolivet, 0);
		G_Jolivet_phys.vitesse_x = 0;
	}
	
	if (nouveau_bouton_presse_manette_1(BOUTON_A))
	{
		saut(&G_Jolivet_phys);
	}
	
	if (i == 5)
	{
		animer(&G_Jolivet);
		i = 0;
	}
	
	fin_boucle();
}