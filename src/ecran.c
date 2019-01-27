#include <ecran.h>
#include <niveau.h>

#define OLD_SCROLL    (unsigned char*)(0x2D) // Registre de travail
#define SCROLL_X      (unsigned char*)(0x2E) // Srolling horizontal (traité en VBlank)
#define SCROLL_Y      (unsigned char*)(0x2F) // Scrolling vertical (traité en VBlank)
#define PPU_CTRL_VAR  (unsigned char*)(0x30) // Nametable de départ pour le scrolling (aussi géré en VBlank)

// Par rapport au coin supérieur gauche du niveau.
static unsigned int camera_x;
static unsigned int camera_y;

// Indique si l'écriture d'une ligne a déjà été faite pendant ce tour de moteur.
unsigned char ligne_chargee;

void fixer_position_camera(unsigned int x, unsigned int y)
{
	// La nouvelle nametable est l'ancienne (deux derniers octets de PPU_CTRL_VAR) inversée (xor sur les deux derniers octets)
	unsigned char new_nametable = ((*PPU_CTRL_VAR) & (unsigned char)0x03) ^ (unsigned char)0x03;

	// Ordonner au moteur de niveau de charger les tiles correspondantes.
	charger_niveau(new_nametable, x / 8, y / 8);
	camera_x = x;
	camera_y = y;

	// Switcher de nametable
	(*PPU_CTRL_VAR) ^= 0x03;
}

// Indique de combien de pixels la camera pourra bouger
signed char faux_bouger_camera_x(signed char pixels)
{
	// Sécurité : éviter un camera_x < 0.
	// Sécurité : éviter un camera_x > taille_x_niveau_courant
	if (pixels < 0 && -pixels > camera_x)
		pixels = camera_x;
	else if (pixels > 0 && camera_x + 256 + pixels > 8 * taille_x_niveau_courant())
		pixels = 8 * taille_x_niveau_courant() - camera_x - 256;

	return pixels;
}

unsigned char bouger_camera_droite(unsigned char pixels)
{
	unsigned char sav = pixels;

	// Sécurité : éviter un camera_x > taille_x_niveau_courant
	if (camera_x + 256 + pixels > 8 * taille_x_niveau_courant())
		pixels = 8 * taille_x_niveau_courant() - camera_x - 256;

	camera_x += pixels;

	(*OLD_SCROLL) = (*SCROLL_X);
	(*SCROLL_X) += pixels;

	if (!ligne_chargee)
	{
		// Inverse le dernier bit de ce registre pour changer de Nametable : on est arrivé au bout de l'autre.
		if ((*SCROLL_X) < (*OLD_SCROLL))
			(*PPU_CTRL_VAR) ^= 0x03;

		charger_ligne_verticale(((*PPU_CTRL_VAR) & (unsigned char)0x03) ^ (unsigned char)0x03, (*SCROLL_Y) / 8, (*SCROLL_X) / 8, (camera_x + 256) / 8, camera_y / 8);
	}

	return sav - pixels;
}

unsigned char bouger_camera_gauche(unsigned char pixels)
{
	unsigned char sav = pixels;

	// Sécurité : éviter un camera_x < 0.
	if (pixels > camera_x)
		pixels = camera_x;

	camera_x -= pixels;

	(*OLD_SCROLL) = (*SCROLL_X);
	(*SCROLL_X) -= pixels;

	if (!ligne_chargee)
	{
		if ((*SCROLL_X) > (*OLD_SCROLL))
			(*PPU_CTRL_VAR) ^= 0x03; // Inverse le dernier bit de ce registre pour changer de Nametable : on est arrivé au bout de l'autre.

			charger_ligne_verticale(((*PPU_CTRL_VAR) & (unsigned char)0x03), (*SCROLL_Y) / 8, (*SCROLL_X) / 8, camera_x / 8, camera_y / 8);
	}

	return sav - pixels;
}

signed char bouger_camera_x(signed char pixels)
{
	signed char sav = pixels;

	// Sécurité : éviter un camera_x < 0.
	// Sécurité : éviter un camera_x > taille_x_niveau_courant
	if (pixels < 0 && -pixels > camera_x)
		pixels = camera_x;
	else if (pixels > 0 && camera_x + 256 + pixels > 8 * taille_x_niveau_courant())
		pixels = 8 * taille_x_niveau_courant() - camera_x - 256;

	camera_x += pixels;

	(*OLD_SCROLL) = (*SCROLL_X);
	(*SCROLL_X) += pixels;

	if (!ligne_chargee)
	{
		// Les parenthèses sont obligatoires parce que ce vieux cc65 ne gère pas les priorités d'opérateurs.
		if ((pixels > 0 && (*SCROLL_X) < (*OLD_SCROLL)) || (pixels < 0 && (*SCROLL_X) > (*OLD_SCROLL)))
			(*PPU_CTRL_VAR) ^= 0x03; // Inverse le dernier bit de ce registre pour changer de Nametable : on est arrivé au bout de l'autre.

		if (pixels > 0)
		{
			charger_ligne_verticale(((*PPU_CTRL_VAR) & (unsigned char)0x03) ^ (unsigned char)0x03, (*SCROLL_Y) / 8, (*SCROLL_X) / 8, (camera_x + 256) / 8, camera_y / 8);
		}
		else
		{
			charger_ligne_verticale(((*PPU_CTRL_VAR) & (unsigned char)0x03), (*SCROLL_Y) / 8, (*SCROLL_X) / 8, camera_x / 8, camera_y / 8);
		}
	}

	return sav - pixels;
}

unsigned char bouger_camera_bas(unsigned char pixels)
{
	unsigned char sav = pixels;

	if (pixels == 0)
		return 0 ;

	// Sécurité : éviter un camera_y > taille_y_niveau_courant
	else if (camera_y + 240 + pixels > 8 * taille_y_niveau_courant())
		pixels = 8 * taille_y_niveau_courant() - camera_y - 240;

	camera_y += pixels;

	(*OLD_SCROLL) = (*SCROLL_Y);
	(*SCROLL_Y) += pixels;

	if (!ligne_chargee)
	{
		// L'écran de la NES ne fait que 240 pixels en hauteur, le controle de l'inversion de la nametable est donc plus compliqué.
		if (pixels > 0 && ((*OLD_SCROLL) > (*SCROLL_Y) || (*SCROLL_Y) > 240))
		{
			(*SCROLL_Y) += 16;
			(*PPU_CTRL_VAR) ^= 0x03;
			// Inverse le penultième bit de ce registre pour changer de Nametable : on est arrivé au bout de l'autre.
		}
		
			charger_ligne_horizontale(((*PPU_CTRL_VAR) & (unsigned char)0x03), (*SCROLL_Y) / 8, (*SCROLL_X) / 8, camera_x / 8, (camera_y + 240) / 8);
	}

	return sav - pixels;
}

unsigned char bouger_camera_haut(unsigned char pixels)
{
	unsigned char sav = pixels;

	if (pixels == 0)
		return 0 ;

	// Sécurité : éviter un camera_y < 0.
	if (pixels > camera_y)
		pixels = camera_y;

	camera_y -= pixels;

	(*OLD_SCROLL) = (*SCROLL_Y);
	(*SCROLL_Y) -= pixels;

	if (!ligne_chargee)
	{
		if ((unsigned char)pixels > (*OLD_SCROLL))
		{
			(*SCROLL_Y) -= 16;
			(*PPU_CTRL_VAR) ^= 0x03;
			// Inverse le penultième bit de ce registre pour changer de Nametable : on est arrivé au bout de l'autre.
		}
		
		charger_ligne_horizontale(((*PPU_CTRL_VAR) & (unsigned char)0x03), (*SCROLL_Y) / 8 + 1, (*SCROLL_X) / 8, camera_x / 8, camera_y / 8);
	}

	return sav - pixels;
}

signed char bouger_camera_y(signed char pixels)
{
	signed char sav = pixels;

	if (pixels == 0)
		return 0 ;

	// Sécurité : éviter un camera_y < 0.
	// Sécurité : éviter un camera_y > taille_y_niveau_courant
	if (pixels < 0 && -pixels > camera_y)
		pixels = camera_y;
	else if (pixels > 0 && camera_y + 240 + pixels > 8 * taille_y_niveau_courant())
		pixels = 8 * taille_y_niveau_courant() - camera_y - 240;

	camera_y += pixels;

	(*OLD_SCROLL) = (*SCROLL_Y);
	(*SCROLL_Y) += pixels;

	if (!ligne_chargee)
	{
		// L'écran de la NES ne fait que 240 pixels en hauteur, le controle de l'inversion de la nametable est donc plus compliqué.
		if (pixels > 0 && ((*OLD_SCROLL) > (*SCROLL_Y) || (*SCROLL_Y) > 240))
		{
			(*SCROLL_Y) += 16;
			(*PPU_CTRL_VAR) ^= 0x03;
			// Inverse le penultième bit de ce registre pour changer de Nametable : on est arrivé au bout de l'autre.
		}
		else if (pixels < 0 && ((unsigned char)-pixels) > (*OLD_SCROLL))
		{
			(*SCROLL_Y) -= 16;
			(*PPU_CTRL_VAR) ^= 0x03;
			// Inverse le penultième bit de ce registre pour changer de Nametable : on est arrivé au bout de l'autre.
		}
		
		if (pixels > 0)
		{
			charger_ligne_horizontale(((*PPU_CTRL_VAR) & (unsigned char)0x03), (*SCROLL_Y) / 8, (*SCROLL_X) / 8, camera_x / 8, (camera_y + 240) / 8);
		}
		else
		{
			charger_ligne_horizontale(((*PPU_CTRL_VAR) & (unsigned char)0x03), (*SCROLL_Y) / 8, (*SCROLL_X) / 8, camera_x / 8, camera_y / 8);
		}
	}

	return sav - pixels;
}

unsigned char est_bloquee_gauche()
{
	return (camera_x == 0);
}

unsigned char est_bloquee_droite()
{
	return (camera_x == 8 * taille_x_niveau_courant() - 256);
}

/*
void set_scrolling(unsigned char x, unsigned char y)
{
	*SCROLL_X = x;
	*SCROLL_Y = y;
}

void set_scrolling_x(unsigned char x)
{
	*SCROLL_X = x;
}

void set_scrolling_y(unsigned char y)
{
	*SCROLL_Y = y;
}

void change_scrolling_x(signed char diff)
{
	(*OLD_SCROLL) = (*SCROLL_X);
	(*SCROLL_X) += diff;

	// Les parenthèses sont obligatoires parce que ce vieux cc65 ne gère pas les priorités d'opérateurs.
	if ((diff > 0 && (*OLD_SCROLL) > (*SCROLL_X)) || (diff < 0 && (unsigned char)-diff > (*OLD_SCROLL)))
		(*PPU_CTRL_VAR) ^= 0x01; // Inverse le dernier bit de ce registre pour changer de Nametable : on est arrivé au bout de l'autre.
}

void change_scrolling_y(signed char diff)
{
	(*OLD_SCROLL) = (*SCROLL_Y);
	(*SCROLL_Y) += diff;

	// L'écran de la NES ne fait que 240 pixels en hauteur, le controle de l'inversion de la nametable est donc plus compliqué.
	if (diff > 0 && ((*OLD_SCROLL) > (*SCROLL_Y) || (*SCROLL_Y) > 240))
	{
		(*SCROLL_Y) += 16;
		(*PPU_CTRL_VAR) ^= 0x02;
		// Inverse le penultième bit de ce registre pour changer de Nametable : on est arrivé au bout de l'autre.
	}
	else if (diff < 0 && ((unsigned char)-diff) > (*OLD_SCROLL))
	{
		(*SCROLL_Y) -= 16;
		(*PPU_CTRL_VAR) ^= 0x02;
		// Inverse le penultième bit de ce registre pour changer de Nametable : on est arrivé au bout de l'autre.
	}
}
*/
