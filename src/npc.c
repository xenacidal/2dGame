#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "npc.h"

NPC* createNpc(char *filename){
  NPC *n;
  FILE *npcFile;
  if((npcFile =fopen(filename, "r")) == NULL) {
    printf("failed to open file\n");
    return;
  } else{
    n = (NPC *)malloc(sizeof(NPC));
    fscanf(npcFile, "%s%s%s%d%d%d%s", n->fileName, n->name, n->mapName, &n->xcoor, &n->ycoor, &n->direction, n->sprite);
  }
  return n;
}

void destroyNpc(NPC *n){
  free(n);
}
