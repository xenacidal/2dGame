#ifndef INC_MAP_H
#define INC_MAP_H

struct tile{
  char type[15];
  int usable;
};

typedef struct tile Tile;

struct mapData{
  Tile** map;
  int rows;
  int cols;
};

typedef struct mapData MapData;

MapData* createMap(char *mapName);

#endif
