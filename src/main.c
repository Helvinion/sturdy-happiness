#include <tiles.h>
#include <messages.h>
#include <sprites.h>
#include <manette.h>
#include <palette.h>
#include <avatar.h>

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

   struct partie_personnage G_Jolivet_debout_curseur = {0, -11, 0x00};
   struct partie_personnage G_Jolivet_debout_tete =    {0, 0,   0x01};
   struct partie_personnage G_Jolivet_debout_tronc =   {0, 8,   0x11};
   struct partie_personnage G_Jolivet_debout_bassin =  {0, 16,  0x21};
   struct partie_personnage G_Jolivet_debout_pieds =   {0, 24,  0x31};
   struct partie_personnage G_Jolivet_debout_tab[5];
   struct personnage_graphique G_Jolivet_debout;
   struct personnage_graphique G_Jolivet_anim_tab[1];
   struct animation G_Jolivet_anim;
   struct avatar G_Jolivet;
   
   G_Jolivet_debout_tab[0] = G_Jolivet_debout_tete;
   G_Jolivet_debout_tab[1] = G_Jolivet_debout_tronc;
   G_Jolivet_debout_tab[2] = G_Jolivet_debout_bassin;
   G_Jolivet_debout_tab[3] = G_Jolivet_debout_pieds;
   G_Jolivet_debout_tab[4] = G_Jolivet_debout_curseur;

   
   G_Jolivet_debout.parties = G_Jolivet_debout_tab;
   G_Jolivet_debout.taille_parties = 5;
   
   G_Jolivet_anim_tab[0] = G_Jolivet_debout;
   
   G_Jolivet_anim.anim = G_Jolivet_anim_tab;
   G_Jolivet_anim.taille_anim = 1;

   G_Jolivet.x = 100;
   G_Jolivet.y = 100;
   G_Jolivet.anim = G_Jolivet_anim;
   G_Jolivet.etape_anim = 0;
      
   // enable vblank
   (*PPUCTRL) = (unsigned char)0x90;
   
   // change palette during vblank
   waitForVblank();
/*   
   // set monochrome palette
   (*PPUADDR) = (unsigned char)0x3F;
   (*PPUADDR) = (unsigned char)0x00;
  */ 
   for (i = 0; i < 8; i++)
   {
	   changer_palette(i, get_palette(PALETTE_BASE));
   }
   
   // write message
   (*PPUADDR) = (unsigned char)0x20;
   (*PPUADDR) = (unsigned char)0x42;
   
   while ( *pmsg )
   {
      (*PPUDATA) = (*pmsg);
      pmsg++;
   }
   
   // turn on rendering
   (*PPUMASK) = (unsigned char)0x18; 
   
   tiles_init();
   /*
   tiles_add_change(10, 10, '0');
   tiles_add_change(9, 9, 0x10);
   tiles_add_change(9, 11, 0x11);
   tiles_add_change(11, 9, 0x12);
   tiles_add_change(11, 11, 0x13);
   tiles_add_change(10, 11, 0x15);
   tiles_add_change(11, 10, 0x14);
   tiles_add_change(10, 9, 0x15);
   tiles_add_change(9, 10, 0x14);
   //tiles_commit_changes();
   
   //tiles_add_group_vertical(11, 10, "uper ca marche !");
   //tiles_add_group_horizontal(10, 10, "Salut ca va ????");
   //tiles_commit_groups();
   */
   //messages_afficher(ID_PER_DIDACTICIEL, ID_MSG_DIDACTICIEL_A_B, 2, 10);
   add_sprite(0, x_coord, y_coord, SPRITES_FLAGS_COLORS_00);
   
   afficher_personnage(G_Jolivet.x, G_Jolivet.y, G_Jolivet.anim.anim);
   
	while(1)
	{
		waitForVblank();
		update_manettes();
		tiles_update();
		remove_all();

		
		
	   //add_sprite(0, x_coord, y_coord, SPRITES_FLAGS_COLORS_00);
	    G_Jolivet.x = x_coord;
		G_Jolivet.y = y_coord;
		
		afficher_personnage(G_Jolivet.x, G_Jolivet.y, G_Jolivet.anim.anim);

		
		if (bouton_haut(1))
			y_coord--;
		if (bouton_bas(1))
			y_coord++;
		if (bouton_droite(1))
			x_coord++;
		if (bouton_gauche(1))
			x_coord--;
	  
		if (bouton_b(1))
			hide_sprite(0);
		if (bouton_a(1))
			unhide_sprite(0);

		if (triche_konami(1))
		{
			x_coord = 15;
			y_coord = 15;
			unhide_sprite(0);
		}
	
		messages_update();
	}
}
