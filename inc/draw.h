#ifndef INC_DRAW_H
#define INC_DRAW_H
#include "map.h"
#define WIDTH 850
#define HEIGHT 650


enum Direction{LEFT, RIGHT, UP, DOWN};

void initializeDraw(SDL_Renderer *ren);

void destoryFrame();

void drawFrame(SDL_Renderer *ren, MapData *mData);

#endif
