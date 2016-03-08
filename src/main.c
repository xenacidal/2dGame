#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
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
  win = SDL_CreateWindow("2dGame", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  initializeFrame(ren);
  p1 = loadPlayer("../data/player1.txt");
  map1 = createMap(p1->mapName);
  drawInitialFrame(ren, map1, p1);
  return;
} 

void exitGame(){
  destroyPlayer(p1);
  destroyMap(map1);
  destroyFrame();
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return;
}

void handleInputs(){
  SDL_Event event;
  MapData *cmap = map1;
  Tile **map = cmap->map;
  while(1){
    SDL_PollEvent(&event);
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP]) {
      if((map[p1->ycoor - 1] + (p1->xcoor))->usable == 1){
	drawMove(ren, cmap, p1, 1);
	p1->ycoor--;
	printf("final x: %d y: %d\n",p1->xcoor, p1->ycoor);
      }
    }
    if(state[SDL_SCANCODE_DOWN]){
      if((map[p1->ycoor + 1] + (p1->xcoor))->usable == 1){
	drawMove(ren, cmap, p1, 2);
	p1->ycoor++;
	printf("final x: %d y: %d\n",p1->xcoor, p1->ycoor);
      }
    }
    if(state[SDL_SCANCODE_LEFT]){
      if((map[p1->ycoor] + (p1->xcoor - 1))->usable == 1){
	drawMove(ren, cmap, p1, 3);
	p1->xcoor--;
	printf("final x: %d y: %d\n",p1->xcoor, p1->ycoor);
      }
    }
    if(state[SDL_SCANCODE_RIGHT]){
      if((map[p1->ycoor] + (p1->xcoor + 1))->usable == 1){
	drawMove(ren, cmap, p1, 4);
	p1->xcoor++;
	printf("final x: %d y: %d\n",p1->xcoor, p1->ycoor);
      }
    }
    if(state[SDL_SCANCODE_RETURN]){
      return;
    }
  }
}
