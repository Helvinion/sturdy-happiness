.include "include/zeropage.inc"
.importzp	sp
.export		_tileset
.export		_index_in_buffer_tile_groupe
.export		_load_tile_hg
.export		_load_tile_hd
.export		_load_tile_bg
.export		_load_tile_bd

.segment	"DATA"

_index_in_buffer_tile_groupe:
	.word	$005C

.segment	"RODATA"

_tileset:
	.byte $00, $00, $00, $00 ; 0x00 : Ciel
	.byte $0d, $0d, $1f, $1f ; 0x01 : Sol plat
	.byte $1f, $1f, $1f, $1f ; 0x02 : Terre
	.byte $00, $0f, $0f, $1e ; 0x03 : Sol oblique montée
	.byte $0e, $00, $1d, $0e ; 0x04 : Sol oblique descente
	.byte $00, $00, $0b, $0c ; 0x05 : Sol sommet
	.byte $09, $0a, $1f, $1f ; 0x06 : Sol creux
	.byte $1e, $1f, $1f, $1f ; 0x07 : Terre coin montee 
	.byte $1f, $1d, $1f, $1f ; 0x08 : Terre coin descente
	.byte $1e, $1d, $1f, $1f ; 0x09 : Terre sous sommet
	.byte $00, $0b, $0f, $1e ; 0x0a : Sol fin montée
	.byte $0c, $00, $1c, $0e ; 0x0b : Sol début descente
	.byte $47, $61, $4e, $20 ; 0x0c : Ga/N_
	.byte $65, $61, $34, $32 ; 0x0d : ea/42
	.byte $01, $01, $01, $01 ; 0x0e : barre

.segment	"CODE"
	
; void __near__ load_tile_hg ()
.proc	_load_tile_hg: near
	ldy     #0
	lda     (ADDR_LEVEL),y
	asl     a
	asl     a
	adc     #0
	tax
	ldy     INDEX_GRP
	lda     _tileset,x
	sta     TILES_GROUP_BUF,y
	inc     INDEX_GRP
	rts
.endproc

; void __near__ load_tile_hd ()
.proc	_load_tile_hd: near
	ldy     #0
	lda     (ADDR_LEVEL),y
	asl     a
	asl     a
	adc     #1
	tax
	ldy     INDEX_GRP
	lda     _tileset,x
	sta     TILES_GROUP_BUF,y
	inc     INDEX_GRP
	rts
.endproc

; void __near__ load_tile_bg ()
.proc	_load_tile_bg: near
	ldy     #0
	lda     (ADDR_LEVEL),y
	asl     a
	asl     a
	adc     #2
	tax
	ldy     INDEX_GRP
	lda     _tileset,x
	sta     TILES_GROUP_BUF,y
	inc     INDEX_GRP
	rts
.endproc

; void __near__ load_tile_bd ()
.proc	_load_tile_bd: near
	ldy     #0
	lda     (ADDR_LEVEL),y
	asl     a
	asl     a
	adc     #3
	tax
	ldy     INDEX_GRP
	lda     _tileset,x
	sta     TILES_GROUP_BUF,y
	inc     INDEX_GRP
	rts
.endproc
