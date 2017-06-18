#ifndef INC_DRAW_H
#define INC_DRAW_H
#include "map.h"
#include "player.h"

enum Direction{LEFT, RIGHT, UP, DOWN};

void initializeDraw(SDL_Renderer *ren, SDL_Window *win);

void destoryFrame();

void drawInitialFrame(SDL_Renderer *ren, MapData *mData, Player *p);

void drawMove(SDL_Renderer *ren, MapData *mData, Player *p, int dir, int sprint);

void drawTurn(SDL_Renderer *ren, Player *p, int dir, MapData *m);

void resize(SDL_Window *win, SDL_Renderer *ren, MapData *mData, Player *p);

#endif
