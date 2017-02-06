#include <tiles.h>
#include <messages.h>
#include <sprites.h>

char* message = "HELLO WORLD";

unsigned char palette[4] = { 0x17, 0x38, 0x38, 0x38 };

#define PPUCTRL (unsigned char*)0x2000
#define PPUMASK (unsigned char*)0x2001
#define PPUSTAT (unsigned char*)0x2002
#define PPUADDR (unsigned char*)0x2006
#define PPUDATA (unsigned char*)0x2007

void waitForVblank(void)
{
   for ( ; ; ) 
   {
      if ( (*PPUSTAT)&0x80 )
      {
         break;
      }
   }
   return;
}

void main(void)
{
   int i;
   unsigned char x_coord = 0;
   unsigned char y_coord = 0;
   unsigned char* pmsg = message;
   
   // enable vblank
   (*PPUCTRL) = (unsigned char)0x90;
   
   // change palette during vblank
   waitForVblank();
   
   // set monochrome palette
   (*PPUADDR) = (unsigned char)0x3F;
   (*PPUADDR) = (unsigned char)0x00;
   
   for ( i = 0; i < 8; i++ )
   {
      (*PPUDATA) = (*(palette+0));
      (*PPUDATA) = (*(palette+1));
      (*PPUDATA) = (*(palette+2)); 
      (*PPUDATA) = (*(palette+3));
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
   add_sprite(0, x_coord, y_coord, 0);
   
	while(1)
	{
	  waitForVblank();
  	  tiles_update();
	  
	  x_coord += 1;
	  y_coord += 2;
	  
	  move_sprite(0, x_coord, y_coord);
	  
	  messages_update();
	}
}
