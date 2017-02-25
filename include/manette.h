#ifndef MANETTE_H
#define MANETTE_H

void update_manettes();

unsigned char bouton_a(unsigned char joueur);

unsigned char bouton_b(unsigned char joueur);

unsigned char bouton_select(unsigned char joueur);

unsigned char bouton_start(unsigned char joueur);

unsigned char bouton_haut(unsigned char joueur);

unsigned char bouton_bas(unsigned char joueur);

unsigned char bouton_gauche(unsigned char joueur);

unsigned char bouton_droite(unsigned char joueur);

unsigned char triche_konami(unsigned char joueur);

unsigned char select_start(unsigned char joueur);

#endif