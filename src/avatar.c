#include <avatar.h>

#include <sprites.h>

void afficher_personnage(unsigned char x, unsigned char y, struct personnage_graphique* perso)
{
	unsigned char i = 0;
	
	while (i < perso->taille_parties)
	{
		add_sprite(perso->parties[i].sprite_id, x + perso->parties[i].delta_x, y + perso->parties[i].delta_y, 0);
		i++;
	}
}