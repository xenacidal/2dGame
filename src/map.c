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
    int rows, cols, use;
    char ty[15];
    fscanf(mapFile, "%d%d", &rows, &cols);
    mData = (MapData *)malloc(sizeof(MapData));
    mData->rows = rows;
    mData->cols = cols;
    map = (Tile**)malloc(rows * sizeof(Tile));
    int i, j;
    for(i = 0; i < rows; i++) {
      map[i] = (Tile *)malloc (cols * sizeof(Tile));
      for(j = 0; j < cols; j++) {
	fscanf(mapFile, "%s%d", (map[i] + j)->type, &(map[i] + j)->usable);
      }
    }
  }
  mData->map = map;
  return mData;
}

   
    
