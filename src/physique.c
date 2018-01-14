#include "physique.h"
#include "tiles.h"
#include <ecran.h>


static const unsigned char gravite = 1;
static const unsigned char diviseur_gravite = 3;
static const int impulsion_saut = 6;
static const int vitesse_terminale = 5;

#define FLAGS_AU_SOL 0x01

static void MaJ_dessin(struct element_physique *element)
{
	// Contiennent un rappel d'un éventuel décalage de la caméra par rapport au perso
	// Si celle si atteint un bord du niveau
	static signed int diff_x = 0;
	signed int ret = 0;
	signed char camera_x = element->vitesse_x;

	
	if (diff_x != 0)
	{
		// On a un décalage de caméra: on l'immobilise donc pour le moment.
		camera_x = 0;

		// diff_x a changé de signe : la caméra peut à nouveau bouger !
		if ((diff_x < 0 && diff_x + element->vitesse_x > 0) || (diff_x > 0 && diff_x + element->vitesse_x < 0))
		{
			camera_x = diff_x + element->vitesse_x;
			element->dessin->x += (element->vitesse_x - camera_x);
			diff_x = 0;
		}
		else
		{
			diff_x += element->vitesse_x;
			element->dessin->x += element->vitesse_x;
		}
	}

	ret = bouger_camera_x(camera_x);
	diff_x += ret;
	
	if (ret != 0) 		// La caméra est collée à droite (ou à gauche) : il faut bouger les sprites de l'avatar lui même
		element->dessin->x += ret;

	element->dessin->y = element->coordonnee_y;
}

void appliquer_physique(struct element_physique *element)
{
	static unsigned char i = 1;

	// Gestion horizontale :
	element->vitesse_x += element->acceleration_x;
	element->coordonnee_x += element->vitesse_x;
	
	// Gestion verticale :
	// Mise à jour des vitesses
	if (element->acceleration_y != 0) // Si une accélaration doit être appliquée, on l'applique.
	{
		element->vitesse_y += element->acceleration_y;
	}
	else if (!(element->flags & FLAGS_AU_SOL))	// Sinon si on est en mode "chute".
	{
		if (i++ == diviseur_gravite)
		{
			i = 1;
			element->vitesse_y += gravite;
		}
	}
	
	// Limite la vitesse max ateignable.
	if (element->vitesse_y > vitesse_terminale)
		element->vitesse_y = vitesse_terminale;
	
	// Mise à jour des positions
	element->coordonnee_y += element->vitesse_y;
	
	// Application des collisions.
	if (element->coordonnee_y > 194)
	{
		// Au sol;
		element->flags |= FLAGS_AU_SOL;
		element->acceleration_y = 0;
		element->vitesse_y = 0;
		element->coordonnee_y = 194;
		i = 1;
	}
	
	// Remise à zéro des forces
	element->acceleration_x = 0;
	element->acceleration_y = 0;
	
	MaJ_dessin(element);
}

void saut(struct element_physique *element)
{
		element->flags &= !FLAGS_AU_SOL;
		element->vitesse_y = 0;
		element->acceleration_y = -impulsion_saut;
}
