#ifndef TILES_H
#define TILES_H

void tiles_init();
void tiles_commit_changes();
void tiles_add_change(unsigned char l, unsigned char c, unsigned char data);
void tiles_update();

void tiles_commit_groups();
void tiles_add_group_vertical(unsigned char l, unsigned char c, const char *buffer);
void tiles_add_group_horizontal(unsigned char l, unsigned char c, const char *buffer);

#endif /* TILES_H */
