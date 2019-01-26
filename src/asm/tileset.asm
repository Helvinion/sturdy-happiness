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
	.byte $00, $00, $00, $00 ;  0: Ciel
	.byte $0d, $0d, $1f, $1f ;  1: Sol plat
	.byte $1f, $1f, $1f, $1f ;  2: Terre
	.byte $00, $0f, $0f, $1e ;  3: Sol oblique montée
	.byte $0e, $00, $1d, $0e ;  4: Sol oblique descente
	.byte $00, $00, $0b, $0c ;  5: Sol sommet
	.byte $09, $0a, $1f, $1f ;  6: Sol creux
	.byte $1e, $1f, $1f, $1f ;  7: Terre coin montee 
	.byte $1f, $1d, $1f, $1f ;  8: Terre coin descente
	.byte $1e, $1d, $1f, $1f ;  9: Terre sous sommet
	.byte $00, $0b, $0f, $1e ;  10: Sol fin montée
	.byte $0c, $00, $1c, $0e ; 11: Sol début descente

.segment	"CODE"

; void __near__ load_tile_hg (unsigned char)
.proc	_load_tile_hg: near
	ldy     #0
	lda     (sp),y
	asl     a
	asl     a
	adc     #0
	tax
	ldy     INDEX_GRP
	lda     _tileset,x
	sta     TILES_GROUP_BUF,y
	inc     INDEX_GRP
	inc     sp
	rts
.endproc

; void __near__ load_tile_hd (unsigned char)
.proc	_load_tile_hd: near
	ldy     #0
	lda     (sp),y
	asl     a
	asl     a
	adc     #1
	tax
	ldy     INDEX_GRP
	lda     _tileset,x
	sta     TILES_GROUP_BUF,y
	inc     INDEX_GRP
	inc     sp
	rts
.endproc

; void __near__ load_tile_bg (unsigned char)
.proc	_load_tile_bg: near
	ldy     #0
	lda     (sp),y
	asl     a
	asl     a
	adc     #2
	tax
	ldy     INDEX_GRP
	lda     _tileset,x
	sta     TILES_GROUP_BUF,y
	inc     INDEX_GRP
	inc     sp
	rts
.endproc

; void __near__ load_tile_bd (unsigned char)
.proc	_load_tile_bd: near
	ldy     #0
	lda     (sp),y
	asl     a
	asl     a
	adc     #3
	tax
	ldy     INDEX_GRP
	lda     _tileset,x
	sta     TILES_GROUP_BUF,y
	inc     INDEX_GRP
	inc     sp
	rts
.endproc
