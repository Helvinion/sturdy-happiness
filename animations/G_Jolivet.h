#ifndef G_JOLIVET_H
#define G_JOLIVET_H

/* POSITON DEBOUT 
static const struct partie_personnage G_Jolivet_debout_tab[] =
{
	{0, -11, 0x00},
	{0, 0,   0x01},
	{0, 8,   0x11},
	{0, 16,  0x21},
	{0, 24,  0x31}
};
*/
static const struct partie_personnage G_Jolivet_debout_tab[] =
{
	{-5, -11, 0x00, 0},
	{-5, 0,   0x01, 1},
	{-8, 8,   25, 2},
	{0, 8,    26, 2},
	{-8, 16,  41, 2},
	{0, 16,   42, 2},
	{-8, 24,  57, 2},
	{0, 24,   58, 2}
};

static const struct partie_personnage G_Jolivet_marche_1_tab[] =
{
	{-5, -11, 0x00, 0},
	{-5, 0,   0x01, 1},
	{-8, 8,   25,   2},
	{0,  8,   26,   2},
	{-8, 16,  0x2B, 2},
	{0,  16,  0x2C, 2},
	{-8, 24,  0x3B, 2},
	{0,  24,  0x3C, 2}
};

static const struct partie_personnage G_Jolivet_marche_2_tab[] =
{
	{-5, -11, 0x00, 0},
	{-5, 0,   0x01, 1},
	{-8, 8,   25,   2},
	{0,  8,   26,   2},
	{-5, 16,  0x2D, 2},
	{-5, 24,  0x3D, 2}
};

static const struct partie_personnage G_Jolivet_marche_3_tab[] =
{
	{-5, -11, 0x00, 0},
	{-5, 0,   0x01, 1},
	{-8, 8,   25,   2},
	{0,  8,   26,   2},
	{-8, 16,  0x2E, 2},
	{0,  16,  0x2F, 2},
	{-9, 24,  0x3E, 2},
	{-1,  24,  0x3F, 2}
};
/*
static const struct partie_personnage G_Jolivet_marche_4_tab[] =
{
	{0, -11, 0x00, 0},
	{0, 0,   0x01, 0},
	{-1, 8,  0x12, 0},
	{0, 16,  0x24, 0},
	{2, 16,  0x25, 0},
	{0, 24,  0x34, 0},
	{2, 24,  0x35, 0}
};
*/
static const struct personnage_graphique G_Jolivet_debout[] =
{
	{
		G_Jolivet_debout_tab,
		8
	}
};

static const struct personnage_graphique G_Jolivet_marche[] =
{
	{
		G_Jolivet_marche_1_tab,
		8
	},	
	{
		G_Jolivet_marche_2_tab,
		6
	},
	{
		G_Jolivet_marche_3_tab,
		8
	},
	{
		G_Jolivet_marche_2_tab,
		6
	},
};

static const struct animation G_Jolivet_animations[] = 
{
	{
		G_Jolivet_debout,
		1
	},
	{
		G_Jolivet_marche,
		4
	}
};

#endif