#ifndef INC_DRAW_H
#define INC_DRAW_H
#include "map.h"
#include "player.h"
#define WIDTH 850
#define HEIGHT 650


enum Direction{LEFT, RIGHT, UP, DOWN};

void initializeDraw(SDL_Renderer *ren);

void destoryFrame();

void drawInitialFrame(SDL_Renderer *ren, MapData *mData, Player *p);

void drawMove(SDL_Renderer *ren, MapData *mData, Player *p, int dir);

#endif
