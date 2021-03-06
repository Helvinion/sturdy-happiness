#ifndef ECRAN_H
#define ECRAN_H

extern unsigned char ligne_chargee;

void fixer_position_camera(unsigned int x, unsigned int y);
signed char faux_bouger_camera_x(signed char pixels);

unsigned char bouger_camera_droite(unsigned char pixels);
unsigned char bouger_camera_gauche(unsigned char pixels);
unsigned char bouger_camera_haut(unsigned char pixels);
unsigned char bouger_camera_bas(unsigned char pixels);

signed char bouger_camera_x(signed char pixels);
signed char bouger_camera_y(signed char pixels);
unsigned char est_bloquee_gauche();
unsigned char est_bloquee_droite();

#endif /* ECRAN_H */
