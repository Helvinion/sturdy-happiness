#include <avatar.h>

#include <sprites.h>

void afficher_personnage(const struct avatar *perso)
{
	unsigned char i = 0;

	// Alias pour acceder à l'étape courante de l'animation courante
	const struct personnage_graphique *tmp = &(perso->anims.anims[perso->animation_courante].anim[perso->etape_anim]);
	const struct partie_personnage* partie;
	unsigned char max = tmp->taille_parties;
	
	while (i < max)
	{
		partie = tmp->parties + i;

		add_sprite(partie->sprite_id, perso->x + partie->delta_x, perso->y + partie->delta_y, 0);
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
