#include <tiles.h>
#include <messages.h>
#include <sprites.h>
#include <manette.h>
#include <palette.h>
#include <avatar.h>
#include <musique.h>
#include <physique.h>

char* message = "HELLO WORLD";

#define PPUCTRL (unsigned char*)0x2000
#define PPUMASK (unsigned char*)0x2001
#define PPUSTAT (unsigned char*)0x2002
#define PPUADDR (unsigned char*)0x2006
#define PPUDATA (unsigned char*)0x2007

#define FRAME_COUNT (unsigned char*)0x00

void waitForVblank(void)
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

void main(void)
{
    int i;
    unsigned char* pmsg = message;
	struct element_physique G_Jolivet_phys = {&G_Jolivet, 15,150, 0,0, 0,0, 0};
	

    //jouer_musique();
   
    // enable vblank
    (*PPUCTRL) = (unsigned char)0x90;
   
    // change palette during vblank
    waitForVblank();

    for (i = 0; i < 8; i++)
    {
 	   changer_palette(i, get_palette(PALETTE_BASE));
    }
    
    // turn on rendering
    (*PPUMASK) = (unsigned char)0x18; 
   
    tiles_init();
   
    tiles_add_change(10, 10, '0');
    tiles_add_change(9, 9, 0x10);
    tiles_add_change(9, 11, 0x11);
    tiles_add_change(11, 9, 0x12);
    tiles_add_change(11, 11, 0x13);
    tiles_add_change(10, 11, 0x15);
    tiles_add_change(11, 10, 0x14);
    tiles_add_change(10, 9, 0x15);
    tiles_add_change(9, 10, 0x14);
    tiles_commit_changes();
   
   
    tiles_add_group_vertical(11, 10, "uper ca marche !");
    tiles_add_group_horizontal(10, 10, "Salut ca va ????");
    tiles_commit_groups();
      
    messages_afficher(ID_PER_DIDACTICIEL, ID_MSG_DIDACTICIEL_A_B, 2, 10);
	changer_animation(&G_Jolivet, 1);
	i = 0;
   
    while(1)
	{
		waitForVblank();
		
		update_manettes();
		tiles_update();
		sprites_begin();
//		remove_all();
		
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
		appliquer_physique(&G_Jolivet_phys);
		afficher_personnage(&G_Jolivet);
		
		sprites_end();
		// messages_update();	
	}
}
