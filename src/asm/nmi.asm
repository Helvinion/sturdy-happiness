.include "include/zeropage.inc"
.export nmi

.segment "STARTUP"

; Cette procédure est appellée à chaque VBlank.
; C'est le seul moment où on peut changer l'affichage.
; On a alors approximativement 2250 cycles CPU pour l'executer
nmi:
    pha ; Sauvegarder A
    txa ;
    pha ; Sauvegarder X
    tya ;
    pha ; Sauvegarder Y

	sta PPU_MASK_VAR
	lda PPU_MASK

    jsr update_sprites
    jsr update_palettes
    jsr update_tiles
	jsr update_tiles_group
    jsr update_scolling
    jsr end_update

    pla ;
    tay ; Restaurer Y
    pla ;
    tax ; Restaurer X
    pla ; Restaurer A
    rti ; Quitter la NMI


end_update:
    inc <FRAMECNT1       ; Incrémente le Frame Count 1
    inc <FRAMECNT2       ; Et le Frame Count 2
    lda <FRAMECNT2       ;
    cmp #6               ;
    bne @1               ; Rien de spécial si le Frame Count 2 n'est pas à 6.
    lda #0               ;
    sta <FRAMECNT2       ; Réinitialise Le Frame Count 2 s'il atteint 6.
@1: rts


update_sprites:
    lda #$00         ;
    sta PPU_OAM_ADDR ; (Fait pointer la SPR-PPU au début de la SPR-RAM (Sprite RAM))
    lda #>OAM_BUF    ;
    sta PPU_OAM_DMA  ; Copie les 256 octets de la RAM ($0200 -> $0300) en SPR-RAM~
    rts

update_scolling:
    ;lda #0
   ; sta PPU_ADDR
    ;sta PPU_ADDR
    lda <SCROLL_X        ;
    sta PPU_SCROLL       ;
    lda <SCROLL_Y        ;
    sta PPU_SCROLL       ;
    lda <PPU_CTRL_VAR    ;
    sta PPU_CTRL         ; Reinitialise la PPU et le scrolling aux paramètres demandés
    rts

update_tiles:
    ldx <NAME_UPD_LEN ;
    beq @2            ; Sauter la fin de l'update si NAME_UPD_LEN est à 0
    ldy #0
@1: iny                    ;
    lda (NAME_UPD_ADR),y   ;
    sta PPU_ADDR           ; Selectionner la première partie de l'adresse de la tile à changer
    dey                    ; L'endianness oblige à aller le chercher en 2e position
    lda (NAME_UPD_ADR),y   ;
    sta PPU_ADDR           ; Selectionner la deuxième partie de l'adresse de la tile à changer
    iny
    iny
    lda (NAME_UPD_ADR),y   ;
    iny                    ;
    sta PPU_DATA           ; Change la valeur de la tile
    dex                    ;
    bne @1 ;
    stx <NAME_UPD_LEN    ; Place un zéro dans NAME_UPD_LEN pour indiquer que tout a été traité.
@2: rts

update_tiles_group:
	ldx <T_GROUP_SIZE
	beq @1            ; Quitter la routine si aucun changement n'est demandé
	ldy #0
@2:	jsr set_addr
; Regarder les options
	iny                   ;
	iny                   ;
	lda (TILES_GROUP),y   ; Charger les options
	and #%00000001        ;
	beq @h                ; Selectionner le mode horizontal ou vertical
    jsr copy_vertical     ; Copier les octets verticalement, puis
	jmp @e                ; Passer à la suite (et fin)
@h: jsr copy_horizontal
@e:	ldx <T_GROUP_SIZE     ; Recharge le nombre de groupes à copier
	dex
	stx <T_GROUP_SIZE     ; stx n'affecte pas les flags
	beq @1                ; Quitter si tout a été lu
	bne @2                ; Sinon, boucler
@1: lda PPU_CTRL_VAR      ; Remet le mode horizontal
	and #%11111011        ; Désactive le bit ordonnant à la PPU de changer son adresse de 32 en 32 pour repasse en mode 1 en 1
	sta PPU_CTRL_VAR      ;
	sta PPU_CTRL          ;
	rts

set_addr:
	iny                   ; Pour chaque groupe :
	lda (TILES_GROUP),y   ;
	sta PPU_ADDR          ;
	and #%00000011        ; Ne garde que les deux derniers bits,
	asl                   ; Les décale à gauche pour accueillir 
	asl                   ; les 3 bits de poids fort de l'octet de poid faible
	asl
	sta PPU_VER_LOC
	dey                   ;
	lda (TILES_GROUP),y   ; Charger l'adresse PPU
	sta PPU_ADDR          ;
	sta PPU_HOR_LOC       ; Sauvegarde l'octet de poid faible
	and #%11100000        ; Récupère les 3 bits de poids fort de cet octet de poids faible
	clc
	lsr                   ; Les décale de 5 bits verss la droite
	lsr
	lsr
	lsr
	lsr
	ora PPU_VER_LOC       ; Les combine avec les bits de poids faible de l'octet de poids fort
	sta PPU_VER_LOC       ; Stocke le tout, qui est normalement un n° de ligne dans PPU_VER_LOC
	rts
	
adjust_vertical:
	pha
	tya
	pha
	ldy #1                ; 
	lda (TILES_GROUP),y   ; Recharger l'adresse de destination
	and #%11111100        ; Virer les bits qui concernent la ligne
	sta PPU_ADDR
	dey
	lda (TILES_GROUP),y   ; Recharger la deuxième partie de l'adresse
	and #%00011111        ; Virer les bits qui concernent la ligne
	sta PPU_ADDR	
	pla
	tay
	pla	
	rts

copy_vertical:
	lda PPU_CTRL_VAR      ; Mode vertical, changer PPU_CTRL et PPU_CTRL_VAR
	ora #%00000100        ; allume le bit ordonnant à la PPU de changer son adresse de 32 en 32
	sta PPU_CTRL_VAR      ;
	sta PPU_CTRL          ;
	;jsr copy_group
    ldx #32               ; Initialise le compteur d'octets copiés
	ldy #0
@4:	lda PPU_VER_LOC       ; Récupère la ligne d'écriture
	cmp #30               ; Si on vient d'atteindre la table des attributions
	bne @6
	jsr adjust_vertical
@6:	lda TILES_GROUP_BUF,y ; Lit l'octet suivant
	sta PPU_DATA          ; et le stocke.
	inc PPU_VER_LOC       ; Incrémente le numéro de ligne
	iny
	dex                   ; Décrémente le nombre d'octets suivants
	bne @4                ; Recommence si on en a pas copié 32.
	iny                   ; Incrémente Y pour le mettre au début du groupe suivant
	rts

adjust_horizontal: ; Remonte d'une ligne dans le pointeur de la PPU et change la nametable
	pha
	tya
	pha                   ; Sauvegarde de Y et A
	ldy #1                ; Reprend l'adresse (poids fort)
	lda (TILES_GROUP),y   ;
	eor #%00001100        ; Change la nametable de cette adresse en inversant certains bits
	sta PPU_ADDR          ; Et stocke le résultat
	lda PPU_HOR_LOC       ; Reprend les bits de poids faible
	clc
	sbc #31               ; Remonte d'une ligne (normalement c'est 32 mais un bug qq part fait que c'est 31)
	sta PPU_ADDR          ; Stocke cet octet
	pla                   ; Restauration de Y et A
	tay
	pla
	rts
	
copy_horizontal:
	lda PPU_CTRL_VAR      ;
	and #%11111011        ; Désactive le bit ordonnant à la PPU de changer 
	sta PPU_CTRL_VAR      ; son adresse de 32 en 32 pour repasser en mode 1 en 1
	sta PPU_CTRL          ;
    ldx #32               ; Initialise le compteur d'octets copiés
	ldy #0
@4: lda TILES_GROUP_BUF,y ; Lit l'octet suivant
	sta PPU_DATA          ; et le stocke.
	inc PPU_HOR_LOC       ; Incrémente la colonne d'affichage
	lda PPU_HOR_LOC       ; Récupère cette valeur
	and #%00011111        ; Si c'est un multiple de 32, alors on est passés à la ligne suivante
	bne @5                ; 
	jsr adjust_horizontal ; Auquel cas on doit en fait changer la nametable mais garder l'ancienne ligne
@5:	iny
	dex                   ; Décrémente le nombre d'octets suivants
	bne @4                ; Recommence si on en a pas copié 32.
	iny                   ; Incrémente Y pour le mettre au début du groupe suivant
	rts

update_palettes:     ;
    lda #$3f         ;
    sta PPU_ADDR     ;
    lda #$00         ;
    sta PPU_ADDR     ; Fait pointer PPU_DATA sur l'adresse $3f00 (palette des images)

    lda PAL_BUF+0   ;
    sta PPU_DATA    ;
    lda PAL_BUF+1   ;
    sta PPU_DATA    ;
    lda PAL_BUF+2   ;
    sta PPU_DATA    ;
    lda PAL_BUF+3   ;
    sta PPU_DATA    ;
                    ;
    lda PPU_DATA    ;
    lda PAL_BUF+5   ;
    sta PPU_DATA    ;
    lda PAL_BUF+6   ;
    sta PPU_DATA    ;
    lda PAL_BUF+7   ;
    sta PPU_DATA    ;
                    ;
    lda PPU_DATA    ;
    lda PAL_BUF+9   ;
    sta PPU_DATA    ;
    lda PAL_BUF+10  ;
    sta PPU_DATA    ;
    lda PAL_BUF+11  ;
    sta PPU_DATA    ;
                    ;
    lda PPU_DATA    ;
    lda PAL_BUF+13  ;
    sta PPU_DATA    ;
    lda PAL_BUF+14  ;
    sta PPU_DATA    ;
    lda PAL_BUF+15  ;
    sta PPU_DATA    ;

    lda PPU_DATA    ;
    lda PAL_BUF+17  ;
    sta PPU_DATA    ;
    lda PAL_BUF+18  ;
    sta PPU_DATA    ;
    lda PAL_BUF+19  ;
    sta PPU_DATA    ;
                    ;
    lda PPU_DATA    ;
    lda PAL_BUF+21  ;
    sta PPU_DATA    ;
    lda PAL_BUF+22  ;
    sta PPU_DATA    ;
    lda PAL_BUF+23  ;
    sta PPU_DATA    ;

    lda PPU_DATA    ;
    lda PAL_BUF+25  ;
    sta PPU_DATA    ;
    lda PAL_BUF+26  ;
    sta PPU_DATA    ;
    lda PAL_BUF+27  ;
    sta PPU_DATA    ;
                    ;
    lda PPU_DATA    ;
    lda PAL_BUF+29  ;
    sta PPU_DATA    ;
    lda PAL_BUF+30  ;
    sta PPU_DATA    ;
    lda PAL_BUF+31  ;
    sta PPU_DATA    ; Charge les 8 palettes enregistrées dans la PPU
    rts
