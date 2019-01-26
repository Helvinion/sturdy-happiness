#include "niveau.h"
#include "tileset.h"
#include "tiles.h"
#include "palette.h"
#include "zeropage.h"

#define PPU_CTRL_VAR  (unsigned char*)(0x30) // Nametable pour le scrolling (aussi géré en VBlank)
#define PPUSTAT (unsigned char*)0x2002

struct niveau
{
	const unsigned char  numero;
	const unsigned char  taille_x;
	const unsigned char  taille_y;
	const unsigned int   x0;
	const unsigned int   y0;
	const unsigned char *addr;
	const unsigned char *palettes;
	const unsigned char *palette_map;
};
typedef struct niveau niveau;

static const unsigned char niveau_0_tiles[] = 
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 10,1,11, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 3, 9, 6, 9, 6, 9, 6, 9, 6, 9, 6, 9, 6, 7, 2, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0, 0, 0, 0, 0,
	0, 0, 0, 3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0, 0, 0, 0,
	0, 0, 3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0, 0, 0,
	0, 3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0, 0,
	3, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4, 0,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 4,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

static const unsigned char niveau_0_palettes[] = 
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char niveau_0_palettes_list[4] = {PALETTE_NIVEAU_0, PALETTE_NIVEAU_0, PALETTE_NIVEAU_0, PALETTE_NIVEAU_0};

static const niveau niveau_0 = 
{
	0,
	32,
	18,
	0,
	0,
	niveau_0_tiles,
	niveau_0_palettes_list,
	niveau_0_palettes,
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
	return niveau_0.taille_x * 2;
}

unsigned int taille_y_niveau_courant()
{
	return niveau_0.taille_y * 2;
}

void changer_niveau(unsigned char niveau_n)
{
	return;
}

void charger_brique(unsigned char nametable, unsigned char ligne, unsigned char colonne, unsigned char brique)
{
	tiles_add_change(nametable, ligne * 2,     colonne * 2,     GET_TILE(brique)[0]);
	tiles_add_change(nametable, ligne * 2,     colonne * 2 + 1, GET_TILE(brique)[1]);
	tiles_add_change(nametable, ligne * 2 + 1, colonne * 2,     GET_TILE(brique)[2]);
	tiles_add_change(nametable, ligne * 2 + 1, colonne * 2 + 1, GET_TILE(brique)[3]);
}

void charger_niveau(unsigned char nametable, unsigned int position_x, unsigned int position_y)
{
	unsigned char ligne = 0;
	unsigned char colonne = 0;
	const unsigned char* addr = niveau_0.addr;
	const unsigned char* palette = niveau_0.palette_map;

    changer_palette(0, get_palette(niveau_0.palettes[0]));
 	changer_palette(1, get_palette(niveau_0.palettes[1]));
 	changer_palette(2, get_palette(niveau_0.palettes[2]));
 	changer_palette(3, get_palette(niveau_0.palettes[3]));

	while (ligne < 15)
	{
		colonne = 0;
		while (colonne < 16)
		{
			charger_brique(nametable, ligne, colonne, *addr);
			charger_palette(nametable, ligne / 2, colonne / 2, *palette);
			
			addr++;
			colonne++;

			// Si on était sur une colonne impaire on
			// commite les changements effectués
			if (colonne % 2 == 0) // 2 4 6 8 10 12 14
			{
				tiles_commit_changes();
				attendre_VBlank();
				tiles_update();
				palette++;
			}
		}
		
		palette -= 8;
		// Passer à la ligne suivante
		ligne++;
		addr = addr - 16 + niveau_0.taille_x;
		if (ligne % 2 == 0)
			palette = palette + (niveau_0.taille_x / 2);
	}

	return;
}

static const unsigned char** addr = (const unsigned char**)ADDR_LEVEL;

static void charger_ligne_verticale_hg()
{
	asm("ldx #0");
	asm("debut_boucle:");
	asm("txa");
	asm("pha");
	asm("jsr _load_tile_hg");
	asm("jsr _load_tile_bg");
	asm("pla");
	asm("tax");
	asm("lda _niveau_0+1");
	asm("clc");
	asm("adc %b",(char)ADDR_LEVEL);
	asm("sta %b",(char)ADDR_LEVEL);
	asm("lda %b+1",(char)ADDR_LEVEL);
	asm("adc #0");
	asm("sta %b+1",(char)ADDR_LEVEL);
	asm("inx");
	asm("cpx #15");
	asm("bne debut_boucle");
	asm("rts");
}

static void charger_ligne_verticale_hd()
{
	asm("ldx #0");
	asm("debut_boucle:");
	asm("txa");
	asm("pha");
	asm("jsr _load_tile_hd");
	asm("jsr _load_tile_bd");
	asm("pla");
	asm("tax");
	asm("lda _niveau_0+1");
	asm("clc");
	asm("adc %b",(char)ADDR_LEVEL);
	asm("sta %b",(char)ADDR_LEVEL);
	asm("lda %b+1",(char)ADDR_LEVEL);
	asm("adc #0");
	asm("sta %b+1",(char)ADDR_LEVEL);
	asm("inx");
	asm("cpx #15");
	asm("bne debut_boucle");
	asm("rts");
}

static void charger_ligne_verticale_bg()
{
	asm("ldx #0");
	asm("debut_boucle:");
	asm("txa");
	asm("pha");
	asm("jsr _load_tile_bg");
	asm("lda _niveau_0+1");
	asm("clc");
	asm("adc %b",(char)ADDR_LEVEL);
	asm("sta %b",(char)ADDR_LEVEL);
	asm("lda %b+1",(char)ADDR_LEVEL);
	asm("adc #0");
	asm("sta %b+1",(char)ADDR_LEVEL);
	asm("jsr _load_tile_hg");
	asm("pla");
	asm("tax");
	asm("inx");
	asm("cpx #15");
	asm("bne debut_boucle");
	asm("rts");
}

static void charger_ligne_verticale_bd()
{
	asm("ldx #0");
	asm("debut_boucle:");
	asm("txa");
	asm("pha");
	asm("jsr _load_tile_bd");
	asm("lda _niveau_0+1");
	asm("clc");
	asm("adc %b",(char)ADDR_LEVEL);
	asm("sta %b",(char)ADDR_LEVEL);
	asm("lda %b+1",(char)ADDR_LEVEL);
	asm("adc #0");
	asm("sta %b+1",(char)ADDR_LEVEL);
	asm("jsr _load_tile_hd");
	asm("pla");
	asm("tax");
	asm("inx");
	asm("cpx #15");
	asm("bne debut_boucle");
	asm("rts");
}

void charger_ligne_verticale(unsigned char nametable, unsigned char l, unsigned char c, unsigned int position_x, unsigned int position_y)
{
	*index_in_buffer_tile_groupe = 0;
	*addr = niveau_0.addr + (position_y / 2) * niveau_0.taille_x + (position_x / 2);

	if (position_y % 2 == 0)
	{
		if (position_x % 2 == 0)
			charger_ligne_verticale_hg();
		else
			charger_ligne_verticale_hd();
	}
	else
	{
		if (position_x % 2 == 0)
			charger_ligne_verticale_bg();
		else
			charger_ligne_verticale_bd();
	}

	tiles_set_group_vertical(nametable, l, c);
	tiles_commit_groups();
}

void charger_ligne_horizontale(unsigned char nametable, unsigned char l, unsigned char c, unsigned int position_x, unsigned int position_y)
{
	unsigned char *buffer = TILES_GROUP_BUF;
	unsigned char i = 0;
	const unsigned char* addr = niveau_0.addr;
	unsigned char brique;

	addr += (position_y / 2) * niveau_0.taille_x + (position_x / 2);

	if (position_x % 2 == 1)
	{
		*buffer = GET_TILE(*addr)[1 + position_y % 2];
		buffer++;
		i++;
		addr ++;
	}
	
	while (i < 16)
	{
		brique = *addr;
		
		*buffer = GET_TILE(brique)[0 + position_y % 2];
		buffer++;
		*buffer = GET_TILE(brique)[1 + position_y % 2];
		buffer++;
		
		addr++;
		i++;
	}

	if (position_x % 2 == 1)
		*buffer = GET_TILE(*addr)[0 + position_y % 2];


	tiles_add_change(nametable ^ 0x03, l, c, GET_TILE(*addr)[0 + position_y % 2]);
	tiles_commit_changes();

	tiles_set_group_horizontal(nametable, l, c);
	tiles_commit_groups();
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
