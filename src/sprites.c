#include <sprites.h>

#define SPRITES_BUFFER ((struct sprite*)(0x0200))

#define SPRITES_BUFFER_MAX_SIZE 64

static unsigned char size;

unsigned char add_sprite(unsigned char code, unsigned char x_init, unsigned char y_init, unsigned char flags)
{
	// Vérifier que l'on peut effectivement ajouter un sprite
	if (size == SPRITES_BUFFER_MAX_SIZE)
		return 65;
	
	SPRITES_BUFFER[size].y_pos = y_init;
	SPRITES_BUFFER[size].design = code;
	SPRITES_BUFFER[size].flags = flags;
	SPRITES_BUFFER[size].x_pos = x_init;
	
	size++;
	
	return size - 1;
}

void move_sprite(unsigned char index, unsigned char x, unsigned char y)
{
	SPRITES_BUFFER[index].x_pos = x;
	SPRITES_BUFFER[index].y_pos = y;
}

void hide_sprite(unsigned char index)
{
	if (index >= size)
		return;
	SPRITES_BUFFER[index].flags |= SPRITES_FLAGS_HIDDEN_BACK;
}

void unhide_sprite(unsigned char index)
{
	if (index >= size)
		return;
	
	SPRITES_BUFFER[index].flags &= (!SPRITES_FLAGS_HIDDEN_BACK);
}

void change_sprite_design(unsigned char index, unsigned char new_design)
{
	if (index >= size)
		return;
	
	SPRITES_BUFFER[index].design = new_design;
}

void remove_sprite(unsigned char index)
{
	SPRITES_BUFFER[index].y_pos = 0;
	SPRITES_BUFFER[index].design = 0;
	SPRITES_BUFFER[index].flags = 0;
	SPRITES_BUFFER[index].x_pos = 0;
}

void remove_all()
{
	unsigned char i = 0;
	
	while (i < size)
	{
		remove_sprite(i);
		i++;
	}
	size = 0;
}

void hide_all()
{
	unsigned char i = 0;
	
	while (i < size)
	{
		hide_sprite(i);
		i++;
	}
}

void unhide_all()
{
	unsigned char i = 0;
	
	while (i < size)
	{
		unhide_sprite(i);
		i++;
	}
}
