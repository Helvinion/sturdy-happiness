#include "tileset.h"
#include "zeropage.h"

// Ce tableau décrit toutes les tiles possibles du jeu
// Une tile est un carré de 4 sous-tiles. Elles sont décrites ici
// les unes après les autres. 
const unsigned char tileset[] =
{
	0x00, 0x00, 0x00, 0x00, // 0: Ciel
	0x0d, 0x0d, 0x1f, 0x1f, // 1: Sol plat
	0x1f, 0x1f, 0x1f, 0x1f, // 2: Terre
	0x00, 0x0f, 0x0f, 0x1e, // 3: Sol oblique montée
	0x0e, 0x00, 0x1d, 0x0e, // 4: Sol oblique descente
	0x00, 0x00, 0x0b, 0x0c, // 5: Sol sommet
	0x09, 0x0a, 0x1f, 0x1f, // 6: Sol creux
	0x1e, 0x1f, 0x1f, 0x1f, // 7: Terre coin montee 
	0x1f, 0x1d, 0x1f, 0x1f, // 8: Terre coin descente
	0x1e, 0x1d, 0x1f, 0x1f, // 9: Terre sous sommet
	0x00, 0x0b, 0x0f, 0x1e, // 10: Sol fin montée
	0x0c, 0x00, 0x1c, 0x0e  // 11: Sol début descente
};

unsigned char *index_in_buffer_tile_groupe = INDEX_GRP;

void load_tile_hg(unsigned char brique)
{
	asm("ldy #0");
	asm("lda (sp),y");
	asm("asl");
	asm("asl");
	asm("tax");
	asm("lda %b", (char)INDEX_GRP);
	asm("tay");
	asm("lda _tileset,x");
	asm("sta %b,y", (char)TILES_GROUP_BUF);
	asm("inc %b", (char)INDEX_GRP);
	asm("inc sp");
	asm("rts");
}

void load_tile_hd(unsigned char brique)
{
	asm("ldy #0");
	asm("lda (sp),y");
	asm("asl");
	asm("asl");
	asm("adc #1");
	asm("tax");
	asm("lda %b", (char)INDEX_GRP);
	asm("tay");
	asm("lda _tileset,x");
	asm("sta %b,y", (char)TILES_GROUP_BUF);
	asm("inc %b", (char)INDEX_GRP);
	asm("inc sp");
	asm("rts");
}

void load_tile_bg(unsigned char brique)
{
	asm("ldy #0");
	asm("lda (sp),y");
	asm("asl");
	asm("asl");
	asm("adc #2");
	asm("tax");
	asm("lda %b", (char)INDEX_GRP);
	asm("tay");
	asm("lda _tileset,x");
	asm("sta %b,y", (char)TILES_GROUP_BUF);
	asm("inc %b", (char)INDEX_GRP);
	asm("inc sp");
	asm("rts");
}

void load_tile_bd(unsigned char brique)
{
	asm("ldy #0");
	asm("lda (sp),y");
	asm("asl");
	asm("asl");
	asm("adc #3");
	asm("tax");
	asm("lda %b", (char)INDEX_GRP);
	asm("tay");
	asm("lda _tileset,x");
	asm("sta %b,y", (char)TILES_GROUP_BUF);
	asm("inc %b", (char)INDEX_GRP);
	asm("inc sp");
	asm("rts");
}
