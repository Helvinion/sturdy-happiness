#ifndef UTILES_H
#define UTILES_H

void ecrire_zeropage(unsigned char addr_dst, unsigned char value);
void ecrire_zeropage_addr(unsigned char addr_dst, unsigned char* addr_src);
void attendre_VBlank_et_afficher_barre();

#endif
