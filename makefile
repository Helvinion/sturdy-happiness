CC=tools/cc65/bin/cc65
CA=tools/cc65/bin/ca65
LD=tools/cc65/bin/ld65
NES=tools/fceux/fceux
NLGEN=tools/nlgen/nlgen
MV=mv
RM=rm

all:: play

asm:
	$(CC) src/text.c     -g -t nes -O -T -I include/ -o compile/asm/text.asm
	$(CC) src/palette.c  -g -t nes -O -T -I include/ -o compile/asm/palette.asm
	$(CC) src/main.c     -g -t nes -O -T -I include/ -o compile/asm/main.asm
	$(CC) src/screen.c   -g -t nes -O -T -I include/ -o compile/asm/screen.asm
	$(CC) src/tiles.c    -g -t nes -O -T -I include/ -o compile/asm/tiles.asm
	$(CC) src/messages.c -g -t nes -O -T -I include/ -o compile/asm/messages.asm
	$(CC) src/sprites.c  -g -t nes -O -T -I include/ -o compile/asm/sprites.asm
	$(CC) src/manette.c  -g -t nes -O -T -I include/ -o compile/asm/manette.asm
	$(CC) src/avatar.c   -g -t nes -O -T -I include/ -o compile/asm/avatar.asm
	
obj: asm
	$(CA) compile/asm/text.asm      -l -g -t nes -W 3 -s -v -o compile/obj/text.o
	$(CA) compile/asm/palette.asm   -l -g -t nes -W 3 -s -v -o compile/obj/palette.o
	$(CA) compile/asm/main.asm      -l -g -t nes -W 3 -s -v -o compile/obj/main.o
	$(CA) compile/asm/screen.asm    -l -g -t nes -W 3 -s -v -o compile/obj/screen.o
	$(CA) compile/asm/tiles.asm     -l -g -t nes -W 3 -s -v -o compile/obj/tiles.o
	$(CA) compile/asm/messages.asm  -l -g -t nes -W 3 -s -v -o compile/obj/messages.o
	$(CA) compile/asm/sprites.asm   -l -g -t nes -W 3 -s -v -o compile/obj/sprites.o
	$(CA) compile/asm/manette.asm   -l -g -t nes -W 3 -s -v -o compile/obj/manette.o
	$(CA) compile/asm/avatar.asm   -l -g -t nes -W 3 -s -v -o compile/obj/avatar.o
	
	$(CA) src/asm/graphics.asm  -l -g -t nes -W 3 -s -v -o compile/obj/graphics.o
	$(CA) src/asm/header.asm    -l -g -t nes -W 3 -s -v -o compile/obj/header.o
	$(CA) src/asm/irq.asm       -l -g -t nes -W 3 -s -v -o compile/obj/irq.o
	$(CA) src/asm/nmi.asm       -l -g -t nes -W 3 -s -v -o compile/obj/nmi.o
	$(CA) src/asm/start.asm     -l -g -t nes -W 3 -s -v -o compile/obj/start.o
	$(CA) src/asm/vectors.asm   -l -g -t nes -W 3 -s -v -o compile/obj/vectors.o
	
	$(MV) src/asm/*.lst     debug/
	$(MV) compile/asm/*.lst debug/
	
rom.nes: obj
	$(LD) -v -C link.ld -o rom.nes compile/obj/*.o lib/nes.lib -m debug/rom.map
	$(NLGEN) -rom rom.nes -nl 0 STARTUP 8000 -nl 0 INIT 81D1 -nl 0 CODE 8201  -lst debug/graphics.lst  -lst debug/header.lst  -lst debug/irq.lst  -lst debug/main.lst  -lst debug/nmi.lst  -lst debug/palette.lst  -map debug/rom.map  -lst debug/screen.lst  -lst debug/start.lst  -lst debug/text.lst  -lst debug/tiles.lst  -lst debug/vectors.lst
	
play: rom.nes
	$(NES) rom.nes

clean::
	$(RM) -f compile/asm/*
	$(RM) -f compile/obj/*
	$(RM) -f debug/*
	$(RM) -f rom.nes
