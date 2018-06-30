CC = gcc
OBJS = main.o blit.o naves.o thanos.o fuego.o escudo.o niveles.o util.o
CFLAGS = -c -O2 -Wall
LIB = -lncurses

galaga: $(OBJS)
	$(CC) $(OBJS) $(LIB) -o galaga
	strip galaga

main.o: main.c

blit.o: blit.c

naves.o: naves.c

thanos.o: thanos.c

fuego.o: fuego.c

escudo.o: escudo.c

niveles.o: niveles.c

util.o: util.c

clean:
	rm -f ./*.o

distclean: clean
	rm -f galaga

