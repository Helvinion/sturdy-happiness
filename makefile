CC=tools/cc65/bin/cc65
CA=tools/cc65/bin/ca65
LD=tools/cc65/bin/ld65


all:
	$(CC) src/text.c    -t nes -O -T -I include/ -o compile/asm/text.s
	$(CC) src/palette.c -t nes -O -T -I include/ -o compile/asm/palette.s
	$(CC) src/main.c    -t nes -O -T -I include/ -o compile/asm/main.s
	$(CC) src/screen.c  -t nes -O -T -I include/ -o compile/asm/screen.s
	
	$(CA) compile/asm/text.s      -t nes -W 3 -s -v -o compile/obj/text.o
	$(CA) compile/asm/palette.s   -t nes -W 3 -s -v -o compile/obj/palette.o
	$(CA) compile/asm/main.s      -t nes -W 3 -s -v -o compile/obj/main.o
	$(CA) compile/asm/screen.s    -t nes -W 3 -s -v -o compile/obj/screen.o
	
	$(CA) src/asm/graphics.s  -t nes -W 3 -s -v -o compile/obj/graphics.o
	$(CA) src/asm/header.s    -t nes -W 3 -s -v -o compile/obj/header.o
	$(CA) src/asm/irq.s       -t nes -W 3 -s -v -o compile/obj/irq.o
	$(CA) src/asm/nmi.s       -t nes -W 3 -s -v -o compile/obj/nmi.o
	$(CA) src/asm/start.s     -t nes -W 3 -s -v -o compile/obj/start.o
	$(CA) src/asm/vectors.s   -t nes -W 3 -s -v -o compile/obj/vectors.o

	$(LD) -v -C link.ld -o rom.nes compile/obj/*.o lib/nes.lib