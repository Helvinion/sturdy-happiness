#include <messages.h>
#include <tiles.h>

static const char *personnages[] =
{
	"Erreur",
	"Didacticiel"
	"Erreur",
};

static const char* liste_messages[][4] =
{
	{"     Erreur 1   ", "Texte non trouvé", "       ...      ", "     Désolé     "},
	{"  Pour fermer   ", "  ce message,   ", "  appuyez sur   ", "    A ou B.     "},
	{"     Erreur 2   ", "Texte non trouvé", "       ...      ", "     Désolé     "},
};

static unsigned char statut_courant;
static unsigned char ligne_courante;     // Ligne d'affichage demandée
static unsigned char colonne_courante;   // Colonne d'affichage demandée
static unsigned char personnage_courant;
static unsigned char message_courant;

void messages_afficher(unsigned char perso, unsigned char message, unsigned char l, unsigned char c)
{
	if (statut_courant == 0)
	{
		ligne_courante = l;
		colonne_courante = c;
		personnage_courant = perso;
		message_courant = message;
		statut_courant = 1;
	}
}

void messages_update()
{
	if (statut_courant != 0)
	{
		tiles_add_group_horizontal(ligne_courante, colonne_courante, liste_messages[message_courant][statut_courant - 1]);
		tiles_commit_groups();
		statut_courant++;
		ligne_courante++;
	}
	if (statut_courant == 5)
		statut_courant = 0;
}