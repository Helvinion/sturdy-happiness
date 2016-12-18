.export nmi

.include "memmap.inc"
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

    jsr update_sprites
    jsr update_palettes
    jsr update_tiles
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
    sta <TODO_NMI        ; Réinitialise la TODO liste de la NMI
@1: rts


update_sprites:
    lda <TODO_NMI    ;
    and #%00000001   ; Vérifie le 1er bit de TODO_NMI
    beq @1           ; Quitter si ce bit est 0
    lda #$00         ;
    sta PPU_OAM_ADDR ; (Fait pointer la SPR-PPU au début de la SPR-RAM (Sprite RAM))
    lda #>OAM_BUF    ;
    sta PPU_OAM_DMA  ; Copie les 256 octets de la RAM ($0200 -> $0300) en SPR-RAM~
@1: rts

update_scolling:
    lda #0
    sta PPU_ADDR
    sta PPU_ADDR
    lda <SCROLL_X        ;
    sta PPU_SCROLL       ;
    lda <SCROLL_Y        ;
    sta PPU_SCROLL       ;
    lda <PPU_CTRL_VAR    ;
    sta PPU_CTRL         ; Reinitialise la PPU et le scrolling aux paramètres demandés
    rts

update_tiles:
    lda <TODO_NMI     ;
    and #%00000100    ; Vérifie le 3e bit de TODO_NMI
    beq @2            ; quitter si ce bit est 0
    ldx <NAME_UPD_LEN ;
    beq @2            ; Sauter la fin de l'update si NAME_UPD_LEN est à 0
    ldy #0
@1:
    iny                    ;
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
@2:
    rts

update_palettes:
    lda <TODO_NMI
    and #%00000010 ; Vérifie le 2e bit de TODO_NMI
    bne @1         ; rester si ce bit est à 1
    rts            ; Sinon quitter
@1:
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
