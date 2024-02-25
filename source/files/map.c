#include "raylib.h"
#include "string.h"
#include "mapData.h"
#include "collision.h"
#include "texture.h"
#include <stdio.h>
// nonstatic
Rectangle blocks[100]={{0}};
int blockAmount=100;
// static
static int current=2;
static Rectangle pingies[3]={{0}};
static int pingSize=200;
static double pingTime[3]={0};
static float growRate=0.1;
static int loader=0;
static int blockWidth=100;
static int blockHeight=100;
static Vector2 spawnPoint={0};
static Vector2 EnemySpawnPoint={0};
//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
void loadMap();
void drawMap(Vector2 offset);
void addPing(Vector2 area);
Vector2 getRelativeMapSize();
static void drawPing(Vector2 offset);
//----------------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------------
//Gets the map size with blocks.
Vector2 getRelativeMapSize(){
    Vector2 bestSize={0};
    for(int i=0;i<blockAmount;i++){
        if(blocks[i].x+blocks[i].width>bestSize.x)bestSize.x=blocks[i].x+blocks[i].width*2;
        if(blocks[i].y+blocks[i].height>bestSize.y)bestSize.y=blocks[i].y+blocks[i].height*2;
    }
    return bestSize;

    printf("\n%d\n",getTexture(0).height);
}
void loadMap(){
    int loadPos=0;
    int blockSize=0;
    char **map=mapList[current];
    for(int v=0;v<mapSize[current];v++){
        for(int i=0;i<strlen(map[v]);i++){
            if(map[v][i]=='#'){
                blockSize++;
            }else if((map[v][i]!='#'||i==strlen(map[v]))&&blockSize!=0){
                blocks[loadPos]=(Rectangle){blockWidth*(i-blockSize),v*blockHeight,blockWidth*blockSize,blockHeight};
                blockSize=0;
                loader++;
                loadPos++;
            }
            if(map[v][i]=='1'){
                blocks[loadPos]=(Rectangle){blockWidth*(i-blockSize),v*blockHeight,blockWidth,50};
                loader++;
                loadPos++;
            }else if(map[v][i]=='2'){
                blocks[loadPos]=(Rectangle){blockWidth*(i-blockSize),v*blockHeight+50,blockWidth,50};
                loader++;
                loadPos++;
            }else if(map[v][i]=='3'){
                blocks[loadPos]=(Rectangle){blockWidth*(i-blockSize),v*blockHeight,50,blockHeight};
                loader++;
                loadPos++;
            }else if(map[v][i]=='4'){
                blocks[loadPos]=(Rectangle){blockWidth*(i-blockSize)+50,v*blockHeight,50,blockHeight};
                loader++;
                loadPos++;    
            }else if(map[v][i]=='$'){
                spawnPoint.x=blockWidth*i;
                spawnPoint.y=v*blockHeight;
            }else if(map[v][i]=='!'){
                EnemySpawnPoint.x=blockWidth*i;
                EnemySpawnPoint.y=v*blockHeight;
            }
        }
    }

}
void drawMap(Vector2 offset){
    /*
    for(int i=0;i<blockAmount;i++){
        if(blocks[i].width!=0&&blocks[i].height!=0){
            DrawRectangle(blocks[i].x+offset.x,blocks[i].y+offset.y,blocks[i].width,blocks[i].height,LIGHTGRAY);
        }else{
            break;
        }
    }
    */
    drawPing(offset);
}
void addPing(Vector2 area){
    pingies[0]=(Rectangle){area.x,area.y,0,0};
    pingTime[0]=GetTime();
}
static void drawPing(Vector2 offset){
    if(pingies[0].width<pingSize*2){
        if(GetTime()-pingTime[0]>0.01*GetFrameTime()){
            pingTime[0]=GetTime();
            //adjust for volume change
            pingies[0].x+=pingies[0].width/2;
            pingies[0].y+=pingies[0].height/2;
            //volume change
            pingies[0].width+=pingSize*growRate;
            pingies[0].height+=pingSize*growRate;
            //readjust
            pingies[0].x-=pingies[0].width/2;
            pingies[0].y-=pingies[0].height/2;
        }
        DrawRectangle(pingies[0].x+offset.x,pingies[0].y+offset.y,10,pingies[0].height,GREEN);
        DrawRectangle(pingies[0].x+offset.x+pingies[0].width-10,pingies[0].y+offset.y,10,pingies[0].height,GREEN);
        DrawRectangle(pingies[0].x+offset.x,pingies[0].y+offset.y,pingies[0].width,10,GREEN);
        DrawRectangle(pingies[0].x+offset.x,pingies[0].y+offset.y+pingies[0].height-10,pingies[0].width,10,GREEN);
    }
    for(int i=0;i<blockAmount;i++){
        if(blocks[i].width!=0&&blocks[i].height!=0){
            drawColInfo(blocks[i],pingies[0],offset);
        }else{
            break;
        }
    }
}
bool collisionRecBlocks(Rectangle rec){
    for(int i=0;i<blockAmount;i++){
        if(blocks[i].width!=0&&blocks[i].height!=0){
            if(CheckCollisionRecs(blocks[i],rec)){
                return true;
            }
        }else{
            return false;
        }
    }
    return false;
}
Rectangle* giveBlocksPntr(){
    return blocks;
}
int giveBlocksAmount(){
    return blockAmount;
}
Vector2 giveBlockSize(){
    return (Vector2){blockWidth,blockHeight};
}
Vector2 giveSpawnPosition(){
    return spawnPoint;
}
Vector2 giveEnemySpawnPosition(){
    return EnemySpawnPoint;
}