.export nmi

.include "memmap.inc"
.segment "STARTUP"

nmi:
    pha ;
	txa ;
	pha ;
	tya ;
	pha ; Sauvegarde A, X et Y sur la pile

	lda <VRAMUPDATE ;
	bne @update     ;
	jmp @skipUpdate ; Sauter la section @update si VRAMUPDATE est à 0

@update:
	lda #$00         ;
	sta PPU_OAM_ADDR ; (Fait pointer PPU_OAM_DATA au début de la SPR-RAM (Sprite RAM))
    lda #>OAM_BUF    ; 
	sta PPU_OAM_DMA  ; Copie les 256 octets de la RAM ($0200 -> $0300) en SPR-RAM

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
                    
	ldx <NAME_UPD_LEN ;
	beq @skipUpdate   ; Sauter la fin de l'update si NAME_UPD_LEN est à 0
	
    ldy #0
@updName:
	lda (NAME_UPD_ADR),y ;
	iny                  ;
	sta PPU_ADDR         ;
	lda (NAME_UPD_ADR),y ;
	iny                  ;
	sta PPU_ADDR         ; 
	lda (NAME_UPD_ADR),y ;
	iny                  ;
	sta PPU_DATA         ;
	dex                  ;
	bne @updName         ; Lit les octets pointés par NAME_UPD_ADR 3 par 3.
                         ; Les deux premiers indiquent où dans la PPU écrire le 3e.
                         ; Effectuer cette opération NAME_UPD_LEN fois

    stx <NAME_UPD_LEN    ; Place un zéro dans NAME_UPD_LEN pour indiquer que tout a été traité.
@skipUpdate:
	lda #0
	sta PPU_ADDR
	sta PPU_ADDR

	lda <SCROLL_X        ;
	sta PPU_SCROLL       ;
	lda <SCROLL_Y        ;
	sta PPU_SCROLL       ;
	lda <PPU_CTRL_VAR    ;
	sta PPU_CTRL         ; Reinitialise la PPU et le scrolling aux paramètres demandés

	inc <FRAMECNT1       ; Incrémente le Frame Count 1
	
    inc <FRAMECNT2       ;
	lda <FRAMECNT2       ;
	cmp #6               ;
	bne @skipNtsc        ;
	lda #0               ;
	sta <FRAMECNT2       ; Incrémente le Frame Count 2, le réinitialise s'il atteint 6.

@skipNtsc: ;
    pla    ;
	tay    ;
	pla    ;
	tax    ;
	pla    ; Restaure X, Y, et A
    rti    ; Return From Interrupt