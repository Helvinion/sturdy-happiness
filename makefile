CC=tools/cc65/bin/cc65
CA=tools/cc65/bin/ca65
LD=tools/cc65/bin/ld65
NES=tools/fceux/fceux
RM=rm

all:: play

asm:
	$(CC) src/text.c    -t nes -O -T -I include/ -o compile/asm/text.asm
	$(CC) src/palette.c -t nes -O -T -I include/ -o compile/asm/palette.asm
	$(CC) src/main.c    -t nes -O -T -I include/ -o compile/asm/main.asm
	$(CC) src/screen.c  -t nes -O -T -I include/ -o compile/asm/screen.asm

obj: asm
	$(CA) compile/asm/text.asm      -t nes -W 3 -s -v -o compile/obj/text.o
	$(CA) compile/asm/palette.asm   -t nes -W 3 -s -v -o compile/obj/palette.o
	$(CA) compile/asm/main.asm      -t nes -W 3 -s -v -o compile/obj/main.o
	$(CA) compile/asm/screen.asm    -t nes -W 3 -s -v -o compile/obj/screen.o
	
	$(CA) src/asm/graphics.asm  -t nes -W 3 -s -v -o compile/obj/graphics.o
	$(CA) src/asm/header.asm    -t nes -W 3 -s -v -o compile/obj/header.o
	$(CA) src/asm/irq.asm       -t nes -W 3 -s -v -o compile/obj/irq.o
	$(CA) src/asm/nmi.asm       -t nes -W 3 -s -v -o compile/obj/nmi.o
	$(CA) src/asm/start.asm     -t nes -W 3 -s -v -o compile/obj/start.o
	$(CA) src/asm/vectors.asm   -t nes -W 3 -s -v -o compile/obj/vectors.o
	
rom.nes: obj
	$(LD) -v -C link.ld -o rom.nes compile/obj/*.o lib/nes.lib
	
play: rom.nes
	$(NES) rom.nes

clean::
	$(RM) -f compile/asm/*
	$(RM) -f compile/obj/*
	$(RM) -f rom.nes
