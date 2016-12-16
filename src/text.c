#define PPUADDR (unsigned char*)0x2006
#define PPUDATA (unsigned char*)0x2007

#define TO_PPU_ADDR(LINE, COL) (((short int)(LINE) << 5) + (COL) + 0x2000)
#define PUT_PPU(BYTE) (*PPUADDR) = (BYYE)

enum
{
    INACTIF,
    BORDURE_DESSUS,
    TEXTE_1,
    TEXTE_2,
    TEXTE_3,
    TEXTE_4,
    BORDURE_DESSOUS,
    FIN
};


static const char* texte = 0x000;
static const char* nom_perso;
static char a_faire = INACTIF;
static char line = 0;
static char col = 0;

static void set_ppu_addr()
{
  // L'écran fait 32 * 32 cases.
  // L'index final est donc line * 32 + col
  unsigned short int ppu_addr = TO_PPU_ADDR(line, col);
  (*PPUADDR) = (unsigned char)(ppu_addr >> 8);
  (*PPUADDR) = (unsigned char)(ppu_addr);
}

static void bordure_haute()
{
  set_ppu_addr(); // positionne le curseur
  
  (*PPUDATA) = 0x10; // Coin supérieur gauche
  asm("lda #$14\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n"
      "sta $2007\n");
  (*PPUDATA) = 0x11; // Coin supérieur droit
  
  line++;
}

static void bordure_basse()
{
}

/* Ecrit le contenu de texte jusuqu'a un retour à la ligne
   ou jusqu'au 16e caractère inclu.
   Renvoie le nombre de caractères écrits
*/
static char ecrire_ligne()
{
  char ret;
  char i;
    
  set_ppu_addr(); // positionne le curseur
    
  (*PPUDATA) = 0x15; // Bordure verticale
  
  i = 0;
  while (i < 16)
  {
    (*PPUDATA) = *texte;
    texte++;
    i++;
  }
    /*
  for (i = 0; i < 16 && (*texte) != '\n' && (*texte) != '\0'; i++, texte++)
    (*PPUDATA) = (*texte);
    
  if (i != 16)
  {
    // On a rencontré un '\n' ou un '\0', on doit finir la ligne
    ret = i - 1;
    
    for (i; i < 16; i++)
      (*PPUDATA) = ' ';
    
    if ((*texte) == '\n') // Si on a rencontré un '\n' il faut passer le caractere.
        texte++;
  }
  else
    ret = 16;
       */
  (*PPUDATA) = 0x15; // Bordure verticale*/
  line++;
  return ret;
}

void afficher_texte(const char* perso, const char* a_ecrire)
{
    // On affiche 64 caractères sur 4 lignes de 16 caractères entourés
    // Par une bordure.
    line = 4;
    col = 4;
    nom_perso = perso;
    texte = a_ecrire;
    a_faire = BORDURE_DESSUS;
    return;
}

void maj_texte()
{
    switch(a_faire)
    {
        case INACTIF:
            return;
        case BORDURE_DESSUS:
            bordure_haute();
            break;
        
        case TEXTE_1:
        case TEXTE_2:
        case TEXTE_3:
        case TEXTE_4:
            ecrire_ligne();
            break;
        case BORDURE_DESSOUS:
            bordure_basse();
            break;
        
    }
    a_faire++;
    if (a_faire == FIN)
        a_faire = INACTIF;
}
