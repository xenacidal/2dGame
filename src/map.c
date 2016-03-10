#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

MapData* createMap(char *mapName){
  MapData *mData;
  Tile **map;
  FILE *mapFile;
  if((mapFile = fopen(mapName, "r")) == NULL) {
      printf("failed to open file\n");
      return;
  } else{
    mData = (MapData *)malloc(sizeof(MapData));
    mData->tempx = -1;
    mData->tempy = -1;
    strncpy(mData->tempMap, "NULL", 25);
    fscanf(mapFile, "%d%d%d%d%d%d%d%d%d%d", &mData->rows, &mData->cols, &mData->load4x, &mData->load4y, &mData->load5x, &mData->load5y, &mData->load6x, &mData->load6y, &mData->load7x, &mData->load7y);
    map = (Tile**)malloc(mData->rows * sizeof(Tile));
    int i, j;
    for(i = 0; i < mData->rows; i++) {
      map[i] = (Tile *)malloc (mData->cols * sizeof(Tile));
      for(j = 0; j < mData->cols; j++) {
	fscanf(mapFile, "%s%d%s", (map[i] + j)->type, &(map[i] + j)->usable, (map[i] + j)->change);
      }
    }
  }
  mData->map = map;
  return mData;
}

void destroyMap(MapData *mData) {
  Tile** map = mData->map;
  int i;
  for(i = 0; i < mData->rows; i++){
    free(map[i]);
  }
  free(map);
  free(mData);
}

   
    
