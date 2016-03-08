#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "draw.h"
#include "map.h"
#include "player.h"

SDL_Surface *bmpg;
SDL_Surface *bmpb;
SDL_Surface *bmpp;
SDL_Surface *bmpr;
SDL_Surface *sprite;
SDL_Texture *texg;
SDL_Texture *texb;
SDL_Texture *texp;
SDL_Texture *texr;
SDL_Texture *texs;

void initializeFrame(SDL_Renderer *ren) {
  bmpg = SDL_LoadBMP("../data/greensq.bmp");
  bmpb = SDL_LoadBMP("../data/bluesq.bmp");
  bmpp = SDL_LoadBMP("../data/pathsq.bmp");
  bmpr = SDL_LoadBMP("../data/redsq.bmp");
  sprite = SDL_LoadBMP("../data/sprite.bmp");
  texg = SDL_CreateTextureFromSurface(ren, bmpg);
  texb = SDL_CreateTextureFromSurface(ren, bmpb);
  texp = SDL_CreateTextureFromSurface(ren, bmpp);
  texr = SDL_CreateTextureFromSurface(ren, bmpr);
  texs = SDL_CreateTextureFromSurface(ren, sprite);
}

void destroyFrame() {
  SDL_FreeSurface(bmpg);
  SDL_FreeSurface(bmpb);
  SDL_FreeSurface(bmpp);
  SDL_FreeSurface(bmpr);
  SDL_FreeSurface(sprite);
  SDL_DestroyTexture(texg);
  SDL_DestroyTexture(texb);
  SDL_DestroyTexture(texp);
  SDL_DestroyTexture(texr);
  SDL_DestroyTexture(texs);
}

void drawInitialFrame(SDL_Renderer *ren, MapData *mData, Player *p){
  //First clear the renderer
  SDL_RenderClear(ren);
  //Draw the texture
  
  int px = p->xcoor, py = p->ycoor;
  Tile **map = mData->map;
  int r = mData->rows, c = mData->cols;

  int rowAdjust = (floor(WIDTH/100)  * 50) - px*50;
  int colAdjust = (floor(HEIGHT/100) * 50) - py*50;
  //int rowAdjust = (WIDTH - (r * 50)) / 2;
  //int colAdjust = (HEIGHT - (c * 50)) / 2;

  SDL_Rect dstrect;
  int i, j;
  int xstart = px - floor(WIDTH/100);
  if(xstart < 0)
    xstart = 0;
  int xend = xstart + floor(WIDTH/50);
  if(xend > r)
    xend = r;
  int ystart = py - floor(HEIGHT/100);
  if(ystart < 0)
    ystart = 0;
  int yend = xstart + floor(HEIGHT/50);
  if(yend > c)
    yend = c;
  //printf("xstart: %d xend: %d ystart: %d yend: %d\n", xstart, xend, ystart, yend);
  for(i = xstart; i < xend; i++) {
    for(j = ystart; j < yend; j++) {
      dstrect.x = rowAdjust + j*50;
      dstrect.y = colAdjust + i*50;
      dstrect.w = 50;
      dstrect.h = 50;
      if(strcmp((map[i] + j)->type, "GRASS") == 0){
	SDL_RenderCopy(ren, texg, NULL, &dstrect);
      } else if(strcmp((map[i] + j)->type, "WATER") == 0){
	SDL_RenderCopy(ren, texb, NULL, &dstrect);
      } else if(strcmp((map[i] + j)->type, "PATH") == 0){
	SDL_RenderCopy(ren, texp, NULL, &dstrect);
      } else {
	SDL_RenderCopy(ren,texr, NULL, &dstrect);
      }
    }
  }

  SDL_Rect plrect;
  plrect.x = WIDTH/2; 
  if(plrect.x%2 == 1)
    plrect.x -= 25;
  plrect.y = HEIGHT/2;
  if(plrect.y%2 == 1)
    plrect.y -= 25;
  plrect.w = 50;
  plrect.h = 50;
  
  SDL_RenderCopy(ren, texs, NULL, &plrect);
  //Update the screen
  SDL_RenderPresent(ren);
}

void drawMove(SDL_Renderer *ren, MapData *mData, Player *p, int dir) {
  int frames = 1;

  int px = p->xcoor, py = p->ycoor;
  printf("start x:%d y:%d\n", px, py);
  Tile **map = mData->map;
  int r = mData->rows, c = mData->cols;

  int rowAdjust = (floor(WIDTH/100)  * 50) - px*50;
  int colAdjust = (floor(HEIGHT/100) * 50) - py*50;

  SDL_Rect dstrect;
  int i, j;
  int xstart = px - floor(WIDTH/100);
  if(xstart < 0)
    xstart = 0;
  int xend = xstart + floor(WIDTH/50);
  if(xend > r)
    xend = r;
  int ystart = py - floor(HEIGHT/100);
  if(ystart < 0)
    ystart = 0;
  int yend = xstart + floor(HEIGHT/50);
  if(yend > c)
    yend = c;
  while(frames <= 50){
    //First clear the renderer
    SDL_RenderClear(ren);
    //Draw the texture
    for(i = xstart; i < xend; i++) {
      for(j = ystart; j < yend; j++) {

	if(dir == 1){
	  dstrect.x = rowAdjust + j*50;
	  dstrect.y = colAdjust + i*50 + frames;
	} else if(dir == 2) {
	  dstrect.x = rowAdjust + j*50;
	  dstrect.y = colAdjust + i*50 - frames;
	} else if(dir == 3) {
	  dstrect.x = rowAdjust + j*50 + frames;
	  dstrect.y = colAdjust + i*50 ;
	} else if(dir == 4){
	  dstrect.x = rowAdjust + j*50 - frames;
	  dstrect.y = colAdjust + i*50;
	}
	dstrect.w = 50;
	dstrect.h = 50;
	if(strcmp((map[i] + j)->type, "GRASS") == 0){
	  SDL_RenderCopy(ren, texg, NULL, &dstrect);
	} else if(strcmp((map[i] + j)->type, "WATER") == 0){
	  SDL_RenderCopy(ren, texb, NULL, &dstrect);
	} else if(strcmp((map[i] + j)->type, "PATH") == 0){
	  SDL_RenderCopy(ren, texp, NULL, &dstrect);
	} else {
	  SDL_RenderCopy(ren,texr, NULL, &dstrect);
	}
      }
    }
    SDL_Rect plrect;
    plrect.x = WIDTH/2; 
    if(plrect.x%2 == 1)
      plrect.x -= 25;
    plrect.y = HEIGHT/2;
    if(plrect.y%2 == 1)
      plrect.y -= 25;
    plrect.w = 50;
    plrect.h = 50;
    SDL_RenderCopy(ren, texs, NULL, &plrect);
    //Update the screen
    SDL_RenderPresent(ren);
    //Take a quick break after all that hard work
    SDL_Delay(5);
    frames++;
  }
}
