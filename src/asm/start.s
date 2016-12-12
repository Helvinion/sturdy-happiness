.export start
.export _exit

.export __STARTUP__:absolute=1      ; Mark as startup

.include "memmap.inc"
.include "zeropage.inc"

.import _main

.import initlib
.import zerobss
.import copydata

.import __RAM_START__
.import __RAM_SIZE__

.segment       	"STARTUP"
start:
_exit:
    sei           ; Désactive les interruptions
    ldx #$ff      ;
    txs           ; Définit le stack pointer à $ff
    inx           ; Remet X à 0
    stx PPU_MASK  ; Met le registre 2 de contrôle de la PPU à 0
    stx DMC_FREQ  ; Met le registre de contrôle du son à 0
    stx PPU_CTRL  ; Met le registre 1 de controle de la PPU à 0 - Désactive l'appel à nmi lors des VBlanks

    bit PPU_STATUS ; La lecture de ce registre met son bit 7 (VBlank en cours) à 0
@1:                ;
    bit PPU_STATUS ; A est indéfini mais le flag N indique maintenant si on est en VBlank
    bpl @1         ; Tant que ce n'est PAS le cas, on attend.

    txa            ; 0 -> A
@clearRAM:          ;
    sta $0000,x    ;
    sta $0100,x    ;
    sta $0200,x    ;
    sta $0300,x    ;
    sta $0400,x    ;
    sta $0500,x    ;
    sta $0600,x    ;
    sta $0700,x    ;
    inx            ;
    bne @clearRAM  ; Met des 0 dans toute la RAM ($0000 -> $07ff)

@clearVRAM:
	lda #$20       ;
	sta PPU_ADDR   ;
	lda #$00       ;
	sta PPU_ADDR   ; Indique que la PPU doit écrire à l'adresse $2000 
@3:                ;
	ldy #$40       ;
@4:                ;
    sta PPU_DATA   ;
	iny            ;
	bne @4         ;
	inx            ;
	bne @3         ; Remplit la mémoire de la PPU de 0 ($2000 -> $e000)

    bit PPU_STATUS ; 
@2:                ;
    bit PPU_STATUS ;
    bpl @2         ; Attend de ne plus être en VBlank

    jsr	zerobss                         ; Remplit de 0 le segment BSS
	jsr	copydata                        ; Charge la section DATA dans la mémoire
    lda #<(__RAM_START__+__RAM_SIZE__)  ;
    sta	sp                              ;
    lda	#>(__RAM_START__+__RAM_SIZE__)  ;
    sta	sp+1                            ; Place le stack pointer (tambouille de ca65) à la fin de la RAM
	jsr	initlib                         ; Tambouille pour pouvoir faire du C

	lda #%10000000   ;
	sta PPU_CTRL_VAR ; Sauvegarde le PPUCTRL dans la zeropage
	sta PPU_CTRL	 ; Active l'appel à NMI lors des VBlank
    
    ; Note constante ;
    jsr init_apu
    lda #%00010111
    sta $4002

    lda #%00000100
    sta $4003

    lda #%10111111
    sta $4000
    ; Fin ;
    
    
    jmp _main		 ; Appelle le programme C !
 
 
init_apu:
        ; Init $4000-4013
        ldy #$13
@loop:  lda @regs,y
        sta $4000,y
        dey
        bpl @loop
 
        ; We have to skip over $4014 (OAMDMA)
        lda #$0f
        sta $4015
        lda #$40
        sta $4017
   
        rts
@regs:
        .byte $30,$08,$00,$00
        .byte $30,$08,$00,$00
        .byte $80,$00,$00,$00
        .byte $30,$00,$00,$00
        .byte $00,$00,$00,$00


; ---Code mort sensé détecter un mode ntsc. On considère le mode PAL ---
;   lda <FRAMECNT1    ;
;@wait:                ;
;	cmp <FRAMECNT1    ;
;	beq @wait         ; Attend un changement de FRAMECNT1 (lors d'une nmi probablement)

;	ldx #52		      ; (blargg's code)
;	ldy #24           ;
;@detectNTSC:          ;
;	dex               ;
;	bne @detectNTSC   ;
;	dey               ;
;	bne @detectNTSC   ; Attendre d'avoir fait cette boucle 1248 fois (??)

;	lda PPU_STATUS    ; 
;	and #$80          ;
;	sta <NTSCMODE     ; (???)

;	lda #1
;	sta <RAND_SEED