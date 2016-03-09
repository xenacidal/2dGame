#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "draw.h"
#include "map.h"
#include "player.h"

SDL_Surface *bmpg;
SDL_Surface *bmpb;
SDL_Surface *bmpp;
SDL_Surface *bmpr;
SDL_Surface *pngs;
SDL_Texture *texg;
SDL_Texture *texb;
SDL_Texture *texp;
SDL_Texture *texr;
SDL_Texture *texs;
int textureH, textureW, spriteTexWidth, spriteTexHeight, spriteFrameW, spriteFrameH;
SDL_Rect playerRect;
SDL_Rect plrect;
SDL_Rect dstrect;
SDL_Rect crect;


void initializeFrame(SDL_Renderer *ren) {
  bmpg = SDL_LoadBMP("../data/greensq.bmp");
  bmpb = SDL_LoadBMP("../data/bluesq.bmp");
  bmpp = SDL_LoadBMP("../data/pathsq.bmp");
  bmpr = SDL_LoadBMP("../data/redsq.bmp");
  pngs = IMG_Load("../data/sprite.png");

  texs = SDL_CreateTextureFromSurface(ren, pngs);
  SDL_QueryTexture(texs, NULL, NULL, &spriteTexWidth, &spriteTexHeight);

  texg = SDL_CreateTextureFromSurface(ren, bmpg);
  texb = SDL_CreateTextureFromSurface(ren, bmpb);
  texp = SDL_CreateTextureFromSurface(ren, bmpp);
  texr = SDL_CreateTextureFromSurface(ren, bmpr);

  spriteFrameW = spriteTexWidth/3;
  spriteFrameH = spriteTexHeight/4;
  playerRect.x = playerRect.y = 0;
  playerRect.w = spriteFrameW;
  playerRect.h = spriteFrameH;

  textureH = 50; 
  textureW = 50;

  plrect.x = WIDTH/2; 
  if(plrect.x%2 == 1)
    plrect.x -= 25;
  crect.x = plrect.x;
  plrect.x += (textureW-spriteFrameW) / 2;
  plrect.y = HEIGHT/2;
  if(plrect.y%2 == 1)
    plrect.y -= 25;
  crect.y = plrect.y;
  plrect.y +=(textureH-spriteFrameH) / 2;

  plrect.w = spriteFrameW;
  plrect.h = spriteFrameH;
  dstrect.w = textureW;
  dstrect.h = textureH;

  crect.w = textureW;
  crect.h = textureH;
}

void destroyFrame() {
  SDL_FreeSurface(bmpg);
  SDL_FreeSurface(bmpb);
  SDL_FreeSurface(bmpp);
  SDL_FreeSurface(bmpr);
  SDL_FreeSurface(pngs);
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
 
  int pdirection = p->direction, px = p->xcoor, py = p->ycoor;
  Tile **map = mData->map;
  int r = mData->rows, c = mData->cols;

  int rowAdjust = (floor(WIDTH/100)  * textureW) - px*textureW;
  int colAdjust = (floor(HEIGHT/100) * textureH) - py*textureH;

  int i, j;
  for(i = 0; i < r; i++) {
    for(j = 0; j < c; j++) {
      dstrect.x = rowAdjust + j*textureW;
      dstrect.y = colAdjust + i*textureH;
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

  if(pdirection == 1){
    playerRect.x = spriteFrameW;
    playerRect.y = spriteFrameH * 3;
  } else if(pdirection == 2){
    playerRect.x = spriteFrameW;
    playerRect.y = 0;
  } else if(pdirection == 3){
    playerRect.x = spriteFrameW;
    playerRect.y = spriteFrameH;
  } else {
    playerRect.x = spriteFrameW;
    playerRect.y = spriteFrameH *2;
  }
  

  SDL_RenderCopy(ren, texs, &playerRect, &plrect);
  //Update the screen
  SDL_RenderPresent(ren);
}

void drawMove(SDL_Renderer *ren, MapData *mData, Player *p, int dir) {
  int px = p->xcoor, py = p->ycoor;
  Tile **map = mData->map;
  int r = mData->rows, c = mData->cols;

  int rowAdjust = (floor(WIDTH/100)  * textureW) - px*textureW;
  int colAdjust = (floor(HEIGHT/100) * textureH) - py*textureH;

  SDL_Rect dstrect;
  int i, j;
  int frames = 1;
  int framerate = 50;
  int walkcount = 1;

  while(frames <= framerate){
    //First clear the renderer
    SDL_RenderClear(ren);
    //Draw the texture

    int xchange = 0, ychange = 0;
    if(dir == 1){
      ychange = frames;
    } else if(dir == 2) {
      ychange = -frames;
    } else if(dir == 3) {
      xchange = frames; 
    } else if(dir == 4){
      xchange = -frames;
    }

    for(i = 0; i < r; i++) {
      for(j = 0; j < c; j++) {
	dstrect.x = rowAdjust + j*textureW + xchange;
	dstrect.y = colAdjust + i*textureH + ychange;
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

    if(walkcount == 1){
      if(playerRect.x >= spriteFrameW*2)
	playerRect.x = 0;
      else{
	playerRect.x += spriteFrameW;
      }
    }
  
    SDL_RenderCopy(ren, texs, &playerRect, &plrect);
  
    walkcount++;
    if(walkcount >= 10)
      walkcount = 1;
    SDL_RenderCopy(ren, texs, &playerRect, &plrect);
    //Update the screen
    SDL_RenderPresent(ren);
    //Take a quick break after all that hard work
    SDL_Delay(1);
    frames++;
  }
}

void drawTurn(SDL_Renderer *ren, Player *p, int dir, MapData *m){
  int x = p->xcoor, y = p->ycoor;
  Tile** map = m->map;
  if(strcmp((map[y] + x)->type, "GRASS") == 0){
    SDL_RenderCopy(ren, texg, NULL, &crect);
  } else if(strcmp((map[y] + x)->type, "WATER") == 0){
    SDL_RenderCopy(ren, texb, NULL, &crect);
  } else if(strcmp((map[y] + x)->type, "PATH") == 0){
    SDL_RenderCopy(ren, texp, NULL, &crect);
  } else {
    SDL_RenderCopy(ren, texr, NULL, &crect);
  }
  
  int cdir = p->direction;
  if(dir == 1){
    playerRect.x = spriteFrameW;
    playerRect.y = spriteFrameH * 3;
  } else if(dir == 2){
    playerRect.x = spriteFrameW;
    playerRect.y = 0;
  } else if(dir == 3){
    playerRect.x = spriteFrameW;
    playerRect.y = spriteFrameH;
  } else {
    playerRect.x = spriteFrameW;
    playerRect.y = spriteFrameH *2;
  }
  SDL_RenderCopy(ren, texs, &playerRect, &plrect);
  SDL_RenderPresent(ren);
}
