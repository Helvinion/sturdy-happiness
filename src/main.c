#include <avatar.h>
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
