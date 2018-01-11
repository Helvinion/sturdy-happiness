CC=tools/cc65/bin/cc65
CA=tools/cc65/bin/ca65
LD=tools/cc65/bin/ld65
NES=tools/fceux/fceux
MV=mv
RM=rm
PYTHON=tools/python/python

CCFLAGS=-g -t nes -O -T -I include/ -I animations/
CAFLAGS=-g -t nes -W 3 -s -v

SRC_ASM=./asm/graphics.asm \
./asm/header.asm           \
./asm/irq.asm              \
./asm/nmi.asm              \
./asm/start.asm            \
./asm/registres_cc65.asm   \
./asm/vectors.asm

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
./moteur.c

OBJ_C=$(patsubst ./%.c,./compile/obj/%.o,$(SRC_C))
OBJ_ASM=$(patsubst ./asm/%.asm,./compile/obj/%.o,$(SRC_ASM))
OBJ=$(OBJ_C) $(OBJ_ASM)

all: rom.nes

# C -> ASM
.PRECIOUS: compile/asm/%.asm

compile/asm/%.asm:src/%.c
	$(CC) $< $(CCFLAGS) -o $@

# ASM -> O
compile/obj/%.o:src/asm/%.asm
	$(CA) $< $(CAFLAGS) -o $@

# ASM -> O
compile/obj/%.o:compile/asm/%.asm
	$(CA) $< $(CAFLAGS) -o $@

rom.nes: $(OBJ) link.ld lib/nes.lib
	$(LD) -v -C link.ld -o rom.nes $(OBJ) lib/nes.lib -vm -m debug/rom.map -Ln debug/labels.txt
	$(PYTHON) fceux_symbols.py
	
play: rom.nes
	$(NES) rom.nes

clean::
	$(RM) -f compile/asm/*
	$(RM) -f compile/obj/*
	$(RM) -f debug/*
	$(RM) -f rom.nes
	$(RM) -f *.nl
