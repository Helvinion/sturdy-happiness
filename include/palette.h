#ifndef PALETTE_H
#define PALETTE_H

enum Couleur
{
	NOIR   = 0x3f,
	NOIR_1 = 0x2f,
	NOIR_2 = 0x1f,
	NOIR_3 = 0x0f,
	NOIR_4 = 0x3e,
	NOIR_5 = 0x2e,
	NOIR_6 = 0x1e,
	NOIR_7 = 0x0e,	
	NOIR_8 = 0x1d,
	NOIR_9 = 0x0d,
	GRIS_0 = 0x2d,
	GRIS_1 = 0x00,
	GRIS_2 = 0x10,
	GRIS_3 = 0x3d,
	GRIS_4 = 0x20,
	BLANC  = 0x30,
	JAUNE  = 0x28,
	ROUGE  = 0x06,
	VERT   = 0x1a,
};

struct palette
{
	unsigned char transparance;
	unsigned char couleur_1;
	unsigned char couleur_2;
	unsigned char couleur_3;
};

enum Palettes
{
	PALETTE_NOIRE = 0,
	PALETTE_BASE  = 1,
	PALETTE_GRISE = 2,
};

struct palette palettes[] = 
{
	{NOIR, NOIR, NOIR, NOIR},	
	{NOIR, JAUNE, ROUGE, VERT},
	{NOIR, GRIS_0, GRIS_2, BLANC}
};

void changer_palette(unsigned char which, struct palette* pal);
struct palette *get_palette(enum Palettes id);

#endif