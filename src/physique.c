#include "physique.h"
#include "tiles.h"

static const unsigned char gravite = 2;

#define FLAGS_AU_SOL 0x01

void mettre_a_jour(struct element_physique *element)
{
	// Mise à jour des accélérations
	if (!(element->flags & FLAGS_AU_SOL))
	{
		element->acceleration_y += gravite;
	}
	
	// Mise à jour des vitesses
	element->vitesse_x += element->acceleration_x;
	element->vitesse_y += element->acceleration_y;
	
	// Mise à jour des positions
	element->coordonnee_x += element->vitesse_x;
	element->coordonnee_y += element->vitesse_y;
	
	if (element->coordonnee_y > 150)
	{
		// Au sol;
		element->flags |= FLAGS_AU_SOL;
		element->acceleration_y = 0;
		element->vitesse_y = 0;
		element->coordonnee_y = 150;
	}
	
	element->dessin->x = element->coordonnee_x;
	element->dessin->y = element->coordonnee_y;
}

void saut(struct element_physique *element)
{
	if (element->flags & FLAGS_AU_SOL)
	{
		element->flags &= !FLAGS_AU_SOL;
		element->acceleration_y -= 9;
	}
	else
	{
		tiles_commit_changes();
	}
}