#ifndef LIDAR_H
#define LIDAR_H
extern int lidarAmount;
void newPoint(Vector2 pos,Vector2 clickpos,int playerX,int playerY);
void drawPoints(Vector2 offset);
#endif