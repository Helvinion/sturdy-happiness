#include <ecran.h>

#define SCROLL_NTABLE (unsigned char*)(0x2D) // Registre de travail
#define SCROLL_X      (unsigned char*)(0x2E) // Srolling horizontal (traité en VBlank)
#define SCROLL_Y      (unsigned char*)(0x2F) // Scrolling vertical (traité en VBlank)
#define PPU_CTRL_VAR  (unsigned char*)(0x30) // Nametable de départ pour le scrolling (aussi géré en VBlank)

void set_ppu_ctrl()
{
	__asm__("lda %b", 0x2e); // Charger le scrolling en X
	__asm__("clc");          // Placer son bit de poids fort à droite
	__asm__("rol");
	__asm__("adc #0");
	__asm__("and #%b", 0x01); // Annuler ses autres bits
	__asm__("sta %b", 0x2d); // Sauvegarder quelque part
	
	__asm__("lda %b", 0x2f); // Charger le scrolling en Y
	__asm__("clc");          // Placer son bit de poids fort à droite
	__asm__("rol");
	__asm__("adc #0");
	__asm__("asl");           // Décaler à gauche pour faire de la place à X
	__asm__("and #%b", 0x02); // Annuler ses autres bits
	
	__asm__("ora %b", 0x2d); // Combiner avec X
	__asm__("sta %b", 0x2d); // Sauvegarder quelque part

	__asm__("lda %b", 0x30); // Récupérer le registre de la PPU
	__asm__("and #%b", (char)0xFC); // Effacer ses deux derniers octets
	__asm__("ora %b", 0x2D); // Combiner avec le registre temporaire	
	__asm__("sta %b", 0x30); // Sauvegarder dans le registre de la PPU
}

void set_scrolling(unsigned char x, unsigned char y)
{
	*SCROLL_X = x;
	*SCROLL_Y = y;
	//set_ppu_ctrl();
}

void change_scrolling_x(signed char diff)
{
	(*SCROLL_NTABLE) = (*SCROLL_X);
	(*SCROLL_X) += diff;
	
	// Les parenthèses sont obligatoires parce que ce vieux cc65 ne gère pas les priorités d'opérateurs.
	if ((diff > 0 && (*SCROLL_NTABLE) > (*SCROLL_X)) || (diff < 0 && (unsigned char)-diff > (*SCROLL_NTABLE)))
		(*PPU_CTRL_VAR) ^= 0x01; // Inverse le dernier bit de ce registre pour changer de Nametable : on est arrivé au bout de l'autre.
}

void change_scrolling_y(signed char diff)
{
	(*SCROLL_NTABLE) = (*SCROLL_Y);
	(*SCROLL_Y) += diff;

	// L'écran de la NES ne fait que 240 pixels en hauteur, le controle de l'inversion de la nametable est donc plus compliqué.
	if (diff > 0 && ((*SCROLL_NTABLE) > (*SCROLL_Y) || (*SCROLL_Y) > 240))
	{
		(*SCROLL_Y) += 16;
		(*PPU_CTRL_VAR) ^= 0x02;
		// Inverse le penultième bit de ce registre pour changer de Nametable : on est arrivé au bout de l'autre.
	}
	else if (diff < 0 && ((unsigned char)-diff) > (*SCROLL_NTABLE))
	{
		(*SCROLL_Y) -= 16;
		(*PPU_CTRL_VAR) ^= 0x02;
		// Inverse le penultième bit de ce registre pour changer de Nametable : on est arrivé au bout de l'autre.
	}
}
