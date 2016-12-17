#ifndef COMMON_H
#define COMMON_H

#define PPUADDR (unsigned char*)0x2006
#define PPUDATA (unsigned char*)0x2007

#define TO_PPU_ADDR(LINE, COL) (((short int)(LINE) << 5) + (COL) + 0x2000)
#define PUT_PPU(BYTE) (*PPUADDR) = (BYTE)

#endif /* COMMON_H */