#include <musique.h>

#define FREQ_PROC	111860800

#define IDX_END		0
#define IDX_LA		1
#define IDX_LAD		2
#define IDX_SIB		2
#define IDX_SI		3
#define IDX_DO		4
#define IDX_DOD		5
#define IDX_REB		5
#define IDX_RE		6
#define IDX_RED		7
#define IDX_MIB		7
#define IDX_MI		8
#define IDX_FA		9
#define IDX_FAD		10
#define IDX_SOLB	10
#define IDX_SOL		11
#define IDX_SOLD	12
#define IDX_LAB		12

#define FREQ_LA 	440000
#define FREQ_LAD	466164
#define FREQ_SIB 	FREQ_LAD
#define FREQ_SI		493883
#define FREQ_DO		523251
#define FREQ_DOD	554365
#define FREQ_REB	FREQ_DOD
#define FREQ_RE		587330
#define FREQ_RED	622254
#define FREQ_MIB	FREQ_RED
#define FREQ_MI		659255
#define FREQ_FA		698456
#define FREQ_FAD	739989
#define FREQ_SOLB	FREQ_FAD
#define FREQ_SOL	783991
#define FREQ_SOLD	830609
#define FREQ_LAB	FREQ_SOLD

// TODO faire -1 sur ce res
#define PERIOD_LA	(FREQ_PROC / FREQ_LA)
#define PERIOD_LAD	(FREQ_PROC / FREQ_LAD)
#define PERIOD_SIB	(FREQ_PROC / FREQ_SIB)
#define PERIOD_SI	(FREQ_PROC / FREQ_SI)
#define PERIOD_DO	(FREQ_PROC / FREQ_DO)
#define PERIOD_DOD	(FREQ_PROC / FREQ_DOD)
#define PERIOD_REB	(FREQ_PROC / FREQ_REB)
#define PERIOD_RE	(FREQ_PROC / FREQ_RE)
#define PERIOD_RED	(FREQ_PROC / FREQ_RED)
#define PERIOD_MIB	(FREQ_PROC / FREQ_MIB)
#define PERIOD_MI	(FREQ_PROC / FREQ_MI)
#define PERIOD_FA	(FREQ_PROC / FREQ_FA)
#define PERIOD_FAD	(FREQ_PROC / FREQ_FAD)
#define PERIOD_SOLB	(FREQ_PROC / FREQ_SOLB)
#define PERIOD_SOL	(FREQ_PROC / FREQ_SOL)
#define PERIOD_SOLD	(FREQ_PROC / FREQ_SOLD)
#define PERIOD_LAB	(FREQ_PROC / FREQ_LAB)

unsigned short notes[13] =
{
	0,
	PERIOD_LA,
	PERIOD_LAD,
	PERIOD_SI,
	PERIOD_DO,
	PERIOD_DOD,
	PERIOD_RE,
	PERIOD_RED,
	PERIOD_MI,
	PERIOD_FA,
	PERIOD_FAD,
	PERIOD_SOL,
	PERIOD_SOLD
};

struct etape_musique
{
	unsigned char registre; // Régistre mémoire ou écrire la valeur
	unsigned char delai;     // Délai (par rapport à l'étape précédente) à attendre (PAL 50 fps)
    unsigned char valeur;    // Valeur à assigner au registre
};

unsigned char bip_bip[] = {0x00, 50, 0x4f,
                           0x01, 0, 0x9a,
						   0x02, 0, 0xeb,
						   0x03, 0, 0x80,
						   0xff, 0, 0};

unsigned char bip_bip2[] =
{
	0x00, 50, 0xef,
	0x01, 0, 0x9a,
	0x02, 0, 0xeb,
	0x03, 0, 0x80,

	0x00, 20, 0x4f,
	0x01, 0, 0x97,
	0x02, 0, 0xeb,
	0x03, 0, 0x80,

	0x00, 20, 0x4f,
	0x01, 0, 0x96,
	0x02, 0, 0xeb,
	0x03, 0, 0x80,

	0x00, 20, 0x4f,
	0x01, 0, 0x95,
	0x02, 0, 0xeb,
	0x03, 0, 0x80,

	0x00, 20, 0x4f,
	0x01, 0, 0x94,
	0x02, 0, 0xeb,
	0x03, 0, 0x80,

	0x00, 20, 0x4f,
	0x01, 0, 0x93,
	0x02, 0, 0xeb,
	0x03, 0, 0x80,

	0x00, 20, 0x4f,
	0x01, 0, 0x92,
	0x02, 0, 0xeb,
	0x03, 0, 0x80,

	0x00, 20, 0x4f,
	0x01, 0, 0x91,
	0x02, 0, 0xeb,
	0x03, 0, 0x80,

	0x00, 20, 0x4f,
	0x01, 0, 0x90,
	0x02, 0, 0xeb,
	0x03, 0, 0x80,

	0xff, 0, 0
};

unsigned char bip_bip3[] =
{
	0x00, 50, 0xef,
	0x01, 0, 0x9a,
	0x02, 0, 0xeb,
	0x03, 0, 0x80,

	0x00, 20, 0x4f,
	0x01, 0, 0x96,
	0x02, 0, 0xeb,
	0x03, 0, 0x00,

	0x00, 20, 0x4f,
	0x01, 0, 0x96,
	0x02, 0, 0xeb,
	0x03, 0, 0x08,

	0x00, 20, 0x4f,
	0x01, 0, 0x96,
	0x02, 0, 0xeb,
	0x03, 0, 0x10,

	0x00, 20, 0x4f,
	0x01, 0, 0x96,
	0x02, 0, 0xeb,
	0x03, 0, 0x18,

	0x00, 20, 0x4f,
	0x01, 0, 0x96,
	0x02, 0, 0xeb,
	0x03, 0, 0x20,

	0x00, 20, 0x4f,
	0x01, 0, 0x96,
	0x02, 0, 0xeb,
	0x03, 0, 0x28,

	0x00, 20, 0x4f,
	0x01, 0, 0x96,
	0x02, 0, 0xeb,
	0x03, 0, 0x30,

	0x00, 20, 0x4f,
	0x01, 0, 0x96,
	0x02, 0, 0xeb,
	0x03, 0, 0x38,

	0xff, 0, 0
};

unsigned char bip_bip4[] =
{
	0x00, 50, 0xbf,
	0x01, 0, 0x00,
	0x02, 0, 0x17,
	0x03, 0, 0xf9,

	0x00, 50, 0xbf,
	0x01, 0, 0x00,
	0x02, 0, 0x8b,
	0x03, 0, 0xf8,

	0xff, 0, 0
};

static struct etape_musique **musique = (void*)0x23;         // Stocke l'adresse du début de la musique en cours, changer pour changer de musique
static struct etape_musique **etape_courante = (void*)0x25;  // Socker l'adresse de l'étape actuelle, incrémenter 50 fois par seconde (en PAL)
static unsigned char         *delai_actuel = (void*)0x27;

void jouer_son_carre_1(struct CanalCarre* son)
{
	*((unsigned char*)0x4000) = son->reg_1;
	*((unsigned char*)0x4001) = son->reg_2;
	*((unsigned char*)0x4002) = son->reg_3;
	*((unsigned char*)0x4003) = son->reg_4;
}

void jouer_son_carre_2(struct CanalCarre* son)
{
	*((unsigned char*)0x4004) = son->reg_1;
	*((unsigned char*)0x4005) = son->reg_2;
	*((unsigned char*)0x4006) = son->reg_3;
	*((unsigned char*)0x4007) = son->reg_4;
}

void jouer_son_triangle(struct CanalTriangle* son)
{
	*((unsigned char*)0x4008) = son->reg_1;
	*((unsigned char*)0x400a) = son->reg_2;
	*((unsigned char*)0x400b) = son->reg_3;
}

void jouer_son_bruit(struct CanalBruit* son)
{
	*((unsigned char*)0x400c) = son->reg_1;
	*((unsigned char*)0x400e) = son->reg_2;
	*((unsigned char*)0x400f) = son->reg_3;
}

#define freq 50

char mus[] = {
	IDX_LA,		-2,
	IDX_DO,		-2,
	IDX_MI,		-2,
	IDX_LA,		-1,
	IDX_DO,		-1,
	IDX_MI,		-1,
	IDX_LA,		0,
	IDX_DO,		0,
	IDX_MI,		0,
	IDX_LA,		1,
	IDX_DO,		1,
	IDX_MI,		1,
	IDX_LA,		2,
	IDX_DO,		2,
	IDX_MI,		2,
	IDX_LA,		3,
	IDX_DO,		3,
	IDX_MI,		3,
	IDX_LA,		4,
	IDX_DO,		4,
	IDX_MI,		4,

	IDX_END,	0
};

unsigned char partition[15] =
{
	0x00, 50, 0xbf,
	0x01, 0, 0x00,
	0x02, 0, 0x17,
	0x03, 0, 0xf9,

	0xff, 0, 0,
};

void jouer_musique()
{
	static char const *m = mus;
	static unsigned char *p = partition;
	unsigned short note;
	signed char vnote;
	signed char hauteur;

	if (*m == IDX_END)
	{
		return;
	}

	vnote = m[0];
	hauteur = m[1];

	if (hauteur > 0)
		note = (notes[vnote] >> hauteur) - 1;
	else if (hauteur < 0)
		note = (notes[vnote] << -hauteur) - 1;
	else
		note = (notes[vnote]) - 1;

	m+=2;
	p[0]  = 0x00; p[1]  = 50; p[2]  = 0xbf;
	p[3]  = 0x01; p[4]  =  0; p[5]  = 0x00;
	p[6]  = 0x02; p[7]  =  0; p[8]  = note & 0xff;
	p[9]  = 0x03; p[10] =  0; p[11] = 0xf8 + ((note >> 8) & 0xff);
	p[12] = 0xff; p[13] =  0; p[14] = 0x00;
	p += 12;
	*musique = (struct etape_musique*)partition;
	*etape_courante = (struct etape_musique*)partition;
	*delai_actuel = 0;
}

#if 0
void jouer_musique()
{
	*musique = (struct etape_musique*)bip_bip4;
	*etape_courante = (struct etape_musique*)bip_bip4;
	*delai_actuel = 0;
}
#endif

/*
// Fonction appellée à chaque IRQ. Joue le son courant si cela est nécéssaire
void irq_musique()
{
	while (delai_actuel == etape_courante->delai)
	{
		// Le délai est expiré, on joue la note.
		*(etape_courante->registre) = etape_courante->valeur;

		delai_actuel = 0; // Remise à 0 du délai
		etape_courante++; // Passage à l'étape suivante

		if (etape_courante->registre == 0x00)
			etape_courante = musique;   // Si la musique est terminée, on repasse au début
	}

	delai_actuel++;
}
*/
