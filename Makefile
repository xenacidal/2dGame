all: bin/2dGame

bin/2dGame: bin/main.o bin/draw.o bin/map.o bin/player.o
	gcc -I inc bin/main.o bin/draw.o bin/map.o bin/player.o -o bin/2dGame -lSDL2 -lSDL2_image

bin/main.o: src/main.c inc/draw.h inc/map.h inc/player.h
	gcc -I inc -c src/main.c -o bin/main.o -lSDL2 -lSDL2_image

bin/draw.o: src/draw.c inc/draw.h
	gcc -I inc -c src/draw.c -o bin/draw.o -lSDL2 -lSDL_image

bin/map.o: src/map.c inc/map.h
	gcc -I inc -c src/map.c -o bin/map.o

bin/player.o: src/player.c inc/player.h
	gcc -I inc -c src/player.c -o bin/player.o
