#include "physique.h"
#include "tiles.h"

static const unsigned char gravite = 1;
static const int impulsion_saut = 6;
static const int vitesse_terminale = 7;

#define FLAGS_AU_SOL 0x01

static void MaJ_dessin(struct element_physique *element)
{
	element->dessin->x = element->coordonnee_x;
	element->dessin->y = element->coordonnee_y;
}

void appliquer_physique(struct element_physique *element)
{
	static unsigned char i = 1;

	// Gestion horizontale :
	element->vitesse_x += element->acceleration_x;
	element->coordonnee_x += element->vitesse_x;

	
	// Gestion verticale :
	// Faire tomber le perso s'il n'est pas au sol.
	if (!(element->flags & FLAGS_AU_SOL))
	{
		element->acceleration_y += gravite;
	}
	
	// Mise à jour des vitesses
	element->vitesse_y += (element->acceleration_y >> 3);
	
	if (element->vitesse_y > vitesse_terminale)
		element->vitesse_y = vitesse_terminale;
	
	// Mise à jour des positions
	element->coordonnee_y += element->vitesse_y;
	
	if (element->coordonnee_y > 150)
	{
		// Au sol;
		element->flags |= FLAGS_AU_SOL;
		element->acceleration_y = 0;
		element->vitesse_y = 0;
		element->coordonnee_y = 150;
	}
	
	MaJ_dessin(element);
}

void saut(struct element_physique *element)
{
		element->flags &= !FLAGS_AU_SOL;
		element->acceleration_y = -impulsion_saut;
}