#ifndef CHARACTER_H
#define CHARACTER_H
extern double playerX;
extern double playerY;
extern int playerWidth;
extern int playerHeight;
void drawCharacter();
void ctrlCharacter(Vector2 offset,Rectangle *blocks,int blockAmount);
void updatePlayerSound();
void updatePlayerNode();
bool playerNodeChanged();
#endif