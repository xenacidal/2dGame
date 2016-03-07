all: bin/2dGame

bin/2dGame: bin/main.o bin/draw.o bin/map.o
	gcc -I inc bin/main.o bin/draw.o bin/map.o -o bin/2dGame -lSDL2

bin/main.o: src/main.c inc/draw.h inc/map.h
	gcc -I inc -c src/main.c -o bin/main.o -lSDL2

bin/draw.o: src/draw.c inc/draw.h inc/map.h
	gcc -I inc -c src/draw.c -o bin/draw.o -lSDL2

bin/map.o: src/map.c inc/map.h
	gcc -I inc -c src/map.c -o bin/map.o
