#include "raylib.h"
#include "trig.h"
#include "collision.h"
#include "map.h"

static Vector2 pointSize=(Vector2){10,10};
static Vector2 points[50];
int lidarAmount=50;
static int currentPoint=0;
//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static bool plotPoint(double angle,int playerX,int playerY);
//----------------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------------
static bool plotPoint(double angle,int playerX,int playerY){
    bool pointFound=false;
    while(!pointFound){
        points[currentPoint].x+=calcCos(1,angle)*GetFrameTime();
        points[currentPoint].y+=calcSin(1,angle)*GetFrameTime();
        if(collisionRecBlocks((Rectangle){points[currentPoint].x,points[currentPoint].y,pointSize.x,pointSize.y})){
            pointFound=true;
        }
        if(points[currentPoint].x<playerX-1000||points[currentPoint].x>playerX+1000||
        points[currentPoint].y<playerY-1000||points[currentPoint].y>playerY+1000){
            pointFound=true;
        }
    }
    return pointFound;
}
void newPoint(Vector2 pos,Vector2 clickpos,int playerX,int playerY){
    double angle = angle2Points(pos.x,pos.y,clickpos.x,clickpos.y);
    points[currentPoint]=pos;
    plotPoint(angle,pos.x,pos.y);
    currentPoint++;
    if(currentPoint>=lidarAmount){
        currentPoint=0;
    }
}
// add keys
void updateLidar(Rectangle *entities,Vector2 playerPos,int playerWidth,int playerHeight,Vector2 offset){
   if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        playerPos.x+=playerWidth/2;
        playerPos.y+=playerHeight/2;
        newPoint(playerPos,(Vector2){GetMouseX()-offset.x,GetMouseY()-offset.y});
   }
}
void drawPoints(Vector2 offset){
    for(int i=0;i<lidarAmount;i++){
        if(points[i].x!=0&&points[i].y!=0){
            DrawRectangle(points[i].x+offset.x,points[i].y+offset.y,pointSize.x,pointSize.y,RED);
        }
    }
}