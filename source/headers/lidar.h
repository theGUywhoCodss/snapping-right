#ifndef LIDAR_H
#define LIDAR_H
extern int lidarAmount;
void newPoint(Vector2 pos,Vector2 clickpos,int playerX,int playerY);
void updateLidar(float playerX,float playerY,int playerWidth,int playerHeight,Vector2 offset);
void drawPoints(Vector2 offset);
#endif