#include <stdio.h>
#include <stdlib.h>
#include "player.h"

Player* loadPlayer(char *loadLocation) {
  Player *pData;
  FILE *playerFile;
  if((playerFile = fopen(loadLocation, "r")) == NULL) {
    printf("failed to open file\n");
    return;
  } else {
    pData = (Player *)malloc(sizeof(Player));
    fscanf(playerFile, "%s%d%d", pData->mapName, &pData->xcoor, &pData->ycoor);
  }
  return pData;
}

void destroyPlayer(Player *p){
  free(p);
}
