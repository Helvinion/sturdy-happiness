#ifndef G_JOLIVET_H
#define G_JOLIVET_H

/* POSITON DEBOUT */
static const struct partie_personnage G_Jolivet_debout_tab[] =
{
	{0, -11, 0x00},
	{0, 0,   0x01},
	{0, 8,   0x11},
	{0, 16,  0x21},
	{0, 24,  0x31}
};

static const struct partie_personnage G_Jolivet_marche_1_tab[] =
{
	{0, -11, 0x00},
	{0, 0,   0x01},
	{0, 8,   0x11},
	{0, 16,  0x22},
	{0, 24,  0x32},
	{-8, 24, 0x10}
};

static const struct partie_personnage G_Jolivet_marche_2_tab[] =
{
	{0, -11, 0x00},
	{0, 0,   0x01},
	{0, 8,   0x11},
	{2, 16,  0x30},
	{2, 24,  0x40},
};

static const struct partie_personnage G_Jolivet_marche_3_tab[] =
{
	{0, -11, 0x00},
	{0, 0,   0x01},
	{-1, 8,  0x12},
	{0, 16,  0x23},
	{0, 16,  0x20},
	{0, 24,  0x33},
	{-8, 24, 0x10}	
};

static const struct partie_personnage G_Jolivet_marche_4_tab[] =
{
	{0, -11, 0x00},
	{0, 0,   0x01},
	{-1, 8,  0x12},
	{0, 16,  0x24},
	{2, 16,  0x25},
	{0, 24,  0x34},
	{2, 24,  0x35}
};

static const struct personnage_graphique G_Jolivet_debout[] =
{
	{
		G_Jolivet_debout_tab,
		5
	}
};

static const struct personnage_graphique G_Jolivet_marche[] =
{
	{
		G_Jolivet_marche_1_tab,
		6
	},	
	{
		G_Jolivet_marche_2_tab,
		5
	},
	{
		G_Jolivet_marche_3_tab,
		7
	},
	{
		G_Jolivet_marche_4_tab,
		7
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

struct avatar G_Jolivet = {100, 100, {G_Jolivet_animations, 2}, 0, 0};

#endif