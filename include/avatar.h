#ifndef AVATAR_H
#define AVATAR_H

struct partie_personnage
{
	const signed char delta_x;      // Distance en X de la coordonnée du personnage
	const signed char delta_y;      // Distance en y de la coordonnée du personnage
	const unsigned char sprite_id;  // Dessin de la, partie de personnage
	const unsigned char numero_palette;
};

struct personnage_graphique
{
	const struct partie_personnage const *parties; // Liste des différents sprites à combiner
	const unsigned char taille_parties;      // Taille de la liste
};

struct animation
{
	const struct personnage_graphique const *anim; // Liste des designs de personnages à animer
	const unsigned char taille_anim;         // Taille de l'animation
};

struct pack_anim
{
	const struct animation const *anims;
	const unsigned char nombre_anmis;
};

struct avatar
{
	unsigned char x;                  // Coordonnée X de l'avatar
	unsigned char y;                  // Coordonnée Y de l'avatar
	
	const struct pack_anim anims;     // Animation du personnage
	unsigned char animation_courante; // Animation actuelle
	unsigned char etape_anim;         // Etape courante de l'animation
};

void afficher_personnage(const struct avatar *perso);
void animer(struct avatar *perso);
void changer_animation(struct avatar *perso, unsigned char anim);

#include <liste_animations.h>

#endif