#include <musique.h>

struct etape_musique
{
	unsigned char registre; // Régistre mémoire ou écrire la valeur
	unsigned char delai;     // Délai (par rapport à l'étape précédente) à attendre (PAL 50 pfs)
    unsigned char valeur;    // Valeur à assigner au registre 
};

unsigned char bip_bip[] = {0x00, 50, 0x4f, 
                           0x01, 0, 0x9a, 
						   0x02, 0, 0xeb, 
						   0x03, 0, 0x80, 
						   0xff, 0, 0};


static struct etape_musique **musique = (void*)0x03;         // Stocke l'adresse du début de la musique en cours, changer pour changer de musique
static struct etape_musique **etape_courante = (void*)0x05;  // Socker l'adresse de l'étape actuelle, incrémenter 50 fois par seconde (en PAL)
static unsigned char         *delai_actuel = (void*)0x07;

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


void jouer_musique()
{
	*musique = (struct etape_musique*)bip_bip;
	*etape_courante = (struct etape_musique*)bip_bip;
	*delai_actuel = 0;
}
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