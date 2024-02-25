#ifndef LOADMAP_H
#define LOADMAP_H
void drawMap(Vector2 offset);
bool collisionRecBlocks(Rectangle rec);
void loadMap(void);
void addPing(Vector2 area);
Vector2 giveBlockSize();
Vector2 getRelativeMapSize();
Vector2 giveSpawnPosition();
Vector2 giveEnemySpawnPosition();
int giveBlocksAmount();
Rectangle* giveBlocksPntr();
#endif