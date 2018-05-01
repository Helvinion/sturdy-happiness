#include <musique.h>

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
    unsigned char registre; // Registre mémoire où écrire la valeur
    unsigned char delai;     // Délai (par rapport à l'étape précédente) à attendre (PAL 50 fps)
    unsigned char valeur;    // Valeur à assigner au registre
};

unsigned char bip_bip[] =
{
    0x00, 50, 0x4f,     0x01, 0, 0x9a,      0x02, 0, 0xeb,      0x03, 0, 0x80,
    0xff, 0, 0
};

unsigned char bip_bip2[] =
{
    0x00, 50, 0xef,     0x01, 0, 0x9a,      0x02, 0, 0xeb,      0x03, 0, 0x80,
    0x00, 20, 0x4f,     0x01, 0, 0x97,      0x02, 0, 0xeb,      0x03, 0, 0x80,
    0x00, 20, 0x4f,     0x01, 0, 0x96,      0x02, 0, 0xeb,      0x03, 0, 0x80,
    0x00, 20, 0x4f,     0x01, 0, 0x95,      0x02, 0, 0xeb,      0x03, 0, 0x80,
    0x00, 20, 0x4f,     0x01, 0, 0x94,      0x02, 0, 0xeb,      0x03, 0, 0x80,
    0x00, 20, 0x4f,     0x01, 0, 0x93,      0x02, 0, 0xeb,      0x03, 0, 0x80,
    0x00, 20, 0x4f,     0x01, 0, 0x92,      0x02, 0, 0xeb,      0x03, 0, 0x80,
    0x00, 20, 0x4f,     0x01, 0, 0x91,      0x02, 0, 0xeb,      0x03, 0, 0x80,
    0x00, 20, 0x4f,     0x01, 0, 0x90,      0x02, 0, 0xeb,      0x03, 0, 0x80,
    0xff, 0, 0
};

unsigned char bip_bip3[] =
{
    0x00, 50, 0xef,     0x01, 0, 0x9a,      0x02, 0, 0xeb,      0x03, 0, 0x80,
    0x00, 20, 0x4f,     0x01, 0, 0x96,      0x02, 0, 0xeb,      0x03, 0, 0x00,
    0x00, 20, 0x4f,     0x01, 0, 0x96,      0x02, 0, 0xeb,      0x03, 0, 0x08,
    0x00, 20, 0x4f,     0x01, 0, 0x96,      0x02, 0, 0xeb,      0x03, 0, 0x10,
    0x00, 20, 0x4f,     0x01, 0, 0x96,      0x02, 0, 0xeb,      0x03, 0, 0x18,
    0x00, 20, 0x4f,     0x01, 0, 0x96,      0x02, 0, 0xeb,      0x03, 0, 0x20,
    0x00, 20, 0x4f,     0x01, 0, 0x96,      0x02, 0, 0xeb,      0x03, 0, 0x28,
    0x00, 20, 0x4f,     0x01, 0, 0x96,      0x02, 0, 0xeb,      0x03, 0, 0x30,
    0x00, 20, 0x4f,     0x01, 0, 0x96,      0x02, 0, 0xeb,      0x03, 0, 0x38,
    0xff, 0, 0
};

unsigned char bip_bip4[] =
{
    0x00, 50, 0xbf,     0x01, 0, 0x00,      0x02, 0, 0x17,      0x03, 0, 0xf9,
    0x00, 50, 0xbf,     0x01, 0, 0x00,      0x02, 0, 0x8b,      0x03, 0, 0xf8,
    0xff, 0, 0
};

static struct etape_musique **musique           = ZP_ADR_MUS;      // Stocke l'adresse du début de la musique en cours, changer pour changer de musique
static struct etape_musique **etape_courante    = ZP_ADR_MUS_CUR;  // Socker l'adresse de l'étape actuelle, incrémenter 50 fois par seconde (en PAL)
static unsigned char         *delai_actuel      = ZP_MUS_CMPT;

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

#if 0
char mus[] = {
    IDX_LA, -2,
    IDX_DO, -2,
    IDX_MI, -2,
    IDX_LA, -1,
    IDX_DO, -1,
    IDX_MI, -1,
    IDX_LA,  0,
    IDX_DO,  0,
//    IDX_MI,  0,
//    IDX_LA,  1,
//    IDX_DO,  1,
//    IDX_MI,  1,
//    IDX_LA,  2,
//    IDX_DO,  2,
//    IDX_MI,  2,
//    IDX_LA,        3,
//    IDX_DO,        3,
//    IDX_MI,        3,
//    IDX_LA,        4,
//    IDX_DO,        4,
//    IDX_MI,        4,
//    IDX_DO,        4,
//    IDX_LA,        4,
//    IDX_MI,        3,
//    IDX_DO,        3,
//    IDX_LA,        3,
//    IDX_MI,  2,
//    IDX_DO,  2,
//    IDX_LA,  2,
//    IDX_MI,  1,
//    IDX_DO,  1,
//    IDX_LA,  1,
    IDX_MI,  0,
    IDX_DO,  0,
    IDX_LA,  0,
    IDX_MI, -1,
    IDX_DO, -1,
    IDX_LA, -1,
    IDX_MI, -2,
    IDX_DO, -2,
    //IDX_LA, -2,

    IDX_END,    0
};
#elif 1
char mus[] = {
    IDX_DO, -2,
    IDX_RE, -2,
    IDX_MI, -2,
    IDX_SOL, -2,
    IDX_MI, -2,
    IDX_RE, -2,

    IDX_END,    0
};
#else
char mus[] = {
    IDX_LA,		-1,
    IDX_LAD,	-1,
    IDX_SI,		-1,
    IDX_DO,		-1,
    IDX_DOD,	-1,
    IDX_RE,		-1,
    IDX_RED,	-1,
    IDX_MI,		-1,
    IDX_FA,		-1,
    IDX_FAD,	-1,
    IDX_SOL,	-1,
    IDX_SOLD,	-1,
    IDX_LA,		0,
    IDX_LAD,	0,
    IDX_SI,		0,
    IDX_DO,		0,
    IDX_DOD,	0,
    IDX_RE,		0,
    IDX_RED,	0,
    IDX_MI,		0,
    IDX_FA,		0,
    IDX_FAD,	0,
    IDX_SOL,	0,
    IDX_SOLD,	0,

    IDX_END,	0
};
#endif

#define PARTITION_SIZE 7

unsigned char partition[12 * PARTITION_SIZE + 3] =
{
    0x00, 50, 0xbf,     0x01, 0, 0x00,      0x02, 0, 0x17,      0x03, 0, 0xf9,
    0xff,  0, 0x00
};

static char const *m = mus;
char variation;
void change_variation(char i)
{
    char tmp = variation + i;

    if (tmp >= 1)
        variation = tmp;
}

void init_musique()
{
    unsigned char *p = partition;
    unsigned short note;
    signed char vnote;
    signed char hauteur;
    int i;

    variation = 1;

    *musique = (struct etape_musique*)partition;
    *etape_courante = (struct etape_musique*)partition;
    *delai_actuel = 0;

    for (i = 0; i < PARTITION_SIZE; ++i)
    {
        p[0]  = 0x00; p[1]  =   variation; p[2]  = 0xbf;
        p[3]  = 0x01; p[4]  =           0; p[5]  = 0x00;
        p[6]  = 0x02; p[7]  =           0; //p[8]  = note & 0xff;
        p[9]  = 0x03; p[10] =           0; //p[11] = 0xf8 + ((note >> 8) & 0xff);
        p += 12;
    }
    p[0] = 0xff; p[1] = 50; p[2] = 0x00;

    if (*mus == IDX_END)
    {
        partition[0] = 0xff;
        return;
    }

    p = partition;

    for (i = 0; i < PARTITION_SIZE; ++i)
    {
        if (*m == IDX_END)
        {
            m = mus;
        }

        vnote = m[0];
        hauteur = m[1];

        if (hauteur > 0)
        {
            note = (notes[vnote] >> hauteur) - 1;
        }
        else if (hauteur < 0)
        {
            note = (notes[vnote] << -hauteur) - 1;
        }
        else
        {
            note = (notes[vnote]) - 1;
        }

        m+=2;
        p[8]  = note & 0xff;
        p[11] = 0xf8 + ((note >> 8) & 0xff);
        p += 12;
    }
}

// TODO: fct transpose

#if 1
void jouer_musique()
{
    static int carry = 0;
    static char *oldcur = (char*)0;
    char *newcur;

    static unsigned int pindex = 0;
    static unsigned char *p = partition;
    static unsigned char *ptmp = partition;
    unsigned short note;
    signed char vnote;
    signed char hauteur;
    static char transpose = 0;
    static char n = 1;
    char i = 0;

    if (*mus == IDX_END)
    {
        partition[0] = 0xff;
        return;
    }

    newcur =  *((char**)ZP_ADR_MUS_CUR);
    if (oldcur > newcur)
    {
        carry = 1;
    }
    oldcur = newcur;

    //if ((char*)p <= (char*)*etape_courante)
    if ((char*)p >= newcur && !carry)
    {
        return;
    }

    if (*m == IDX_END)
    {
        transpose += n;
        if (transpose == 0)
            n = 1;
        if (transpose == 11)
            n = -1;
        //transpose %= 12;

        m = mus;
    }

    vnote = ((m[0] - 1 + transpose) % 12) + 1;
    hauteur = m[1] + (vnote < m[0] ? 1 : 0);

    if (hauteur > 0)
    {
        note = (notes[vnote] >> hauteur) - 1;
    }
    else if (hauteur < 0)
    {
        note = (notes[vnote] << -hauteur) - 1;
    }
    else
    {
        note = (notes[vnote]) - 1;
    }

    m+=2;
    p[1]  = variation;
    p[8]  = note & 0xff;
    p[11] = 0xf8 + ((note >> 8) & 0xff);
    p += 12;
    pindex++;
    if (pindex == PARTITION_SIZE)
    {
        pindex = 0;
        p = partition;
        carry = 0;
    }

    ptmp = partition;
    for (i = 0; i < PARTITION_SIZE; ++i)
    {
        ptmp[1] = variation;
        ptmp += 12;
    }

}
// TODO: etape_courante: en faire offset et pas un pointeur ?
#else
void jouer_musique()
{
    *musique = (struct etape_musique*)bip_bip;
    *etape_courante = (struct etape_musique*)bip_bip;
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
