#ifndef AVATAR_H
#define AVATAR_H

struct partie_personnage
{
	const signed char delta_x;      // Distance en X de la coordonnée du personnage
	const signed char delta_y;      // Distance en y de la coordonnée du personnage
	const unsigned char sprite_id;  // Dessin de la, partie de personnage
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


#define G_Jolivet_debout_curseur {0, -11, 0x00}
#define G_Jolivet_debout_tete    {0, 0,   0x01}
#define G_Jolivet_debout_tronc   {0, 8,   0x11}
#define G_Jolivet_debout_bassin  {0, 16,  0x21}
#define G_Jolivet_debout_pieds   {0, 24,  0x31}
static const struct partie_personnage G_Jolivet_debout_tab[5] =
{
	G_Jolivet_debout_curseur,
	G_Jolivet_debout_tete,
	G_Jolivet_debout_tronc,
	G_Jolivet_debout_bassin,
	G_Jolivet_debout_pieds
};

static const struct personnage_graphique G_Jolivet_postures[1] =
{
	{
		G_Jolivet_debout_tab,
		5
	}
};

static const struct animation G_Jolivet_animations[1] = 
{
	{
		G_Jolivet_postures,
		1
	}
};

struct avatar G_Jolivet = {100, 100, {G_Jolivet_animations, 1}, 0, 0};

void afficher_personnage(unsigned char x, unsigned char y, const struct personnage_graphique* const perso);

void afficher_personnage_2(const struct avatar *perso);

#undef G_Jolivet_debout_curseur
#undef G_Jolivet_debout_tete
#undef G_Jolivet_debout_tronc
#undef G_Jolivet_debout_bassin
#undef G_Jolivet_debout_pieds


#endif