#include <musique.h>

void jouer_son_carre_1(struct CanalCarre* son)
{
	*((unsigned char*)0x4000) = son->reg_1;
	*((unsigned char*)0x4001) = son->reg_2;
	*((unsigned char*)0x4002) = son->reg_3;
	*((unsigned char*)0x4003) = son->reg_4;
}

void jouer_son_carre_2(struct CanalCarre* son)
{
	*((unsigned char*)0x4004) = son->reg_1;
	*((unsigned char*)0x4005) = son->reg_2;
	*((unsigned char*)0x4006) = son->reg_3;
	*((unsigned char*)0x4007) = son->reg_4;
}

void jouer_son_triangle(struct CanalTriangle* son)
{
	*((unsigned char*)0x4008) = son->reg_1;
	*((unsigned char*)0x400a) = son->reg_2;
	*((unsigned char*)0x400b) = son->reg_3;	
}

void jouer_son_bruit(struct CanalBruit* son)
{
	*((unsigned char*)0x400c) = son->reg_1;
	*((unsigned char*)0x400e) = son->reg_2;
	*((unsigned char*)0x400f) = son->reg_3;	
}
