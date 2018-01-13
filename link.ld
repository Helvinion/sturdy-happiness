MEMORY
{
	########## Description du fichier de sortie (ROM) ###########
	
    # Le Header se place au début du fichier ROM et identifie un jeu NES.
    HEADER: start = $0, size = $10, file = %O ,fill = yes;

	# La PRG est la ROM proprement dite. Son adresse virtuelle est en 0x8000
	# Elle fait 0x8000 cases moins 6.
    PRG: start = $8000, size = $3ffa, file = %O ,fill = yes, define = yes;
	
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
	# Plutot evident, le segment HEADER remplie la zone memoire HEADER
    HEADER:   load = HEADER,         type = ro;
	
	# Le segment startup est destiné à contenir le code qui initialise un environnement C
    STARTUP:  load = PRG,            type = ro,  define = yes;
	
	# Le segment LowCode est garanti comme accessible depuis toutes les banques de données (utile si on en utilise plusieurs)
    LOWCODE:  load = PRG,            type = ro,                optional = yes;
    
	# Le segment INIT est sensé contenir des procédires d'initialisation... Je ne l'utilise pas à l'écriture de ces lignes.
	INIT:     load = PRG,            type = ro,  define = yes, optional = yes;
	
	# Le segment CODE contient le binaire du programme du jeu lui même
    CODE:     load = PRG,            type = ro,  define = yes;
    
	# Ce segment contient les données constantes (chaines, etc.)
	RODATA:   load = PRG,            type = ro,  define = yes;
    
	# Ce segment contient les variables globales avec leu initialisation. Il sera copié en RAM au démarrage
	DATA:     load = PRG, run = RAM, type = rw,  define = yes;
	
	# Ce segment contient les 3 adresses des trois interruptions du jeu.
    VECTORS:  load = VECTORS,        type = rw;
	
	# Ce segment contient... les sprites et les tiles
	GRAPHICS: load = CHR,            type = ro;
	
	# Comme DATA sauf que son contenu *doit* être initialisé à 0 avant de lancer le code C.
    BSS:      load = RAM,             type = bss, define = yes;
	
	# La zéropage, evidemment.
    ZEROPAGE: load = ZP,              type = zp;
}

# Je ne suis pas sur, mais je crois que le code C a besoin de cette section pour linker.
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
