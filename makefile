CC=tools/cc65/bin/cc65
CA=tools/cc65/bin/ca65
LD=tools/cc65/bin/ld65
NES=tools/fceux/fceux
MV=mv
RM=rm

SRC_ASM=./asm/graphics.asm \
./asm/header.asm           \
./asm/irq.asm              \
./asm/nmi.asm              \
./asm/start.asm            \
./asm/vectors.asm

SRC_C=./avatar.c \
./main.c         \
./manette.c      \
./messages.c     \
./musique.c      \
./palette.c      \
./screen.c       \
./sprites.c      \
./text.c         \
./tiles.c

OBJ_C=$(patsubst ./%.c,./compile/obj/%.o,$(SRC_C))
OBJ_ASM=$(patsubst ./asm/%.asm,./compile/obj/%.o,$(SRC_ASM))
OBJ=$(OBJ_C) $(OBJ_ASM)

all:: play

# C -> ASM
compile/asm/%.asm:src/%.c
	$(CC) $<     -g -t nes -O -T -I include/ -o $@

# ASM -> O
compile/obj/%.o:src/asm/%.asm
	$(CA) $<      -g -t nes -W 3 -s -v -o $@

# ASM -> O
compile/obj/%.o:compile/asm/%.asm
	$(CA) $<      -g -t nes -W 3 -s -v -o $@

rom.nes: $(OBJ) link.ld lib/nes.lib
	$(LD) -v -C link.ld -o rom.nes $(OBJ) lib/nes.lib -m debug/rom.map
	
play: rom.nes
	$(NES) rom.nes

clean::
	$(RM) -f compile/asm/*
	$(RM) -f compile/obj/*
	$(RM) -f debug/*
	$(RM) -f rom.nes
