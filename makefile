CC=tools/cc65/bin/cc65
CA=tools/cc65/bin/ca65
LD=tools/cc65/bin/ld65
NES=tools/fceux/fceux
MV=mv
RM=rm
MKDIR=mkdir
PYTHON=tools/python/python

CCFLAGS=-g -t nes -O -T -I include/ -I animations/include
CAFLAGS=-g -t nes -W 3 -s -v

SRC_ASM=./asm/graphics.asm \
./asm/header.asm           \
./asm/irq.asm              \
./asm/nmi.asm              \
./asm/start.asm            \
./asm/registres_cc65.asm   \
./asm/vectors.asm          \
./asm/tileset.asm          \
./asm/utile.asm

SRC_C=./avatar.c \
./main.c         \
./manette.c      \
./messages.c     \
./musique.c      \
./palette.c      \
./ecran.c        \
./sprites.c      \
./text.c         \
./physique.c     \
./tiles.c        \
./moteur.c       \
./niveau_bis.c

ANIMS_C=./animations/src/G_Jolivet.c

OBJ_ANIMS=$(patsubst ./animations/src/%.c,./compile/obj/animations/%.o,$(ANIMS_C))
OBJ_C=$(patsubst ./%.c,./compile/obj/%.o,$(SRC_C))
OBJ_ASM=$(patsubst ./asm/%.asm,./compile/obj/%.o,$(SRC_ASM))
OBJ=$(OBJ_C) $(OBJ_ASM) $(OBJ_ANIMS)

all: prepare rom.nes

# C -> ASM
.PRECIOUS: compile/asm/%.asm compile/asm/animations/%.asm


compile/asm/%.asm:src/%.c
	$(CC) $< $(CCFLAGS) -o $@

compile/asm/animations/%.asm:animations/src/%.c
	$(CC) $< $(CCFLAGS) -o $@

# ASM -> O
compile/obj/%.o:src/asm/%.asm
	$(CA) $< $(CAFLAGS) -o $@

# ASM -> O
compile/obj/%.o:compile/asm/%.asm
	$(CA) $< $(CAFLAGS) -o $@

rom.nes: $(OBJ) link.ld lib/nes.lib graphics/noobnes.chr
	$(LD) -v -C link.ld -o rom.nes $(OBJ) lib/nes.lib -vm -m debug/rom.map -Ln debug/labels.txt
	$(PYTHON) fceux_symbols.py

play: rom.nes
	$(NES) rom.nes

prepare:
	$(MKDIR) -p compile/asm/animations
	$(MKDIR) -p compile/obj/animations
	$(MKDIR) -p debug

clean::
	$(RM) -f compile/asm/*.asm
	$(RM) -f compile/asm/animations/*.asm
	$(RM) -f compile/obj/*.o
	$(RM) -f compile/obj/animations/*.o
	$(RM) -f debug/*
	$(RM) -f rom.nes
	$(RM) -f rom.nes.deb
	$(RM) -f *.nl

# EOF
