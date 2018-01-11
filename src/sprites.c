#include <sprites.h>

#define SPRITES_BUFFER ((struct sprite*)(0x0200))

#define SPRITES_BUFFER_MAX_SIZE 64

static unsigned char old_size;
static unsigned char size;

// Cette fonction doit être appellée au début de la boucle principale,
// Elle réinitialise le buffer des sprites.
void sprites_begin()
{
	old_size = size;
	size = 0;
}

// Cette fonction doit être appellée à la fin de la boucle principale.
// Elle efface le reste du buffer.
void sprites_end()
{
	unsigned char i = size;
	
	while (i < old_size)
		remove_sprite(i++);
}

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

void select_sprite_palette(unsigned char index, unsigned char palette)
{
	/* Les deux derniers bits de flags designent la palette a utiliser */
	SPRITES_BUFFER[index].flags |= (palette & 0x03);
}

void remove_sprite(unsigned char index)
{
	unsigned char offset = index * sizeof(struct sprite);

	/*
	SPRITES_BUFFER[index].y_pos = 0;
	SPRITES_BUFFER[index].design = 0;
	SPRITES_BUFFER[index].flags = 0;
	SPRITES_BUFFER[index].x_pos = 0;
	*/

	__asm__("pha");
	__asm__("txa");
	__asm__("pha");
	__asm__ ("lda #%o", offset);
	__asm__ ("tax");
	__asm__ ("lda #0");
	__asm__ ("sta %w,x", 0x200);
	__asm__ ("inx");
	__asm__ ("sta %w,x", 0x200);
	__asm__ ("inx");
	__asm__ ("sta %w,x", 0x200);
	__asm__ ("inx");
	__asm__ ("sta %w,x", 0x200);
	__asm__("pla");
	__asm__("tax");
	__asm__("pla");
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
