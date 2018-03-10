.segment	"CODE"

.importzp	sp
.autoimport	on

.export _ecrire_zeropage
.export _ecrire_zeropage_addr

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
