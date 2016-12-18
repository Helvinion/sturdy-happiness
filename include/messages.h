#ifndef MESSAGES_H
#define MESSAGES_H

#define ID_PER_AUCUN       0
#define ID_PER_DIDACTICIEL 1
#define ID_PER_FIN         255

#define ID_MSG_AUCUN           0
#define ID_MSG_DIDACTICIEL_A_B 1
#define ID_MSG_FIN             255

void messages_afficher(unsigned char perso, unsigned char message, unsigned char l, unsigned char c);
void messages_update();

#endif
