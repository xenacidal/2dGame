#ifndef INC_PLAYER_H
#define INC_PLAYER_H

struct playerData{
  char pFile[25];
  char mapName[25];
  char prevMap[25];
  int direction;
  int xcoor;
  int ycoor;
  int prevx;
  int prevy;
};

typedef struct playerData Player;

Player* loadPlayer(char *loadLocation);

void savePlayer(Player *p);

void destroyPlayer(Player *pData);

#endif
