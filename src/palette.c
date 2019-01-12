#include <palette.h>
#include <tiles.h>

#define BUFFER_PALETTE ((struct palette*)0x01b0)
#define TALLE_BUFFER_PALETTE 8

const unsigned short int ATTRTABLES[4] = {0x23c0, 0x27c0, 0x2bc0, 0x2fc0};

void charger_palette(unsigned char nametable, unsigned char ligne, unsigned char colonne, unsigned char color)
{
	unsigned char* attrtable = 0;

	attrtable = (unsigned char*)(ATTRTABLES[nametable] + ligne * 8 + colonne);
	/*
	value = *attrtable;
	
	// Maintenant qu'on a la valeur, il faut choisir lesquels de ses 2 bits il faut modifier.
	// Pour chacune des quatre possibilité, on commence par effacer les deux bits à changer
	// puis on les fixe à la valeur souhaitée.
	if (ligne & 1)
	{
		if (colonne & 1)
			value = (value & 0x3f) | (which & 0x03) << 6; // bas droite : 1100 0000
		else
			value = (value & 0xcf) | (which & 0x03) << 4; // bas gauche : 0011 0000
	}
	else	
	{
		if (colonne & 1)
			value = (value & 0xf3) | (which & 0x03) << 2; // haut droite : 0000 1100
		else
			value = (value & 0xfc) | (which & 0x03) << 0; // haut gauche : 0000 0011
	}
	*/
	tiles_set_change(attrtable, color);
	tiles_commit_changes();
}

void changer_palette(unsigned char which, struct palette* pal)
{
	BUFFER_PALETTE[which] = *pal;
}

struct palette* get_palette(enum Palettes id)
{
	return &(palettes_definies[id]);
}
