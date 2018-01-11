#include <ecran.h>

#define SCROLL_X  (unsigned char*)(0x2E) // Srolling horizontal (traité en VBlank)
#define SCROLL_Y  (unsigned char*)(0x2F) // Scrolling vertical (traité en VBlank)

void set_scrolling(unsigned char x, unsigned char y)
{
	*SCROLL_X = x;
	*SCROLL_Y = y;
}

void change_scrolling_x(char diff)
{
	(*SCROLL_X) += diff;
}

void change_scrolling_y(char diff)
{
	(*SCROLL_Y) += diff;
}
