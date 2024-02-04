#ifndef ENEMY_H
#define ENEMY_H
void updateEnemy(Vector2 offset);
void newEnemy(Vector2 spawnPos);
bool harmCheck(Rectangle rect,int damage);
int attackCheck(Rectangle rect);
void resetEnemies();
void resetEnemyPathfinding(int playerX,int playerY);
extern float enemyHealth;
#endif