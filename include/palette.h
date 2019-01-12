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
	MARRON = 0x07,
	MARR_2 = 0x16,
	PEAU   = 0x36,
	VERT_1 = 0x18,
	SAUMON = 0x26,
	BLEU   = 0x01,
	BLEU_1 = 0x11,
	KAKI   = 0x08,
	BLEU_2 = 0x21
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
	PALETTE_CURSEURS  = 1,
	PALETTE_VISAGE_JOLIVET = 2,
	PALETTE_JOLIVET = 3,
	PALETTE_GRISE = 4,
	PALETTE_NIVEAU_0 = 5
};

struct palette palettes_definies[] =
{
	{NOIR, NOIR, NOIR, NOIR},
	{NOIR, JAUNE, ROUGE, VERT},
	{NOIR, MARRON, PEAU, BLEU},
	{NOIR, VERT, PEAU, BLEU},
	{NOIR, GRIS_0, GRIS_2, BLANC},
	{BLEU_2, MARRON, KAKI, VERT}
};

void changer_palette(unsigned char which, struct palette* pal);
struct palette *get_palette(enum Palettes id);

#endif
