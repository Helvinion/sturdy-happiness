.segment	"CODE"

.importzp	sp
.autoimport	on
.include "include/zeropage.inc"

.export _ecrire_zeropage
.export _ecrire_zeropage_addr
.export _attendre_VBlank_et_afficher_barre

; ecrire_zeropage(unsigned char addr_dst, unsigned char value)
.proc	_ecrire_zeropage: near

	; Mettre dans x le premier argument, l'adresse zp
	ldy     #$01
	lda     (sp),y
	tax

	; Mettre dans a le deuxième argument, la valeur
	ldy #$00
	lda (sp), y

	; Copier A à l'adresse X
	sta $00,x

	; Quitter la fonction
	jmp     incsp2
.endproc

; ecrire_zeropage_addr(unsigned char addr_dst, unsigned char* addr_src)
.proc	_ecrire_zeropage_addr: near

	; Mettre dans x le premier argument, l'adresse zp
	ldy     #$02
	lda     (sp),y
	tax

	; Mettre dans a le deuxième argument, le début de la valeur
	ldy #$00
	lda (sp), y


	; Copier A à l'adresse X
	sta $00,x

	; Mettre dans a le deuxième argument, la fin de la valeur
	ldy #$01
	lda (sp), y

	; Copier A à l'adresse X + 1
	sta $01,x

	; Quitter la fonction
	jmp     incsp3
.endproc

; _attendre_VBlank_et_afficher_barre()
.proc _attendre_VBlank_et_afficher_barre

; Commencer par attendre un VBlank.
loop1:
	lda PPU_STATUS
	and #$80
	beq loop1

	lda ACTIVER_BARRE
	bne pasDeBarre
	lda #$40
; Attendre que le bit indiquant le hit du sprite zéro soit reinitialisé	
Sprite0ClearWait:
    bit PPU_STATUS
    bne Sprite0ClearWait ; Sauter si 0x40 AND PPU_STATUS != 0
	nop

	;jmp pasDeBarre

; Attendre l'activation du bit du sprite 0;
Sprite0Wait:
    bit PPU_STATUS
    beq Sprite0Wait ; Sauter si 0x40 AND PPU_STATUS == 0
	nop
pasDeBarre:
; Quand on arrive ici, un VBlank vient d'avoir lieu et la NMI a été exectutée.

; La PPU possède quatre registres internes. t, v, x, et w. t et v font 15 bits, x en fait 3 et w 1 seul
; Quand on utilise deux fois PPUADDR ou PPUSCROLL, t est copié dans v.
; t et v semblent avoir le format suivant: YYYNNYYYYYXXXXX ou NN correspond à la nametable
; PPUADDR est relié aux bits ..... de t.
; PPUSCROLL est relié aux bits YYY--YYYYY----- de t, puis aux bits ----------XXXXX de t et XXX de x.
; Quand on écrit à deux reprises sur PPUADDR ou PPUSCROLL (même l'un puis l'autre), t est chargé dans v.
	lda PPU_CTRL_VAR
	and #$03          ; Extraire la nametable de PPU_CTRL_VAR
	asl               ; Shift deux fois vers la gauche pour 
	asl               ; correspondre à la PPU
	sta PPU_ADDR      ; Ecrire sur le registre t de la PPU

	lda <SCROLL_Y ; Récupérer le scrolling en Y
	sta PPU_SCROLL ; Ecrire sur le registre t de la PPU, ce qui le transfert dans v

	and #$F8     ; Garder Y mais ne garder que ses bits de poid fort
	asl          ; et les décaller vers la gauche
	asl
	sta tmp1

	lda <SCROLL_X  ; Charger le paramètre scrollX
	sta PPU_SCROLL ; L'enregistrer aussi sec dans PPUSCROLL

	lsr
	lsr
	lsr ; Virer les bits de poids faible de X
	ora tmp1 ; On a maintenant dans A la valeur à écrire
	         ; dans PPUADDR pendant le prochain HBlank
			 ; On aura alors un temps minuscule pour le faire
			 
	ldx #$06 ; A ajuster pour tomber pile sur un HBlank...
loop2:
	dex
	bne loop2
	
	; HBlank en court !
	sta PPU_ADDR
	rts
.endproc