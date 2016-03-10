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
    fscanf(playerFile, "%s %d %d %d %s %s %d %d", pData->mapName, &pData->direction, &pData->xcoor, &pData->ycoor, pData->pFile, pData->prevMap, &pData->prevx, &pData->prevy);
  }
  return pData;
}

void savePlayer(Player *pData){
  FILE *playerFile;
  if((playerFile = fopen(pData->pFile, "w")) == NULL) {
    printf("failed to write file\n");
    return;
  } else {
    fprintf(playerFile, "%s %d %d %d %s %s %d %d", pData->mapName, pData->direction, pData->xcoor, pData->ycoor, pData->pFile, pData->prevMap, pData->prevx, pData->prevy);
  }
  return;
}

void destroyPlayer(Player *p){
  free(p);
}
