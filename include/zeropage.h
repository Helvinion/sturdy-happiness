///////////// ZEROPAGE /////////////
// TODO: générer ce fichier automatiquement à partir de zeropage.inc

#ifndef ZEROPAGE_H
# define ZEROPAGE_H

//              NOM             |   CASE            || COMMENTAIRE
# define     ZP_FRAMECNT1           ((void*)0x20)   // Compteur de frames
# define     ZP_FRAMECNT2           ((void*)0x21)   // Compteur de frames modulo 6
# define     ZP_NTSCMODE            ((void*)0x22)   // Mode NTSC ou PAL
# define     ZP_ADR_MUS             ((void*)0x23)   // Adresse de la musique à jouer sur deux octets
# define     ZP_ADR_MUS_CUR         ((void*)0x25)   // Adresse de la note à jouer
# define     ZP_MUS_CMPT            ((void*)0x27)   // Compteur actuel
# define     ZP_MUS_REG_TMP         ((void*)0x28)   // Adresse du registre de musique où écrire
# define     ZP_PPU_MASK_VAR        ((void*)0x2A)   // Adresse de masquage de la PPU
//                                  ((void*)0x2B)
//                                  ((void*)0x2C)
# define     ZP_SCROLL_NTABLE       ((void*)0x2D)   // Registre temporaire pour calculer du scrolling
# define     ZP_SCROLL_X            ((void*)0x2E)   // Srolling horizontal (traité en VBlank)
# define     ZP_SCROLL_Y            ((void*)0x2F)   // Scrolling vertical (traité en VBlank)
# define     ZP_PPU_CTRL_VAR        ((void*)0x30)   // Controle de la PPU (traité en VBlank)
# define     ZP_RAND_SEED           ((void*)0x31)   // Graine du générateur aléatoire
# define     ZP_NAME_UPD_ADR        ((void*)0x32)   // Adresse du buffer de modifs de tiles (traité en VBlank)
# define     ZP_NAME_UPD_LEN        ((void*)0x34)   // Nombre de modifications de tiles à appliquer (traité en VBlank)
//                                  ((void*)0x35)
# define     ZP_TILES_GROUP         ((void*)0x36)   // Adresse du buffer des goupes de modifs (traité en VBlank)
# define     ZP_T_GROUP_SIZE        ((void*)0x38)   // Taille du buffer
//                                  ((void*)0x39)
# define     ZP_ADDR_AVATAR_X       ((void*)0x3A)
//OCCUPE                            ((void*)0x3B)
#define      TILES_GROUP_BUF        ((unsigned char*)0x3C)
// OCCUPE TILESGROUP                ((void*)0x3D)
// OCCUPE TILESGROUP                ((void*)0x3E)
// OCCUPE TILESGROUP                ((void*)0x3F)
// OCCUPE TILESGROUP                ((void*)0x40)
// OCCUPE TILESGROUP                ((void*)0x41)
// OCCUPE TILESGROUP                ((void*)0x42)
// OCCUPE TILESGROUP                ((void*)0x43)
// OCCUPE TILESGROUP                ((void*)0x44)
// OCCUPE TILESGROUP                ((void*)0x45)
// OCCUPE TILESGROUP                ((void*)0x46)
// OCCUPE TILESGROUP                ((void*)0x47)
// OCCUPE TILESGROUP                ((void*)0x48)
// OCCUPE TILESGROUP                ((void*)0x49)
// OCCUPE TILESGROUP                ((void*)0x4A)
// OCCUPE TILESGROUP                ((void*)0x4B)
// OCCUPE TILESGROUP                ((void*)0x4C)
// OCCUPE TILESGROUP                ((void*)0x4D)
// OCCUPE TILESGROUP                ((void*)0x4E)
// OCCUPE TILESGROUP                ((void*)0x4F)
// OCCUPE TILESGROUP                ((void*)0x50)
// OCCUPE TILESGROUP                ((void*)0x51)
// OCCUPE TILESGROUP                ((void*)0x52)
// OCCUPE TILESGROUP                ((void*)0x53)
// OCCUPE TILESGROUP                ((void*)0x54)
// OCCUPE TILESGROUP                ((void*)0x55)
// OCCUPE TILESGROUP                ((void*)0x56)
// OCCUPE TILESGROUP                ((void*)0x57)
// OCCUPE TILESGROUP                ((void*)0x58)
// OCCUPE TILESGROUP                ((void*)0x59)
// OCCUPE TILESGROUP                ((void*)0x5A)
// OCCUPE TILESGROUP                ((void*)0x5B)
#define INDEX_GRP                   ((unsigned char*)0x5C)
#define ADDR_LEVEL                  ((unsigned char*)0x5D)
// OCCUPE                           ((void*)0x5E)
#define ACTIVER_BARRE               ((unsigned char*)0x5F)
//                                  ((void*)0x60)
//                                  ((void*)0x61)
//                                  ((void*)0x62)
//                                  ((void*)0x63)
//                                  ((void*)0x64)
//                                  ((void*)0x65)
//                                  ((void*)0x66)
//                                  ((void*)0x67)
//                                  ((void*)0x68)
//                                  ((void*)0x69)
//                                  ((void*)0x6A)
//                                  ((void*)0x6B)
//                                  ((void*)0x6C)
//                                  ((void*)0x6D)
//                                  ((void*)0x6E)
//                                  ((void*)0x6F)
//                                  ((void*)0x70)
//                                  ((void*)0x71)
//                                  ((void*)0x72)
//                                  ((void*)0x73)
//                                  ((void*)0x74)
//                                  ((void*)0x75)
//                                  ((void*)0x76)
//                                  ((void*)0x77)
//                                  ((void*)0x78)
//                                  ((void*)0x79)
//                                  ((void*)0x7A)
//                                  ((void*)0x7B)
//                                  ((void*)0x7C)
//                                  ((void*)0x7D)
//                                  ((void*)0x7E)
//                                  ((void*)0x7F)
//                                  ((void*)0x80)
//                                  ((void*)0x81)
//                                  ((void*)0x82)
//                                  ((void*)0x83)
//                                  ((void*)0x84)
//                                  ((void*)0x85)
//                                  ((void*)0x86)
//                                  ((void*)0x87)
//                                  ((void*)0x88)
//                                  ((void*)0x89)
//                                  ((void*)0x8A)
//                                  ((void*)0x8B)
//                                  ((void*)0x8C)
//                                  ((void*)0x8D)
//                                  ((void*)0x8E)
//                                  ((void*)0x8F)
//                                  ((void*)0x90)
//                                  ((void*)0x91)
//                                  ((void*)0x92)
//                                  ((void*)0x93)
//                                  ((void*)0x94)
//                                  ((void*)0x95)
//                                  ((void*)0x96)
//                                  ((void*)0x97)
//                                  ((void*)0x98)
//                                  ((void*)0x99)
//                                  ((void*)0x9A)
//                                  ((void*)0x9B)
//                                  ((void*)0x9C)
//                                  ((void*)0x9D)
//                                  ((void*)0x9E)
//                                  ((void*)0x9F)
//                                  ((void*)0xA0)
//                                  ((void*)0xA1)
//                                  ((void*)0xA2)
//                                  ((void*)0xA3)
//                                  ((void*)0xA4)
//                                  ((void*)0xA5)
//                                  ((void*)0xA6)
//                                  ((void*)0xA7)
//                                  ((void*)0xA8)
//                                  ((void*)0xA9)
//                                  ((void*)0xAA)
//                                  ((void*)0xAB)
//                                  ((void*)0xAC)
//                                  ((void*)0xAD)
//                                  ((void*)0xAE)
//                                  ((void*)0xAF)
//                                  ((void*)0xB0)
//                                  ((void*)0xB1)
//                                  ((void*)0xB2)
//                                  ((void*)0xB3)
//                                  ((void*)0xB4)
//                                  ((void*)0xB5)
//                                  ((void*)0xB6)
//                                  ((void*)0xB7)
//                                  ((void*)0xB8)
//                                  ((void*)0xB9)
//                                  ((void*)0xBA)
//                                  ((void*)0xBB)
//                                  ((void*)0xBC)
//                                  ((void*)0xBD)
//                                  ((void*)0xBE)
//                                  ((void*)0xBF)
//                                  ((void*)0xC0)
//                                  ((void*)0xC1)
//                                  ((void*)0xC2)
//                                  ((void*)0xC3)
//                                  ((void*)0xC4)
//                                  ((void*)0xC5)
//                                  ((void*)0xC6)
//                                  ((void*)0xC7)
//                                  ((void*)0xC8)
//                                  ((void*)0xC9)
//                                  ((void*)0xCA)
//                                  ((void*)0xCB)
//                                  ((void*)0xCC)
//                                  ((void*)0xCD)
//                                  ((void*)0xCE)
//                                  ((void*)0xCF)
//                                  ((void*)0xD0)
//                                  ((void*)0xD1)
//                                  ((void*)0xD2)
//                                  ((void*)0xD3)
//                                  ((void*)0xD4)
//                                  ((void*)0xD5)
//                                  ((void*)0xD6)
//                                  ((void*)0xD7)
//                                  ((void*)0xD8)
//                                  ((void*)0xD9)
//                                  ((void*)0xDA)
//                                  ((void*)0xDB)
//                                  ((void*)0xDC)
//                                  ((void*)0xDD)
//                                  ((void*)0xDE)
//                                  ((void*)0xDF)
//                                  ((void*)0xE0)
//                                  ((void*)0xE1)
//                                  ((void*)0xE2)
//                                  ((void*)0xE3)
//                                  ((void*)0xE4)
//                                  ((void*)0xE5)
//                                  ((void*)0xE6)
//                                  ((void*)0xE7)
//                                  ((void*)0xE8)
//                                  ((void*)0xE9)
//                                  ((void*)0xEA)
//                                  ((void*)0xEB)
//                                  ((void*)0xEC)
//                                  ((void*)0xED)
//                                  ((void*)0xEE)
//                                  ((void*)0xEF)
//                                  ((void*)0xF0)
//                                  ((void*)0xF1)
//                                  ((void*)0xF2)
//                                  ((void*)0xF3)
//                                  ((void*)0xF4)
//                                  ((void*)0xF5)
//                                  ((void*)0xF6)
//                                  ((void*)0xF7)
//                                  ((void*)0xF8)
//                                  ((void*)0xF9)
//                                  ((void*)0xFA)
//                                  ((void*)0xFB)
//                                  ((void*)0xFC)
//                                  ((void*)0xFD)
//                                  ((void*)0xFE)
//                                  ((void*)0xFF)

///////////// Registres de la NES /////////////
# define     ZP_PPU_CTRL            ((void*)0x2000)
# define     ZP_PPU_MASK            ((void*)0x2001)
# define     ZP_PPU_STATUS          ((void*)0x2002)
# define     ZP_PPU_OAM_ADDR        ((void*)0x2003)
# define     ZP_PPU_OAM_DATA        ((void*)0x2004)
# define     ZP_PPU_SCROLL          ((void*)0x2005)
# define     ZP_PPU_ADDR            ((void*)0x2006)
# define     ZP_PPU_DATA            ((void*)0x2007)
# define     ZP_PPU_OAM_DMA         ((void*)0x4014)
# define     ZP_PPU_FRAMECNT        ((void*)0x4017)
# define     ZP_DMC_FREQ            ((void*)0x4010)
# define     ZP_CTRL_PORT1          ((void*)0x4016)
# define     ZP_OAM_BUF             ((void*)0x0200)
# define     ZP_PAL_BUF             ((void*)0x01b0)

#endif // !ZEROPAGE_H
