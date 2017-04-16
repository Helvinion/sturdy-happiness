#ifndef MUSIQUE_H
# define MUSIQUE_H

struct CanalCarre
{
	char reg_1;
	char reg_2;
	char reg_3;
	char reg_4;
};

struct CanalTriangle
{
	char reg_1;
	char reg_2;
	char reg_3;
};

struct CanalBruit
{
	char reg_1;
	char reg_2;
	char reg_3;
};

void jouer_son_carre_1(struct CanalCarre* son);
void jouer_son_carre_2(struct CanalCarre* son);

void jouer_son_triangle(struct CanalTriangle* son);

void jouer_son_bruit(struct CanalBruit* son);

void jouer_musique();

#endif