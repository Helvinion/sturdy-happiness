#ifndef TILES_H
#define TILES_H

void tiles_init();
void tiles_commit_changes();
void tiles_add_change(unsigned char nametable, unsigned char l, unsigned char c, unsigned char data);
void tiles_update();

void tiles_commit_groups();
void tiles_add_group_vertical(unsigned char nametable, unsigned char c, const char *buffer);
void tiles_add_group_horizontal(unsigned char nametable, unsigned char l, unsigned int step, const char *buffer);

unsigned char *tiles_get_buffer();
void tiles_set_group_vertical(unsigned char nametable, unsigned char c);
void tiles_set_group_horizontal(unsigned char nametable, unsigned char l);


#endif /* TILES_H */
