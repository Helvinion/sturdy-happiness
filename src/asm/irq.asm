.include "include/zeropage.inc"
.export irq

.segment "STARTUP"

irq:
	php ; Sauvegarder le statut
	pha ; Sauvergarder A
	txa
	pha ; Sauvergarder X;
	tya
	pha ; Sauvegarder Y

	lda $4015 ; Aknowldege de l'interruption

boucle:
	lda MUS_CMPT         ; Charger le délai actuel dans A
	ldy #1               ; Le délai à attendre est le deuxième octet de la structure
	cmp (ADR_MUS_CUR),y  ; Comparer le délai actuel avec celui à atteindre
	bne @1               ; Sauter ce qui suit si le délai n'est pas atteint. TODO: bmi à la place pour modifs à la volée
	                     ; OK, si on est ici, on a un bout de note à jouer !

	ldy #0
	lda (ADR_MUS_CUR),y  ; Charge dans A le n° de registre où écrire la valeur
	tax                  ; Copie ce n° dans X
	ldy #2
	lda (ADR_MUS_CUR),y  ; Charge dans A la valeur à écrire dans le registre
	sta $4000,X          ; Sauvegarde cette valeur en 0x4000 + X, soit le registre à atteindre

	                     ; Il faut à présent remettre le délai à 0 et passer à l'étape suivante
	lda #0
	sta MUS_CMPT

	clc
	lda ADR_MUS_CUR   ; Charge les bits de poids *faible* (little endian) de l'adresse de la note courante
	adc #3            ; Y ajoute 3
	sta ADR_MUS_CUR   ; Sauvegarde le résultat
	lda ADR_MUS_CUR+1 ; Charge les bits de poids fort
	adc #0            ; Y ajoute 0, plus le Carry s'il est set.
	sta ADR_MUS_CUR+1

	ldy #0
	lda (ADR_MUS_CUR),y ; Charge le registre de la nouvelle note
	cmp #$ff            ; Compare cette valeur avec 0xff
	bne boucle          ; Et si ce n'est pas le cas, retour en haut; Sinon :
	lda ADR_MUS         ; Recommencer la musique au début !
	sta ADR_MUS_CUR
	lda ADR_MUS+1
	sta ADR_MUS_CUR+1

	jmp boucle          ; retour en haut

@1:
	; La boucle est terminée, on peut finaliser l'IRQ
	inc MUS_CMPT ; Incrémenter le délai

	pla
	tay ; Restaurer Y
	pla
	tax ; Restaurer X
	pla ; Restaurer A
	plp ; Restaurer le statut
    rti ; Return from interrupt
