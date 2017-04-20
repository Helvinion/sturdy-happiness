#ifndef PHYSIQUE
#define PHYSIQUE

#include "avatar.h"

struct element_physique
{
	struct avatar *dessin;
	
	signed long int coordonnee_x;
	signed long int coordonnee_y;
	
	signed long int vitesse_x;
	signed long int vitesse_y;

	signed long int acceleration_x;
	signed long int acceleration_y;
	
	unsigned char flags;
};

void mettre_a_jour(struct element_physique *element);

void saut(struct element_physique *element);

#endif