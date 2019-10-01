#include "niveau.h"
#include "tileset.h"
#include "tiles.h"
#include "palette.h"
#include "zeropage.h"
#include "ecran.h"

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
    14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,12,13,0,14,14,14,14,14,14,14,14,14,14,14,14,
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
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char niveau_0_palettes_list[4] = {PALETTE_NIVEAU_0, PALETTE_GRISE, PALETTE_NIVEAU_0, PALETTE_NIVEAU_0};

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

		colonne = 0;
		while (colonne < 16)
		{
			charger_brique(nametable ^ 0x03, ligne, colonne, *addr);
			charger_palette(nametable ^ 0x03, ligne / 2, colonne / 2, *palette);
			
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

		palette -= 16;
		// Passer à la ligne suivante
		ligne++;
		addr = addr - 32 + niveau_0.taille_x;
		if (ligne % 2 == 0)
			palette = palette + (niveau_0.taille_x / 2);
	}

	return;
}

static const unsigned char** addr = (const unsigned char**)ADDR_LEVEL;

static void charger_ligne_verticale_hg()
{
	// Initialiser le compteur de boucle
	asm("ldx #0");
	asm("debut_boucle:");

	// Appeler les deux procédures de changement appropriées
	asm("txa");
	asm("pha");
	asm("jsr _load_tile_hg");
	asm("jsr _load_tile_bg");
	asm("pla");
	asm("tax");

	// Incrémenter l'adresse de lecture utilisée par les procédures de changement
	asm("lda _niveau_0+1");
	asm("clc");
	asm("adc %b",(char)ADDR_LEVEL);
	asm("sta %b",(char)ADDR_LEVEL);
	asm("lda %b+1",(char)ADDR_LEVEL);
	asm("adc #0");
	asm("sta %b+1",(char)ADDR_LEVEL);

	// Passer au tour de boucle suivant
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
	static unsigned int dernier_chargement_ver_x = 0;
	static unsigned int dernier_chargement_ver_y = 0;

	if (dernier_chargement_ver_x == position_x && dernier_chargement_ver_y == position_y)
		return;
	
	dernier_chargement_ver_x = position_x;
	dernier_chargement_ver_y = position_y;
	
	*index_in_buffer_tile_groupe = 0;
	*addr = niveau_0.addr + (position_y / 2) * niveau_0.taille_x + (position_x / 2);

	// Pour chacune des positions fournies, charger une ligne à partir d'un des quatre tiles par brique.
	if (position_y % 2 == 0)
	{
		if (position_x % 2 == 0)
			charger_ligne_verticale_hg(); // hg = Haut Gauche
		else
			charger_ligne_verticale_hd(); // hd = Haut Droite
	}
	else
	{
		if (position_x % 2 == 0)
			charger_ligne_verticale_bg(); // bg = Bas Gauche
		else
			charger_ligne_verticale_bd(); // bd = Bas Droite
	}

	tiles_set_group_vertical(nametable, l, c);
	tiles_commit_groups();
	ligne_chargee = 1;
}

void charger_ligne_horizontale_hg()
{
	asm("ldx #0");
	asm("debut_boucle:");
	asm("txa");
	asm("pha");
	asm("jsr _load_tile_hg");
	asm("jsr _load_tile_hd");
	asm("pla");
	asm("tax");
	asm("clc");
	asm("lda %b", (char)ADDR_LEVEL);
	asm("adc #1");
	asm("sta %b", (char)ADDR_LEVEL);
	asm("lda %b+1",(char)ADDR_LEVEL);
	asm("adc #0");
	asm("sta %b+1",(char)ADDR_LEVEL);
	asm("inx");
	asm("cpx #16");
	asm("bne debut_boucle");
	asm("rts");
}

void charger_ligne_horizontale_hd()
{
	asm("ldx #0");
	asm("debut_boucle:");
	asm("txa");
	asm("pha");
	asm("jsr _load_tile_hd");
	asm("clc");
	asm("lda %b", (char)ADDR_LEVEL);
	asm("adc #1");
	asm("sta %b", (char)ADDR_LEVEL);
	asm("lda %b+1",(char)ADDR_LEVEL);
	asm("adc #0");
	asm("sta %b+1",(char)ADDR_LEVEL);
	asm("jsr _load_tile_hg");
	asm("pla");
	asm("tax");
	asm("inx");
	asm("cpx #16");
	asm("bne debut_boucle");
	asm("rts");	
}

void charger_ligne_horizontale_bg()
{
	asm("ldx #0");
	asm("debut_boucle:");
	asm("txa");
	asm("pha");
	asm("jsr _load_tile_bg");
	asm("jsr _load_tile_bd");
	asm("pla");
	asm("tax");
	asm("clc");
	asm("lda %b", (char)ADDR_LEVEL);
	asm("adc #1");
	asm("sta %b", (char)ADDR_LEVEL);
	asm("lda %b+1",(char)ADDR_LEVEL);
	asm("adc #0");
	asm("sta %b+1",(char)ADDR_LEVEL);
	asm("inx");
	asm("cpx #16");
	asm("bne debut_boucle");
	asm("rts");
}

void charger_ligne_horizontale_bd()
{
	asm("ldx #0");
	asm("debut_boucle:");
	asm("txa");
	asm("pha");
	asm("jsr _load_tile_bd");
	asm("clc");
	asm("lda %b", (char)ADDR_LEVEL);
	asm("adc #1");
	asm("sta %b", (char)ADDR_LEVEL);
	asm("lda %b+1",(char)ADDR_LEVEL);
	asm("adc #0");
	asm("sta %b+1",(char)ADDR_LEVEL);
	asm("jsr _load_tile_bg");
	asm("pla");
	asm("tax");
	asm("inx");
	asm("cpx #16");
	asm("bne debut_boucle");
	asm("rts");
}

void charger_ligne_horizontale(unsigned char nametable, unsigned char l, unsigned char c, unsigned int position_x, unsigned int position_y)
{
	static unsigned int dernier_chargement_hor_x = 0;
	static unsigned int dernier_chargement_hor_y = 0;

	if (dernier_chargement_hor_x == position_x && dernier_chargement_hor_y == position_y)
		return;
	
	dernier_chargement_hor_x = position_x;
	dernier_chargement_hor_y = position_y;

	*index_in_buffer_tile_groupe = 0;
	*addr = niveau_0.addr + (position_y / 2) * niveau_0.taille_x + (position_x / 2);

	if (position_y % 2 == 0)
	{
		if (position_x % 2 == 0)
		{
			charger_ligne_horizontale_hg();
			tiles_add_change(nametable ^ 0x03, l, c, GET_TILE(**addr)[0]);
		}		
		else
		{
			charger_ligne_horizontale_hd();
			tiles_add_change(nametable ^ 0x03, l, c, GET_TILE(**addr)[1]);
		}
	}
	else
	{
		if (position_x % 2 == 0)
		{
			charger_ligne_horizontale_bg();
			tiles_add_change(nametable ^ 0x03, l, c, GET_TILE(**addr)[2]);
		}
		else
		{
			charger_ligne_horizontale_bd();
			tiles_add_change(nametable ^ 0x03, l, c, GET_TILE(**addr)[3]);
		}
	}
	
	tiles_commit_changes();

	tiles_set_group_horizontal(nametable, l, c);
	tiles_commit_groups();
	ligne_chargee = 1;
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
