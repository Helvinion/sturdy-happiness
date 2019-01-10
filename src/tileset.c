#include "tileset.h"

// Ce tableau décrit toutes les tiles possibles du jeu
// Une tile est un carré de 4 sous-tiles. Elles sont décrites ici
// les unes après les autres. 
unsigned char tileset[] =
{
	0x00, 0x00, 0x00, 0x00, // Ciel
	0x0f, 0x0f, 0x1f, 0x1f,  // Sol
	0x1e, 0x1e, 0x1e, 0x1e  // Terre
};
