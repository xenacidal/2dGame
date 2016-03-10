#ifndef INC_MAP_H
#define INC_MAP_H

struct tile{
  char type[15];
  char change[25];
  int usable;
};

typedef struct tile Tile;

struct mapData{
  Tile** map;
  int rows;
  int cols;
  int load4x, load4y, load5x, load5y, load6x, load6y, load7x, load7y;
  int tempx, tempy;
  char tempMap[25];
};

typedef struct mapData MapData;

MapData* createMap(char *mapName);

void destroyMap(MapData *mData);

#endif
