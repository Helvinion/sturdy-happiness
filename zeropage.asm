;
; zeropage.inc
;
; (C) Copyright 2002-2012, Ullrich von Bassewitz (uz@cc65.org)
;

; Assembler include file that imports the runtime zero page locations used
; by the compiler, ready for usage in asm code.


        .globalzp       sp, sreg, regsave
        .globalzp       ptr1, ptr2, ptr3, ptr4
        .globalzp       tmp1, tmp2, tmp3, tmp4
        .globalzp       regbank
  
; The size of the register bank
regbanksize     = 6

; The total amount of zero page space used
zpspace         = 26

; The amount of space that needs to be saved by an interrupt handler that
; calls C code (does not include the register bank, which is saved by the
; generated C code if required).
zpsavespace     = zpspace - regbanksize


PPU_CTRL	=$2000
PPU_MASK	=$2001
PPU_STATUS	=$2002
PPU_OAM_ADDR=$2003
PPU_OAM_DATA=$2004
PPU_SCROLL	=$2005
PPU_ADDR	=$2006
PPU_DATA	=$2007
PPU_OAM_DMA	=$4014
PPU_FRAMECNT=$4017
DMC_FREQ	=$4010
CTRL_PORT1	=$4016
OAM_BUF		=$0200
PAL_BUF		=$01b0


;  NOM       |    CASE  | COMMENTAIRE
FRAMECNT1    =    $00   ; Compteur de frames
FRAMECNT2    =    $01   ; Compteur de frames modulo 6
NTSCMODE     =    $02   ; Mode NTSC ou PAL
ADR_MUS      =    $03   ; Adresse de la musique à jouer sur deux octets
;            =    $04   ;
ADR_MUS_CUR  =    $05   ; Adresse de la note à jouer
;            =    $06   ; 
MUS_CMPT     =    $07   ; Compteur actuel
MUS_REG_TMP  =    $08   ; Adresse du registre de musique où écrire
;            =    $09   ;
;            =    $0A
;            =    $0B
;            =    $0C
;            =    $0D
SCROLL_X     =    $0E  ; Srolling horizontal (traité en VBlank)
SCROLL_Y     =    $0F  ; Scrolling vertical (traité en VBlank)
PPU_CTRL_VAR =    $10  ; Controle de la PPU (traité en VBlank)
RAND_SEED    =    $11  ; Graine du générateur aléatoire
NAME_UPD_ADR =    $12  ; Adresse du buffer de modifs de tiles (traité en VBlank)
;            =    $13  ;
NAME_UPD_LEN =    $14  ; Nombre de modifications de tiles à appliquer (traité en VBlank)
;            =    $15 
TILES_GROUP  =    $16  ; Adresse du buffer des goupes de modifs (traité en VBlank)
;            =    $17  ;
T_GROUP_SIZE =    $18  ; Taille du buffer
;            =    $19
;            =    $1A
;            =    $1B
;            =    $1C
;            =    $1D
;            =    $1E
;            =    $1F
;            =    $20 ; SP Toute cette zone est interdite d'accès.
;            =    $21 ; |  Elle appartient au compilateur C.
;            =    $22 ; SREG
;            =    $23 ; |
;            =    $24 ; REGSAVE
;            =    $25 ; |
;            =    $26 ; |
;            =    $27 ; |
;            =    $28 ; PTR1
;            =    $29 ; |
;            =    $2A ; PTR2
;            =    $2B ; |
;            =    $2C ; PTR3
;            =    $2D ; |
;            =    $2E ; PTR4
;            =    $2F ; |
;            =    $30 ; TMP1
;            =    $31 ; TMP2
;            =    $32 ; TMP3
;            =    $33 ; TMP4
;            =    $34 ; REGBANK
;            =    $35 ; |
;            =    $36 ; |
;            =    $37 ; |
;            =    $38 ; |
;            =    $39 ; |
;            =    $3A
;            =    $3B
;            =    $3C
;            =    $3D
;            =    $3E
;            =    $3F
;            =    $40
;            =    $41
;            =    $42
;            =    $43
;            =    $44
;            =    $45
;            =    $46
;            =    $47
;            =    $48
;            =    $49
;            =    $4A
;            =    $4B
;            =    $4C
;            =    $4D
;            =    $4E
;            =    $4F
;            =    $50
;            =    $51
;            =    $52
;            =    $53
;            =    $54
;            =    $55
;            =    $56
;            =    $57
;            =    $58
;            =    $59
;            =    $5A
;            =    $5B
;            =    $5C
;            =    $5D
;            =    $5E
;            =    $5F
;            =    $60
;            =    $61
;            =    $62
;            =    $63
;            =    $64
;            =    $65
;            =    $66
;            =    $67
;            =    $68
;            =    $69
;            =    $6A
;            =    $6B
;            =    $6C
;            =    $6D
;            =    $6E
;            =    $6F
;            =    $70
;            =    $71
;            =    $72
;            =    $73
;            =    $74
;            =    $75
;            =    $76
;            =    $77
;            =    $78
;            =    $79
;            =    $7A
;            =    $7B
;            =    $7C
;            =    $7D
;            =    $7E
;            =    $7F
;            =    $80
;            =    $81
;            =    $82
;            =    $83
;            =    $84
;            =    $85
;            =    $86
;            =    $87
;            =    $88
;            =    $89
;            =    $8A
;            =    $8B
;            =    $8C
;            =    $8D
;            =    $8E
;            =    $8F
;            =    $90
;            =    $91
;            =    $92
;            =    $93
;            =    $94
;            =    $95
;            =    $96
;            =    $97
;            =    $98
;            =    $99
;            =    $9A
;            =    $9B
;            =    $9C
;            =    $9D
;            =    $9E
;            =    $9F
;            =    $A0
;            =    $A1
;            =    $A2
;            =    $A3
;            =    $A4
;            =    $A5
;            =    $A6
;            =    $A7
;            =    $A8
;            =    $A9
;            =    $AA
;            =    $AB
;            =    $AC
;            =    $AD
;            =    $AE
;            =    $AF
;            =    $B0
;            =    $B1
;            =    $B2
;            =    $B3
;            =    $B4
;            =    $B5
;            =    $B6
;            =    $B7
;            =    $B8
;            =    $B9
;            =    $BA
;            =    $BB
;            =    $BC
;            =    $BD
;            =    $BE
;            =    $BF
;            =    $C0
;            =    $C1
;            =    $C2
;            =    $C3
;            =    $C4
;            =    $C5
;            =    $C6
;            =    $C7
;            =    $C8
;            =    $C9
;            =    $CA
;            =    $CB
;            =    $CC
;            =    $CD
;            =    $CE
;            =    $CF
;            =    $D0
;            =    $D1
;            =    $D2
;            =    $D3
;            =    $D4
;            =    $D5
;            =    $D6
;            =    $D7
;            =    $D8
;            =    $D9
;            =    $DA
;            =    $DB
;            =    $DC
;            =    $DD
;            =    $DE
;            =    $DF
;            =    $E0
;            =    $E1
;            =    $E2
;            =    $E3
;            =    $E4
;            =    $E5
;            =    $E6
;            =    $E7
;            =    $E8
;            =    $E9
;            =    $EA
;            =    $EB
;            =    $EC
;            =    $ED
;            =    $EE
;            =    $EF
;            =    $F0
;            =    $F1
;            =    $F2
;            =    $F3
;            =    $F4
;            =    $F5
;            =    $F6
;            =    $F7
;            =    $F8
;            =    $F9
;            =    $FA ; 6 octets pour les registres du compilateur
;            =    $FB
;            =    $FC
;            =    $FD
;            =    $FE
;            =    $FF

.globalzp       sp, sreg, regsave
        .globalzp       ptr1, ptr2, ptr3, ptr4
        .globalzp       tmp1, tmp2, tmp3, tmp4
        .globalzp       regbank