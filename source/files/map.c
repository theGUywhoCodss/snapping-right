#include "raylib.h"
#include "string.h"
#include "collision.h"
#include "mapData.h"
#include "character.h"
// nonstatic
Rectangle blocks[100];
int blockAmount=100;
// static
static int current=0;
static bool col[4];
static Rectangle pingies[3];
static int pingSize=200;
static double pingTime[3];
static float growRate=0.1;
static int loader=0;
static int blockWidth=100;
static int blockHeight=100;
static bool col[4];
//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
void loadMap();
void drawMap(Vector2 offset);
void addPing(Vector2 area);
static void drawPing(Vector2 offset);
//----------------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------------
void loadMap(){
    int loadPos=0;
    int blockSize=0;
    int spawnerPos=0;
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
                playerX=blockWidth*i;
                playerY=v*blockHeight;
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