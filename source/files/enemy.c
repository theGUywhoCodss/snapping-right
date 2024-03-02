#include "raylib.h"
#include "trig.h"
#include "node.h"
struct enemy{
    float x;
    float y;
    int health;
    int path[10];
    int currentNode;
};
//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static int speed=100;
static struct enemy enemies[10];
static double enemiesAttackTime[10];
static int enemyArrSize=10;
static float attackRate=1;
static int damage=1;
float enemyHealth=1;
static Vector2 enemySize=(Vector2){40,40};
//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static Rectangle enemyRect(int pos);
static int getFreeEnemy();
void newEnemy(Vector2 spawnPos);
void updateEnemy(Vector2 offset);
bool harmCheck(Rectangle rect,int damage);
int attackCheck(Rectangle rect);
//----------------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------------
//resets enemy path with new character position.
void resetEnemyPathfinding(int playerX,int playerY){
    int posx=playerX;
    int posy=playerY;
    for(int i=0;i<enemyArrSize;i++){
        if(enemies[i].health>0){
            enemies[i].currentNode=0;
            int enemyx=enemies[i].x/100;
            int enemyy=enemies[i].y/100;
            for(int x=0;x<10;x++){
                enemies[i].path[x]=0;
            }
            if(getNodeXY(posx/100,posy/100)>0&&getNodeXY(posx/100,posy/100)<nodesInit)
                runNodes(getNodeXY(enemyx,enemyy),getNodeXY(posx/100,posy/100),10,enemies[i].path);
        }
    }
}
static Rectangle enemyRect(int pos){
    return (Rectangle){enemies[pos].x,enemies[pos].y,enemySize.x,enemySize.y};
}
void resetEnemies(Vector2 spawnpos){
    for(int i=0;i<enemyArrSize;i++){
        enemies[i].health=0;
        enemies[i].x=spawnpos.x;
        enemies[i].y=spawnpos.y;
    }
}
void updateEnemy(Vector2 offset){
    for(int i=0;i<enemyArrSize;i++){
        if(enemies[i].health>0){
            if(enemies[i].currentNode<10&&enemies[i].path[enemies[i].currentNode]>0){
                Vector2 nodePos=getNodePos(enemies[i].path[enemies[i].currentNode]);
                double angle = angle2Points(enemies[i].x,enemies[i].y,nodePos.x,nodePos.y);
                enemies[i].x+=calcCos(speed,angle)*GetFrameTime();
                //enemies[i].x=horizontalC(enemyRect(i)).x;
                enemies[i].y+=calcSin(speed,angle)*GetFrameTime();
                //enemies[i].y=verticalC(enemyRect(i)).y;
                int enemyNode=getNodeXY(enemies[i].x/100,enemies[i].y/100);
                if(enemyNode==enemies[i].path[enemies[i].currentNode]){
                    enemies[i].currentNode++;
                }
            }
            for(int x=0;x<10;x++){
                DrawText(TextFormat("%d",enemies[i].path[x]),10,10*x,10,RED);
            }
            DrawRectangle(enemies[i].x+offset.x,enemies[i].y+offset.y,enemySize.x,enemySize.y,GREEN);
        }
    }
}
void newEnemy(Vector2 spawnPos){
    int enemyPos=getFreeEnemy();
    if(enemyPos>=0){
        enemies[enemyPos].health=enemyHealth;
        enemies[enemyPos].x=spawnPos.x;
        enemies[enemyPos].y=spawnPos.y;
    }
}
bool harmCheck(Rectangle rect,int damage){
    for(int i=0;i<enemyArrSize;i++){
        if(enemies[i].health>0&&CheckCollisionRecs(rect,enemyRect(i))){
            enemies[i].health-=damage;
            return true;
        }
    }
    return false;
}
int attackCheck(Rectangle rect){
    int totalDamage=0;
    for(int i=0;i<enemyArrSize;i++){
        if(enemies[i].health>0&&CheckCollisionRecs(rect,enemyRect(i))){
            if(GetTime()-enemiesAttackTime[i]>attackRate){
                enemiesAttackTime[i]=GetTime();
                totalDamage+=damage;
            }
        }
    }
    return totalDamage;
}
static int getFreeEnemy(){
    for(int i=0;i<enemyArrSize;i++){
        if(enemies[i].health<=0){
            return i;
        }
    }
    return -1;
}