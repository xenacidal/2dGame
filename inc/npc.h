#ifndef INC_NPC_H
#define INC_NPC_H

struct npc{
  char fileName[25];
  char name[20];
  char mapName[25];
  char sprite[25];
  int xcoor, ycoor, direction;
};

typedef struct npc NPC;

NPC* createNpc(char *fileName);

void destroyNpc(NPC *n);

#endif
