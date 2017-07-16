#include <tiles.h>
#include <messages.h>
#include <sprites.h>
#include <manette.h>
#include <palette.h>
#include <avatar.h>
#include <musique.h>
#include <physique.h>
#include <moteur.h>

void main(void)
{

	initialiser();

	changer_animation(&G_Jolivet, 1);

    while(1)
	{
		moteur_mode_jeu();
	}
}
