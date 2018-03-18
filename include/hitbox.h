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

/* Une hitline est une ligne défini par rapport à la position x, y du personnage, ainsi que par sa taille */
struct hitline
{
	const signed char diff_x; /* Delta X et Y de la hitbox par */
	const signed char diff_y; /* rapport à la position du personnage */
	
	const unsigned char taille;
};

struct pack_hitbox
{
	const struct hitline* hitline_haut; /* hitline à vérifier quand le personnage va vers le haut */
	unsigned char nb_hitline_haut;

	const struct hitline* hitline_bas; /* hitline à vérifier quand le personnage va vers le bas */
	unsigned char nb_hitline_bas;

	const struct hitline* hitline_gauche; /* hitline à vérifier quand le personnage va vers la gauche */
	unsigned char nb_hitline_gauche;

	const struct hitline* hitline_droite; /* hitline à vérifier quand le personnage va vers la droite */
	unsigned char nb_hitline_droite;

	const struct hitbox* degats; /* hitbox servant a détecter les dégats sur le personnage */
	unsigned char nb_hitbox_degats;
	
	const struct hitbox* frappe; /* hitbox servant a détecter les frappes du personnage sur les ennemis*/
	unsigned char nb_hitbox_frappe;	
};

#endif