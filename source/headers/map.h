#ifndef LOADMAP_H
#define LOADMAP_H
void drawMap(Vector2 offset);
bool collisionRecBlocks(Rectangle rec);
void loadMap(void);
void addPing(Vector2 area);
extern Rectangle blocks[10];
extern int blockAmount;
void nodeMapper(Vector2 nodeMapSize);
Vector2 getRelativeMapSize();
#endif