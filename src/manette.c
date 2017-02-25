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

#define TAILLE_HISTORIQUE 16

struct manette_joueur
{
	// Liste des TAILLE_HISTORIQUE dernières combinaisons de touches pressées
	unsigned char historique[TAILLE_HISTORIQUE];
	// Index de la prochaine écriture.
	unsigned char index_actuel;
	// Indique si les touches étaient relachées à la dernière vérification.
	unsigned char relachee;
};

static struct manette_joueur manettes[4];

// Les codes sont marques à l'envers parce qu'on remonte l'historique de leur appui
unsigned char konami_code[] = {BOUTON_START, BOUTON_A, BOUTON_B, BOUTON_DROITE, BOUTON_GAUCHE, BOUTON_DROITE, BOUTON_GAUCHE, BOUTON_BAS, BOUTON_BAS, BOUTON_HAUT, BOUTON_HAUT};



// Indique quelle a été la nieme dernière combinaison de touches

static unsigned char chercher_historique(unsigned char joueur, unsigned char n)
{
	struct manette_joueur *manette = manettes + (joueur - 1);
	unsigned char index = manette->index_actuel;
	
	if (index < n)
		index = index + TAILLE_HISTORIQUE;
	
	index = index - 1 - n;

	return manette->historique[index];
}

static unsigned char fetch_manette(unsigned char* registre)
{
	unsigned char res = 0;
	// Lit 8 fois le registre approprié pour récupérer le statut des 8 boutons
	
	res = (res << 1) + (*registre & 0x01);
	res = (res << 1) + (*registre & 0x01);
	res = (res << 1) + (*registre & 0x01);
	res = (res << 1) + (*registre & 0x01);
	
	res = (res << 1) + (*registre & 0x01);
	res = (res << 1) + (*registre & 0x01);
	res = (res << 1) + (*registre & 0x01);
	res = (res << 1) + (*registre & 0x01);
		
	return res;
}

static void ajouter_historique(unsigned char joueur, unsigned char combinaison)
{
	struct manette_joueur* manette = manettes + (joueur - 1);
	
	if (combinaison == 0) // Aucune touche pressee
	{
		// Ne rien ajouter si aucune touche n'a été préssée
		// En revanche, le signaler pour la prochaine fois.
		manette->relachee = 1;
		return;
	}
	else if (manette->relachee || combinaison != chercher_historique(joueur, 0))
	{
		// N'ajouter la combinaison enregistree que si elle est différente de la précédente
		// Ou si le pad a été relaché depuis.
		manette->relachee = 0;
		
		manette->historique[manette->index_actuel] = combinaison;

		// Incrémente l'index et le remet à 0 si nécéssaire.
		manette->index_actuel++;
		if (manette->index_actuel >= TAILLE_HISTORIQUE)
			manette->index_actuel = 0;
	}	
}

void update_manettes()
{
	unsigned char combinaison;

	*(MANETTE_1_3) = 0;
	*(MANETTE_2_4) = 0;
	
	combinaison = fetch_manette(MANETTE_1_3);
	ajouter_historique(1, combinaison);

	combinaison = fetch_manette(MANETTE_2_4);
	ajouter_historique(2, combinaison);

	combinaison = fetch_manette(MANETTE_1_3);		
	ajouter_historique(3, combinaison);	
	
	combinaison = fetch_manette(MANETTE_2_4);
	ajouter_historique(4, combinaison);
	
	*(MANETTE_1_3) = 1;
	*(MANETTE_2_4) = 1;
}

// Indique si le code Konami a été entré par un joueur.
unsigned char triche_konami(unsigned char joueur)
{
	unsigned char i = 0;
	const unsigned char taille = 3;
	// Contient le konami code a l'envers parce qu'on
	// Le vérifie dans les sens inverse.
	unsigned char code[] =
	{BOUTON_START, BOUTON_A, BOUTON_B,
     BOUTON_DROITE, BOUTON_GAUCHE, BOUTON_DROITE, BOUTON_GAUCHE,
	 BOUTON_BAS, BOUTON_BAS, BOUTON_HAUT, BOUTON_HAUT}/**/;
	 
	 while (i < taille && chercher_historique(joueur, i) == code[i])
		i++;
	
	// Si i == taille, c'est qu'on est arrivé en fin de boucle et donc que le konami code est OK.
	if (i == taille)
		return 1;
	else
		return 0;
}

unsigned char bouton_a(unsigned char joueur)
{
	return (!manettes[joueur - 1].relachee) && (chercher_historique(joueur, 0) & BOUTON_A);
}

unsigned char bouton_b(unsigned char joueur)
{
	return (!manettes[joueur - 1].relachee) && (chercher_historique(joueur, 0) & BOUTON_B);
}

unsigned char bouton_select(unsigned char joueur)
{
	return (!manettes[joueur - 1].relachee) && (chercher_historique(joueur, 0) & BOUTON_SELECT);
}

unsigned char bouton_start(unsigned char joueur)
{
	return (!manettes[joueur - 1].relachee) && (chercher_historique(joueur, 0) & BOUTON_START);
}

unsigned char bouton_haut(unsigned char joueur)
{
	return (!manettes[joueur - 1].relachee) && (chercher_historique(joueur, 0) & BOUTON_HAUT);
}

unsigned char bouton_bas(unsigned char joueur)
{
	return (!manettes[joueur - 1].relachee) && (chercher_historique(joueur, 0) & BOUTON_BAS);
}

unsigned char bouton_gauche(unsigned char joueur)
{
	return (!manettes[joueur - 1].relachee) && (chercher_historique(joueur, 0) & BOUTON_GAUCHE);
}

unsigned char bouton_droite(unsigned char joueur)
{
	return (!manettes[joueur - 1].relachee) && (chercher_historique(joueur, 0) & BOUTON_DROITE);
}
