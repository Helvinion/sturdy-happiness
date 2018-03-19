#include "physique.h"
#include "tiles.h"
#include <ecran.h>
#include <niveau.h>


static const unsigned char gravite = 1;
static const unsigned char diviseur_gravite = 3;
static const int impulsion_saut = 6;
static const int vitesse_terminale = 6;

#define FLAGS_AU_SOL 0x01
#define avatar_x ((unsigned char *)0x3A)

static void MaJ_dessin(struct element_physique *element)
{
	// Contiennent un rappel d'un éventuel décalage de la caméra par rapport au perso
	// Si celle si atteint un bord du niveau

	const unsigned char x_favori = 120;
	signed int ret = 0;

	if (element->dessin->x == x_favori)
	{
		// Cas normal
		ret = faux_bouger_camera_x(element->vitesse_x);
		if (ret == element->vitesse_x)
		{
			// On peut bouger la caméra autant qu'on veut !
			bouger_camera_x(element->vitesse_x);
		}
		else
		{
			bouger_camera_x(ret);
			element->dessin->x += (element->vitesse_x - ret);
		}
	}
	else
	{
		// Cas spécial : l'avatar est au bord de l'écran
		if (element->dessin->x > x_favori)
		{
			// l'avatar est trop à droite
			if (element->vitesse_x > 0)
			{
				// Et on veut aller encore plus à droite !
				element->dessin->x += element->vitesse_x;
			}
			else
			{
				// Et on veut revenir à gauche
				element->dessin->x += element->vitesse_x;
				if (element->dessin->x < x_favori)
				{
					// On est trop revenu à gauche !
					bouger_camera_x(element->dessin->x- x_favori);
					element->dessin->x = x_favori;
				}
			}
		}
		else
		{
			// L'avatar est trop à gauche
			if (element->vitesse_x < 0)
			{
				// Et on veut aller encore plus à gauche !
				element->dessin->x += element->vitesse_x;
			}
			else
			{
				// Et on veut revenir à droite
				element->dessin->x += element->vitesse_x;
				if (element->dessin->x > x_favori)
				{
					// On est trop revenu à droite !
					bouger_camera_x(element->dessin->x - x_favori);
					element->dessin->x = x_favori;
				}
			}
		}
	}	
	element->dessin->y = element->coordonnee_y;

	return;
}

static void corriger_verticalement(struct element_physique *element)
{
	signed int future_coordonnee_y = element->coordonnee_y + element->vitesse_y;
	signed int tmp = 0;
	const struct avatar*      raccourci_dessin = element->dessin;
	const struct pack_hitbox* raccourci_hitbox = raccourci_dessin->anims->anims[raccourci_dessin->animation_courante].anim[raccourci_dessin->etape_anim].hitbox;
	const struct hitline*     raccourci_hitbox_bas = raccourci_hitbox->hitline_bas;
	const unsigned char       nb_hitbox_bas = raccourci_hitbox->nb_hitline_bas;
	
	// Application des collisions.
	if (future_coordonnee_y > 191)
	{
		// Au sol;
		element->flags |= FLAGS_AU_SOL;
		element->acceleration_y = 0;
		element->vitesse_y = 0;
		element->coordonnee_y = 191;
	}
	else
	{
		if (element->vitesse_y > 0)
		{
			tmp = detecter_future_collision_bas(element, raccourci_hitbox_bas);
			if (tmp != element->vitesse_y)
			{
				element->flags |= FLAGS_AU_SOL;
				element->acceleration_y = 0;
				element->vitesse_y = 0;
				element->coordonnee_y += tmp;
			}
			else
				element->coordonnee_y = future_coordonnee_y;
		}
		else
			element->coordonnee_y = future_coordonnee_y;
	}
}

static void appliquer_gravite(struct element_physique *element)
{
	static unsigned char i = 1;
	
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

}

void appliquer_physique(struct element_physique *element)
{
	// Gestion horizontale :
	element->vitesse_x += element->acceleration_x;
	if (element->vitesse_x != 0)
		element->coordonnee_x += element->vitesse_x;
	
	// Gestion verticale :
	appliquer_gravite(element);
	corriger_verticalement(element);

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
