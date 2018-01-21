#ifndef ECRAN_H
#define ECRAN_H

void fixer_position_camera(unsigned int x, unsigned int y);
signed char faux_bouger_camera_x(signed char pixels);
signed char bouger_camera_x(signed char pixels);
signed char bouger_camera_y(signed char pixels);
unsigned char est_bloquee_gauche();
unsigned char est_bloquee_droite();

#endif /* ECRAN_H */
