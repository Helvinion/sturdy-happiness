MEMORY
{
	########## Description du fichier de sortie (ROM) ###########
	
    # Le Header se place au début du fichier ROM et identifie un jeu NES.
    HEADER: start = $0, size = $10, file = %O ,fill = yes;

	# La PRG est la ROM proprement dite. Son adresse virtuelle est en 0x8000
	# Elle fait 0x8000 cases moins 6.
    PRG: start = $8000, size = $7ffa, file = %O ,fill = yes, define = yes;
	
    # Cette zone de 6 octets indique la localisation des 3 interruptions
	# de la NES : nmi, start et irq.
    VECTORS: start = $fffa, size = $6, file = %O, fill = yes;

	# Cette zone contiendra les graphismes du jeu.
	# Je je comprend pas encore pourquoi elle doit être chargée de cette manière.
	CHR: start = $0000, size = $2000, file = %O, fill = yes;

	############# Description de la RAM ######################
	
	# La ZeroPage : une zone RAM facilement accessible de 256 cases.
	# Les 32 premières sont utilisées par le code C.
    ZP:  start = $00, size = $100, type = rw, define = yes;

	# La zone entre la ZeroPage et le début de la RAM, soit
	# deux pages de 256 octets, servent à la pile et à un buffer
	# spécial utilisé pour les sprites.
	
	# Le début de la RAM normale proprement dite. Elle fait 5 pages de 256 cases.
    RAM: start = $0300, size = $0500, define = yes;
}

SEGMENTS {
    HEADER:   load = HEADER,         type = ro;
    STARTUP:  load = PRG,            type = ro,  define = yes;
    LOWCODE:  load = PRG,            type = ro,                optional = yes;
    INIT:     load = PRG,            type = ro,  define = yes, optional = yes;
    CODE:     load = PRG,            type = ro,  define = yes;
    RODATA:   load = PRG,            type = ro,  define = yes;
    DATA:     load = PRG, run = RAM, type = rw,  define = yes;
    VECTORS:  load = VECTORS,        type = rw;
	GRAPHICS: load = CHR,            type = ro;
	
    BSS:      load = RAM,             type = bss, define = yes;
    HEAP:     load = RAM,             type = bss, optional = yes;
    ZEROPAGE: load = ZP,              type = zp;
}

FEATURES {
    CONDES: segment = INIT,
	    type = constructor,
	    label = __CONSTRUCTOR_TABLE__,
	    count = __CONSTRUCTOR_COUNT__;
    CONDES: segment = RODATA,
	    type = destructor,
	    label = __DESTRUCTOR_TABLE__,
	    count = __DESTRUCTOR_COUNT__;
    CONDES: type = interruptor,
	    segment = RODATA,
	    label = __INTERRUPTOR_TABLE__,
	    count = __INTERRUPTOR_COUNT__;
}


#SYMBOLS {
#    __STACKSIZE__: type = weak, value = $0300;   # 3 pages stack
#	}
