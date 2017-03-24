#include <palette.h>

#define BUFFER_PALETTE ((struct palette*)0x01b0)
#define TALLE_BUFFER_PALETTE 8

void changer_palette(unsigned char which, struct palette* pal)
{
	BUFFER_PALETTE[which] = *pal;
}

struct palette* get_palette(enum Palettes id)
{
	return &(palettes[id]);
}
