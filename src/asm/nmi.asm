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
	and #%00000001 ; V�rifie le 1er bit de VRAMUPDATE
	beq @update_palettes ; Sauter la section @update_sprites si ce bit est 0

@update_sprites:
	; Mise � jour des sprites
	lda #$00         ;
	sta PPU_OAM_ADDR ; (Fait pointer la SPR-PPU au d�but de la SPR-RAM (Sprite RAM))
    lda #>OAM_BUF    ; 
	sta PPU_OAM_DMA  ; Copie les 256 octets de la RAM ($0200 -> $0300) en SPR-RAM

@update_palettes:
	lda <VRAMUPDATE
	and #%00000010 ; V�rifie le 2e bit de VRAMUPDATE
	bne @1         ; Execute l'update des palettes si ce bit est � 0
	jmp @update_tiles
@1:
	; Mise � jour des palettes
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
	sta PPU_DATA    ; Charge les 8 palettes enregistr�es dans la PPU
	
	; Mettre � jour les changements de tiles
@update_tiles:
	lda <VRAMUPDATE ;
	and #%00000100 ; V�rifie le 3e bit de VRAMUPDATE
	beq @update_scroll ; Sauter la section si ce bit est 0
	                    
	ldx <NAME_UPD_LEN ;
	beq @update_scroll   ; Sauter la fin de l'update si NAME_UPD_LEN est � 0
    
	ldy #0
@update_tiles_loop:
	iny	                   ;
	lda (NAME_UPD_ADR),y   ; 
	sta PPU_ADDR           ; Selectionner la premi�re partie de l'adresse de la tile � changer
                           ; L'endianness oblige � aller le chercher en 2e position                 
    dey                    ;
	lda (NAME_UPD_ADR),y   ; 
	sta PPU_ADDR           ; Selectionner la deuxi�me partie de l'adresse de la tile � changer

	iny
	iny
	lda (NAME_UPD_ADR),y   ;
	iny                    ;
	sta PPU_DATA           ; Change la valeur de la tile

	dex                    ;
	bne @update_tiles_loop ; Lit les octets point�s par NAME_UPD_ADR 3 par 3.
                           ; Les deux premiers indiquent o� dans la PPU �crire le 3e.
                           ; Effectuer cette op�ration NAME_UPD_LEN fois

    stx <NAME_UPD_LEN    ; Place un z�ro dans NAME_UPD_LEN pour indiquer que tout a �t� trait�.

@update_scroll:
	;lda <VRAMUPDATE ;
	;and #%00001000 ; V�rifie le 4e bit de VRAMUPDATE
	;beq @endUpdate ; Sauter la section si ce bit est 0

	lda #0
	sta PPU_ADDR
	sta PPU_ADDR

	lda <SCROLL_X        ;
	sta PPU_SCROLL       ;
	lda <SCROLL_Y        ;
	sta PPU_SCROLL       ;
	lda <PPU_CTRL_VAR    ;
	sta PPU_CTRL         ; Reinitialise la PPU et le scrolling aux param�tres demand�s

@endUpdate:
	inc <FRAMECNT1       ; Incr�mente le Frame Count 1
	
    inc <FRAMECNT2       ;
	lda <FRAMECNT2       ;
	cmp #6               ;
	bne @end_nmi        ;
	lda #0               ;
	sta <FRAMECNT2       ; Incr�mente le Frame Count 2, le r�initialise s'il atteint 6.

	lda #0
	sta <VRAMUPDATE
@end_nmi: ;
    pla    ;
	tay    ;
	pla    ;
	tax    ;
	pla    ; Restaure X, Y, et A
    rti    ; Return From Interrupt
