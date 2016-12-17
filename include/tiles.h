#ifndef TILES_H
#define TILES_H

void tiles_init();
void tiles_commit_changes();
void tiles_add_change(unsigned char l, unsigned char c, unsigned char data);
void tiles_update();

#endif /* TILES_H */
