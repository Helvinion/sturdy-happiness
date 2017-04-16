#include <tiles.h>
#include <messages.h>
#include <sprites.h>
#include <manette.h>
#include <palette.h>
#include <avatar.h>
#include <musique.h>

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
   unsigned char x_coord = 15;
   unsigned char y_coord = 15;
   unsigned char* pmsg = message;

   struct CanalCarre canal_carre_1;
   
   canal_carre_1.reg_1 = 0x4f;
   canal_carre_1.reg_2 = 0x9a;
   canal_carre_1.reg_3 = 0xeb;
   canal_carre_1.reg_4 = 0x80;

   jouer_musique();
   
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
   
   afficher_personnage_2(&G_Jolivet);

   while(1)
	{
		waitForVblank();
		
		update_manettes();
		tiles_update();
		remove_all();
		
	    G_Jolivet.x = x_coord;
		G_Jolivet.y = y_coord;
		
		afficher_personnage_2(&G_Jolivet);

		
		if (bouton_haut(1))
			y_coord--;
		if (bouton_bas(1))
			y_coord++;
		if (bouton_droite(1))
			x_coord++;
		if (bouton_gauche(1))
			x_coord--;
	  
		if (bouton_b(1))
		   jouer_son_carre_1(&canal_carre_1);
		if (bouton_a(1))
		   jouer_son_carre_1(&canal_carre_1);;

		if (triche_konami(1))
		{
			x_coord = 15;
			y_coord = 15;
			unhide_sprite(0);
		}
		
		messages_update();
		
	}
}
