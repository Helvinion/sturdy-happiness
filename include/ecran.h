#ifndef ECRAN_H
#define ECRAN_H

void fixer_position_camera(unsigned int x, unsigned int y);
signed char bouger_camera_x(signed char pixels);
signed char bouger_camera_y(signed char pixels);
unsigned char est_bloquee_gauche();
unsigned char est_bloquee_droite();


/*
void set_scrolling(unsigned char x, unsigned char y);
void set_scrolling_x(unsigned char x);
void set_scrolling_y(unsigned char y);
void change_scrolling_x(signed char diff);
void change_scrolling_y(signed char diff);
*/

#endif /* ECRAN_H */
