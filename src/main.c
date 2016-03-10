#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "draw.h"
#include "map.h"
#include "player.h"

void initialize();
void exitGame();
void handleInputs();

SDL_Window *win;
SDL_Renderer *ren;
Player *p1;
MapData *map1;

int main(int argc, char* argv[]){
  initialize();
  handleInputs();
  exitGame();
  return 0;
}

void initialize(){
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  win = SDL_CreateWindow("2dGame", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  initializeFrame(ren);
  p1 = loadPlayer("../data/player1");
  map1 = createMap(p1->mapName);
  drawInitialFrame(ren, map1, p1);
  return;
} 

void exitGame(){
  destroyPlayer(p1);
  destroyFrame();
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  IMG_Quit();
  SDL_Quit();
  return;
}

void handleInputs(){

  SDL_Event event;
  MapData *cmap = map1;
  Tile **map = cmap->map;
  const Uint8 *state;

  while(1){
    SDL_WaitEvent(&event);
    state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT]){
      int direction;
      Tile *moveTile;
      if(state[SDL_SCANCODE_UP]){
	direction = 1;
	moveTile = (map[p1->ycoor - 1] + (p1->xcoor));
      } else if(state[SDL_SCANCODE_DOWN]){
	direction = 2;
	moveTile = (map[p1->ycoor + 1] + (p1->xcoor));
      } else if(state[SDL_SCANCODE_LEFT]){
	direction = 3;
	moveTile = (map[p1->ycoor] + (p1->xcoor - 1));
      } else {
	direction = 4;
	moveTile = (map[p1->ycoor] + (p1->xcoor + 1));
      }
      int use = moveTile->usable;
      if(p1->direction != direction){
	drawTurn(ren, p1, direction, cmap);
	p1->direction = direction;
      } else if(use == 1){
	if(state[SDL_SCANCODE_RSHIFT])
	  drawMove(ren, cmap, p1, direction, 3);
	else
	  drawMove(ren,cmap, p1, direction, 2);
	if(direction == 1)
	  p1->ycoor--;
	else if(direction == 2)
	  p1->ycoor++;
	else if(direction == 3)
	  p1->xcoor--;
	else 
	  p1->xcoor++;
      } else if(use >= 4 && use <=8){
	MapData *oldmap = cmap;
	cmap = createMap(moveTile->change);
	destroyMap(oldmap);
	map = cmap->map;

	if(use == 4){
	  p1->xcoor = cmap->load4x;
	  p1->ycoor = cmap->load4y;
	} else if(use == 5){
	  p1->xcoor = cmap->load5x;
	  p1->ycoor = cmap->load5y;
	} else if(use == 6){
	  p1->xcoor = cmap->load6x;
	  p1->ycoor = cmap->load6y;
	} else if(use == 7){
	  p1->xcoor = cmap->load7x;
	  p1->ycoor = cmap->load7y;
	} else if(use == 8) {
	  strncpy(cmap->tempMap, p1->mapName, 25);
	  strncpy(p1->prevMap, p1->mapName, 25);
	  p1->prevx = cmap->tempx = p1->xcoor;
	  p1->prevy = cmap->tempy = p1->ycoor;
	  p1->xcoor = cmap->load4x;
	  p1->ycoor = cmap->load4y;
	}
	strncpy(p1->mapName, moveTile->change, 25);
	drawInitialFrame(ren, cmap, p1);
      } else if(use == 9){
	if(strcmp(cmap->tempMap, "NULL") == 0){
	  strncpy(p1->mapName, p1->prevMap, 25);
	  p1->xcoor = p1->prevx;
	  p1->ycoor = p1->prevy;
	} else {
	  strncpy(p1->mapName, cmap->tempMap, 25);
	  p1->xcoor = cmap->tempx;
	  p1->ycoor = cmap->tempy;
	}
	MapData *oldmap = cmap;
	cmap = createMap(p1->mapName);
	destroyMap(oldmap);
	map = cmap->map;
	drawInitialFrame(ren, cmap, p1);
      }
    }
    
    if(state[SDL_SCANCODE_RETURN]){
      savePlayer(p1);
      destroyMap(cmap);
      return;
    }
  }
}
