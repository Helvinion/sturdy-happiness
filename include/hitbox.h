#ifndef HITBOX_H
#define HITBOX_H

/* Une hitbox est un rectangle défini par rapport à la position x, y du personnage */
/* Ainsi que ses dimensions par rapport a son coté supérieur gauche */
struct hitbox
{
	const signed char diff_x; /* Delta X et Y de la hitbox par */
	const signed char diff_y; /* rapport à la position du personnage */
	
	const unsigned char taille_x;
	const unsigned char taille_y;
};


struct pack_hitbox
{
	const struct hitbox *collisions; /* hitbox servant a détecter les collisions */
	
	const struct hitbox *degats; /* hitbox servant a détecter les dégats sur le personnage */
	unsigned char nb_hitbox_degats;
	
	const struct hitbox *frappe; /* hitbox servant a détecter les frappes du personnage sur les ennemis*/
	unsigned char nb_hitbox_frappe;	
};

#endif