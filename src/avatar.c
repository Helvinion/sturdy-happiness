#include <avatar.h>

#include <sprites.h>

void afficher_personnage(const struct avatar *perso)
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

void animer(struct avatar *perso)
{
	perso->etape_anim++;
	
	if (perso->etape_anim == perso->anims.anims[perso->animation_courante].taille_anim)
		perso->etape_anim = 0;
}

void changer_animation(struct avatar *perso, unsigned char anim)
{
	if (perso->animation_courante != anim)
	{
		perso->animation_courante = anim;
		perso->etape_anim = 0;
	}
}
