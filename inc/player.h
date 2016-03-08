#ifndef INC_PLAYER_H
#define INC_PLAYER_H

struct playerData{
  char mapName[25];
  int xcoor;
  int ycoor;
};

typedef struct playerData Player;

Player* loadPlayer(char *loadLocation);

void destroyPlayer(Player *p);

#endif
