#define MANETTE_1_3 (unsigned char*)0x4016
#define MANETTE_2_4 (unsigned char*)0x4017

#define BOUTON_A      0x80
#define BOUTON_B      0x40
#define BOUTON_SELECT 0x20
#define BOUTON_START  0x10
#define BOUTON_HAUT   0x08
#define BOUTON_BAS    0x04
#define BOUTON_GAUCHE 0x02
#define BOUTON_DROITE 0x01

unsigned char manettes[5];

static void fetch_manette(unsigned char* manette, unsigned char* registre)
{
	unsigned char i = 0;
	unsigned char tmp = 0;

	*manette = 0;
	for (i = 0; i < 8; i++)
	{
		tmp = *registre;
		*manette = ((*manette) << 2) + (tmp & 0x01);
	}
}

void update_manettes()
{
	*(MANETTE_1_3) = 1;
	*(MANETTE_1_3) = 0;
	fetch_manette(manettes + 1, MANETTE_1_3);
	fetch_manette(manettes + 3, MANETTE_1_3);
		
	*(MANETTE_2_4) = 1;
	*(MANETTE_2_4) = 0;
	fetch_manette(manettes + 2, MANETTE_2_4);
	fetch_manette(manettes + 4, MANETTE_2_4);
}

unsigned char bouton_a(unsigned char joueur)
{
	return (manettes[joueur] & BOUTON_A);
}

unsigned char bouton_b(unsigned char joueur)
{
	return (manettes[joueur] & BOUTON_B);
}

unsigned char bouton_select(unsigned char joueur)
{
	return (manettes[joueur] & BOUTON_SELECT);
}

unsigned char bouton_start(unsigned char joueur)
{
	return (manettes[joueur] & BOUTON_START);
}

unsigned char bouton_haut(unsigned char joueur)
{
	return (manettes[joueur] & BOUTON_HAUT);
}

unsigned char bouton_bas(unsigned char joueur)
{
	return (manettes[joueur] & BOUTON_BAS);
}

unsigned char bouton_gauche(unsigned char joueur)
{
	return (manettes[joueur] & BOUTON_GAUCHE);
}

unsigned char bouton_droite(unsigned char joueur)
{
	return (manettes[joueur] & BOUTON_DROITE);
}
