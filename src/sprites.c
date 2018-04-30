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
	unsigned char index = size * 4;

	// Vérifier que l'on peut effectivement ajouter un sprite
	if (size == SPRITES_BUFFER_MAX_SIZE)
		return 65;

	// unsigned char* sprite = SPRITES_BUFFER + size;

	__asm__ ("ldy #%o", index);
	__asm__ ("lda (sp),y");
	__asm__ ("tax");

	__asm__ ("ldy #%o", y_init);
	__asm__ ("lda (sp),y");
	__asm__ ("sta %w,x", 0x200);
	__asm__ ("inx");

	__asm__ ("ldy #%o", code);
	__asm__ ("lda (sp),y");
	__asm__ ("sta %w,x", 0x200);
	__asm__ ("inx");

	__asm__ ("ldy #%o", flags);
	__asm__ ("lda (sp),y");
	__asm__ ("sta %w,x", 0x200);
	__asm__ ("inx");

	__asm__ ("ldy #%o", x_init);
	__asm__ ("lda (sp),y");
	__asm__ ("sta %w,x", 0x200);

	/*
	SPRITES_BUFFER[size].y_pos = y_init;
	SPRITES_BUFFER[size].design = code;
	SPRITES_BUFFER[size].flags = flags;
	SPRITES_BUFFER[size].x_pos = x_init;
	*/
	size++;

	return size - 1;
}

void move_sprite(unsigned char index, unsigned char x, unsigned char y)
{
	index *= 4;

	__asm__ ("ldy #%o", index);
	__asm__ ("lda (sp),y");
	__asm__ ("tax");
	__asm__ ("ldy #%o", y);
	__asm__ ("lda (sp),y");
	__asm__ ("sta %w,x", 0x200);
	__asm__ ("inx");
	__asm__ ("inx");
	__asm__ ("inx");
	__asm__ ("ldy #%o", x);
	__asm__ ("lda (sp),y");
	__asm__ ("sta %w,x", 0x200);
}

void hide_sprite(unsigned char index)
{
	if (index >= size)
		return;

	index *= 4;

	__asm__ ("ldy #%o", index);
	__asm__ ("lda (sp),y");
	__asm__ ("tax");
	__asm__ ("inx");
	__asm__ ("inx");
	__asm__ ("lda #%b", SPRITES_FLAGS_HIDDEN_BACK);
	__asm__ ("ora %w,x", 0x200);
	__asm__ ("sta %w,x", 0x200);
}

void unhide_sprite(unsigned char index)
{
	if (index >= size)
		return;

	index *= 4;

	__asm__("ldy #%o", index);
	__asm__("lda (sp),y");
	__asm__("tax");
	__asm__("inx");
	__asm__("inx");
	__asm__("lda #%b", SPRITES_FLAGS_HIDDEN_BACK);
	__asm__("eor #%b", (unsigned int)0xff);
	__asm__("and %w,x", 0x200);
	__asm__("sta %w,x", 0x200);
}

void change_sprite_design(unsigned char index, unsigned char new_design)
{
	if (index >= size)
		return;

	index *= 4;

	__asm__ ("ldy #%o", index);
	__asm__ ("lda (sp),y");
	__asm__ ("tax");
	__asm__ ("inx");
	__asm__ ("ldy #%o", new_design);
	__asm__ ("lda (sp),y");
	__asm__ ("sta %w,x", 0x200);
}

void select_sprite_palette(unsigned char index, unsigned char palette)
{
	/* Les deux derniers bits de flags designent la palette a utiliser */
	if (index >= size)
		return;

	index *= 4;

	__asm__ ("ldy #%o", index);
	__asm__ ("lda (sp),y");
	__asm__ ("tax");
	__asm__ ("inx");
	__asm__ ("inx");
	__asm__ ("ldy #%o", palette);
	__asm__ ("lda (sp),y");
	__asm__ ("and #%b", 0x03);
	__asm__ ("ora %w,x", 0x200);
	__asm__ ("sta %w,x", 0x200);
}

void remove_sprite(unsigned char index)
{
	unsigned char offset = index * 4; //sizeof(struct sprite);

	/*
	SPRITES_BUFFER[index].y_pos = 0;
	SPRITES_BUFFER[index].design = 0;
	SPRITES_BUFFER[index].flags = 0;
	SPRITES_BUFFER[index].x_pos = 0;
	*/

	__asm__ ("ldy #%o", offset);
	__asm__ ("lda (sp),y");
	__asm__ ("tax");
	__asm__ ("lda #0");
	__asm__ ("sta %w,x", 0x200);
	__asm__ ("inx");
	__asm__ ("sta %w,x", 0x200);
	__asm__ ("inx");
	__asm__ ("sta %w,x", 0x200);
	__asm__ ("inx");
	__asm__ ("sta %w,x", 0x200);
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
