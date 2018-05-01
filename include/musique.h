#ifndef MUSIQUE_H
# define MUSIQUE_H

# include "zeropage.h"

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
void init_musique();

# define FREQ_PROC	111860800

# define IDX_END	0
# define IDX_LA		1
# define IDX_LAD	2
# define IDX_SIB	2
# define IDX_SI		3
# define IDX_DO		4
# define IDX_DOD	5
# define IDX_REB	5
# define IDX_RE		6
# define IDX_RED	7
# define IDX_MIB	7
# define IDX_MI		8
# define IDX_FA		9
# define IDX_FAD	10
# define IDX_SOLB	10
# define IDX_SOL	11
# define IDX_SOLD	12
# define IDX_LAB	12

# define FREQ_LA 	440000
# define FREQ_LAD	466164
# define FREQ_SIB 	FREQ_LAD
# define FREQ_SI	493883
# define FREQ_DO	523251
# define FREQ_DOD	554365
# define FREQ_REB	FREQ_DOD
# define FREQ_RE	587330
# define FREQ_RED	622254
# define FREQ_MIB	FREQ_RED
# define FREQ_MI	659255
# define FREQ_FA	698456
# define FREQ_FAD	739989
# define FREQ_SOLB	FREQ_FAD
# define FREQ_SOL	783991
# define FREQ_SOLD	830609
# define FREQ_LAB	FREQ_SOLD

// TODO faire -1 sur ce res
# define PERIOD_LA	(FREQ_PROC / FREQ_LA)
# define PERIOD_LAD	(FREQ_PROC / FREQ_LAD)
# define PERIOD_SIB	(FREQ_PROC / FREQ_SIB)
# define PERIOD_SI	(FREQ_PROC / FREQ_SI)
# define PERIOD_DO	(FREQ_PROC / FREQ_DO)
# define PERIOD_DOD	(FREQ_PROC / FREQ_DOD)
# define PERIOD_REB	(FREQ_PROC / FREQ_REB)
# define PERIOD_RE	(FREQ_PROC / FREQ_RE)
# define PERIOD_RED	(FREQ_PROC / FREQ_RED)
# define PERIOD_MIB	(FREQ_PROC / FREQ_MIB)
# define PERIOD_MI	(FREQ_PROC / FREQ_MI)
# define PERIOD_FA	(FREQ_PROC / FREQ_FA)
# define PERIOD_FAD	(FREQ_PROC / FREQ_FAD)
# define PERIOD_SOLB	(FREQ_PROC / FREQ_SOLB)
# define PERIOD_SOL	(FREQ_PROC / FREQ_SOL)
# define PERIOD_SOLD	(FREQ_PROC / FREQ_SOLD)
# define PERIOD_LAB	(FREQ_PROC / FREQ_LAB)

#endif
