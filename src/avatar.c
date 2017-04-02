#include <avatar.h>

#include <sprites.h>

void afficher_personnage(unsigned char x, unsigned char y, const struct personnage_graphique* const perso)
{
	unsigned char i = 0;
	
	while (i < perso->taille_parties)
	{
		add_sprite(perso->parties[i].sprite_id, x + perso->parties[i].delta_x, y + perso->parties[i].delta_y, 0);
		i++;
	}
}

void afficher_personnage_2(const struct avatar *perso)
{
	unsigned char i = 0;
	// Alia pour acceder à l'étape courante de l'animation courante
	const struct personnage_graphique *tmp = &(perso->anims.anims[perso->animation_courante].anim[perso->etape_anim]);
	
	while (i < tmp->taille_parties)
	{
		add_sprite(tmp->parties[i].sprite_id,
				   perso->x + tmp->parties[i].delta_x,
				   perso->y + tmp->parties[i].delta_y,
				   0);
		i++;
	}
}
