.include "include/zeropage.inc"
.importzp sp
.import _main
.import initlib
.import zerobss
.import copydata
.import __RAM_START__
.import __RAM_SIZE__

.export start
.export _exit
.export __STARTUP__:absolute=1      ; Place le bout de code dans le segment startup

start:
_exit:
    sei           ; Désactive les interruptions
    ldx #$ff      ;
    txs           ; Définit le stack pointer à $ff, le haut de la stack
    inx           ; Remet X à 0
    stx PPU_MASK  ; Met le registre 2 de contrôle de la PPU à 0
    stx DMC_FREQ  ; Met le registre de contrôle du son à 0
    stx PPU_CTRL  ; Met le registre 1 de controle de la PPU à 0 - Désactive l'appel à nmi lors des VBlanks

    bit PPU_STATUS ; La lecture de ce registre met son bit 7 (VBlank en cours) à 0
@1:                ;
    bit PPU_STATUS ; A est indéfini mais le flag N indique maintenant si on est en VBlank
    bpl @1         ; Tant que ce n'est PAS le cas, on attend.
				   ; Ca y est, on est en VBlank, on peut placer nos instructions
    txa            ; 0 -> A

; Effacer toute la mémoire vive
@clearRAM:         ;
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

; Effacer toute la mémoire vidéo.
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

	lda #%10010000   ;
	sta PPU_CTRL_VAR ; Sauvegarde le PPUCTRL dans la zeropage
	sta PPU_CTRL	 ; Active l'appel à NMI lors des VBlank

    ; Initialise le moteur de sons.
    jsr init_apu

	; Fin ;

	cli ; Reactive les interruptions

    jmp _main		 ; Appelle le programme C !

init_apu:
        ; Init $4000-4013
        ldy #$13
@loop:  lda #0
        sta $4000,y
        dey
        bpl @loop

        ; On saute $4014 et $4016 (OAMDMA)
        lda #%00001111
        sta $4015
        lda #%00000000
        sta $4017
        rts
