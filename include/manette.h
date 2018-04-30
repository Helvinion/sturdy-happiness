#ifndef MANETTE_H
#define MANETTE_H

#define BOUTON_A      0x80
#define BOUTON_B      0x40
#define BOUTON_SELECT 0x20
#define BOUTON_START  0x10
#define BOUTON_HAUT   0x08
#define BOUTON_BAS    0x04
#define BOUTON_GAUCHE 0x02
#define BOUTON_DROITE 0x01

void update_manettes();

unsigned char nouveau_bouton_presse_manette_1(unsigned char bouton);

unsigned char bouton_presse_manette_1(unsigned char bouton);

#endif
