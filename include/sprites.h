#define SPRITES_FLAGS_FLIP_VERT   0x80
#define SPRITES_FLAGS_FLIP_HORI   0x40
#define SPRITES_FLAGS_HIDDEN_BACK 0x20
#define SPRITES_FLAGS_COLORS_00   0x00
#define SPRITES_FLAGS_COLORS_01   0x01
#define SPRITES_FLAGS_COLORS_10   0x10
#define SPRITES_FLAGS_COLORS_11   0x11

#define SPRITE_Y      0
#define SPRITE_DESIGN 1
#define SPRITE_FLAGS  2
#define SPRITE_X      3

typedef unsigned char sprite[4];

/*
struct sprite
{
	unsigned char y_pos;
	unsigned char design;
	unsigned char flags;
	unsigned char x_pos;
};
*/

void sprites_begin();

void sprites_end();

unsigned char add_sprite (unsigned char code, unsigned char x_init, unsigned char y_init, unsigned char flags);

void move_sprite (unsigned char index, unsigned char x, unsigned char y);

void remove_sprite(unsigned char index);

void hide_sprite(unsigned char index);

void unhide_sprite(unsigned char index);

void change_sprite_design(unsigned char index, unsigned char new_design);

void select_sprite_palette(unsigned char index, unsigned char palette);

void remove_all();

void hide_all();

void unhide_all();
