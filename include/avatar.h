#ifndef AVATAR_H
#define AVATAR_H

struct partie_personnage
{
	signed char delta_x;      // Distance en X de la coordonnée du personnage
	signed char delta_y;      // Distance en y de la coordonnée du personnage
	unsigned char sprite_id;  // Dessin de la, partie de personnage
};

struct personnage_graphique
{
	struct partie_personnage* parties; // Liste des différents sprites à combiner
	unsigned char taille_parties;      // Taille de la liste
};

struct animation
{
	struct personnage_graphique* anim; // Liste des designs de personnages à animer
	unsigned char taille_anim;         // Taille de l'animation
};

struct avatar
{
	unsigned char x;           // Coordonnée X de l'avatar
	unsigned char y;           // Coordonnée Y de l'avatar
	
	struct animation anim;     // Animation du personnage
	unsigned char etape_anim;  // Etape courante de l'animation
};

void afficher_personnage(unsigned char x, unsigned char y, struct personnage_graphique* perso);

#endif