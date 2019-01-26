#ifndef TILESET_H
# define TILESET_H

extern const unsigned char tileset[];

#define GET_TILE(n) (tileset + ((n) * 4))

extern unsigned char *index_in_buffer_tile_groupe;

void load_tile_hg();
void load_tile_hd();
void load_tile_bg();
void load_tile_bd();

#endif