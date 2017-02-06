#include <sprites.h>

#define SPRITES_BUFFER ((struct sprite*)(0x0200))

#define SPRITES_BUFFER_MAX_SIZE 64

static unsigned char size;

unsigned char add_sprite (unsigned char code, unsigned char x_init, unsigned char y_init, unsigned char flags)
{
	// Vérifier que l'on peut effectivement ajouter un sprite
	if (size == SPRITES_BUFFER_MAX_SIZE)
		return 65;
	
	SPRITES_BUFFER[size].x_pos = x_init;
	SPRITES_BUFFER[size].y_pos = y_init;
	SPRITES_BUFFER[size].design = code;
	SPRITES_BUFFER[size].flags = flags;
	
	size++;
	
	return size - 1;
}

void move_sprite (unsigned char index, unsigned char x, unsigned char y)
{
	SPRITES_BUFFER[index].x_pos = x;
	SPRITES_BUFFER[index].y_pos = y;
}
