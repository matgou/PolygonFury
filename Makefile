CC=gcc
CFLAGS=-W -Wall -I./include -I/usr/include/SDL
LFLAGS=-I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -L/usr/lib -lSDL lib/libSDL_draw.a -lSDL_ttf

EXEC=bin/PolygonFury
SRC= $(wildcard *.c)
OBJ= $(addprefix obj/,$(SRC:.c=.o))

all: $(EXEC)

bin/PolygonFury: $(OBJ)
	gcc -o $@ $^ $(LFLAGS)
	cp -r img/ bin/img
	cp *.ttf bin/
	cp niveaux.csv bin/
	cp run.sh bin/
obj/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf obj/*.o

mrproper: clean
	rm -rf bin/*
