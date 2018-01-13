#ifndef NIVEAU_H
#define NIVEAU_H

unsigned int taille_x_niveau_courant();
unsigned int taille_y_niveau_courant();

void changer_niveau(unsigned char niveau_n);
void charger_niveau(unsigned char nametable, unsigned int position_x, unsigned int position_y);

void charger_ligne_verticale(unsigned char nametable, unsigned char c, unsigned int position_x, unsigned int position_y);
void charger_ligne_horizontale(unsigned char nametable, unsigned char l, unsigned int position_x, unsigned int position_y);

#endif /* NIVEAU_H */