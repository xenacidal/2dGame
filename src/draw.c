#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "draw.h"
#include "map.h"

SDL_Surface *bmpg;
SDL_Surface *bmpb;
SDL_Surface *bmpp;
SDL_Surface *sprite;
SDL_Texture *texg;
SDL_Texture *texb;
SDL_Texture *texp;
SDL_Texture *texs;
SDL_Rect crect;

void initializeFrame(SDL_Renderer *ren) {
  bmpg = SDL_LoadBMP("../data/greensq.bmp");
  bmpb = SDL_LoadBMP("../data/bluesq.bmp");
  bmpp = SDL_LoadBMP("../data/pathsq.bmp");
  sprite = SDL_LoadBMP("../data/sprite.bmp");
  texg = SDL_CreateTextureFromSurface(ren, bmpg);
  texb = SDL_CreateTextureFromSurface(ren, bmpb);
  texp = SDL_CreateTextureFromSurface(ren, bmpp);
  texs = SDL_CreateTextureFromSurface(ren, sprite);
}

void destroyFrame() {
  SDL_FreeSurface(bmpg);
  SDL_FreeSurface(bmpb);
  SDL_FreeSurface(bmpp);
  SDL_FreeSurface(sprite);
  SDL_DestroyTexture(texg);
  SDL_DestroyTexture(texb);
  SDL_DestroyTexture(texp);
  SDL_DestroyTexture(texs);
}

void drawFrame(SDL_Renderer *ren, MapData *mData){
  //First clear the renderer
  SDL_RenderClear(ren);
  //Draw the texture
  int i, j;
  Tile **map = mData->map;
  int r = mData->rows, c = mData->cols;
  SDL_Rect dstrect;
  int rowAdjust = (WIDTH - (c * 50)) / 2;
  int colAdjust = (HEIGHT - (r * 50)) / 2;
  printf("rows: %d, cols: %d\n", r, c);
  for(i = 0; i < r; i++) {
    for(j = 0; j < c; j++) {
      dstrect.x = rowAdjust + j*50;
      dstrect.y = colAdjust + i*50;
      dstrect.w = 50;
      dstrect.h = 50;
      printf("%s ", (map[i] + j)->type);
      if(strcmp((map[i] + j)->type, "GRASS") == 0){
	SDL_RenderCopy(ren, texg, NULL, &dstrect);
      } else if(strcmp((map[i] + j)->type, "WATER") == 0){
	SDL_RenderCopy(ren, texb, NULL, &dstrect);
      } else if(strcmp((map[i] + j)->type, "PATH") == 0){
	SDL_RenderCopy(ren, texp, NULL, &dstrect);
      }
    }
  printf("\n");
  }
  //SDL_RenderCopy(ren, texs, NULL, &crect);
  //Update the screen
  SDL_RenderPresent(ren);

  SDL_Event test_event;
  while(1){
    SDL_PollEvent(&test_event);
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP]) {
      return;
    }
  }
}

/*
void drawFrame(SDL_Renderer *ren){
  int r = WIDTH/50, c = HEIGHT/50;
  int *map = (int*)malloc(r*c*sizeof(int));
  int i, j;
  srand(time(NULL));
  for(i = 0; i < r; i++){
    for(j = 0; j < c; j++){
      *(map + i*c + j) = 1 + (rand()%3);
    }
  }
  int frames = 0;
  while(frames <= 50){
    //First clear the renderer
    SDL_RenderClear(ren);
    //Draw the texture
    int i, j;
    for(i = 0; i < r; i++) {
      for(j = 0; j < c; j++) {
	SDL_Rect dstrect;
	dstrect.x = frames + i*50;
	dstrect.y = j*50;
	dstrect.w = 50;
	dstrect.h = 50;
	if(*(map + i*c + j) == 1){
	  SDL_RenderCopy(ren, texr, NULL, &dstrect);
	} else if(*(map + i*c + j) == 2){
	  SDL_RenderCopy(ren, texy, NULL, &dstrect);
	} else{
	  SDL_RenderCopy(ren, texb, NULL, &dstrect);
	}
      }
    }
    SDL_RenderCopy(ren, texs, NULL, &crect);
    //Update the screen
    SDL_RenderPresent(ren);
    //Take a quick break after all that hard work
    SDL_Delay(5);
    frames++;
  }
    SDL_Event test_event;
  while(1){
    SDL_PollEvent(&test_event);
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP]) {
      printf("<UP> is pressed.\n");
      SDL_DestroyTexture(texy);
      SDL_DestroyTexture(texb);
      SDL_DestroyTexture(texr);
      return;
    }
  }
}
*/
