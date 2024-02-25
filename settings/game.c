#include "raylib.h"
#include "string.h"
#include "map.h"
#include "character.h"
#include "sound.h"
#include "texture.h"
#include "node.h"
#include "enemy.h"
//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void nodeMapper(Vector2 nodeMapSize);
static void bootNodes(Vector2 nodeMapSize);
//----------------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------------

static void bootNodes(Vector2 nodeMapSize){
    generateNodes(nodeMapSize);
    nodeMapper(nodeMapSize);
}

//Makes unalive nodes for blocks.
static void nodeMapper(Vector2 nodeMapSize){
    Rectangle* blocks=giveBlocksPntr();
    for(int i=0;i<giveBlocksAmount();i++){
        if(blocks[i].x<nodeMapSize.x&&blocks[i].y<nodeMapSize.y){
            for(int x=0;x<blocks[i].width/giveBlockSize().x;x++){
                unaliveNode(getNodeXY((100*x+blocks[i].x)/100,blocks[i].y/100));
            }
        }
    }
}
void updateGame(){
    updateMusic();
    Vector2 offset = (Vector2){-playerX+GetScreenWidth()/2-playerWidth/2,-playerY+GetScreenHeight()/2-playerHeight/2};
    ctrlCharacter(offset,giveBlocksPntr(),giveBlocksAmount());
    updatePlayerSound();
    if(playerNodeChanged()){
        resetEnemyPathfinding(playerX,playerY);
        updatePlayerNode();
    }
    
    BeginDrawing();
        ClearBackground(BLACK);
        updateEnemy(offset);
        DrawFPS(0,0);
        drawCharacter();
        drawMap(offset);
    EndDrawing();
}
void loadGame(){
    loadMap();
    defineMusicStream("resources/jovial.wav");
    defineSound("resources/footstep.wav",0);
    bootNodes(getRelativeMapSize());
    saveTexture("images/character.png",0,5);
    saveTexture("images/characterflipped.png",1,5);
    Vector2 pnt=giveSpawnPosition();
    playerX=pnt.x;
    playerY=pnt.y;
    pnt=giveEnemySpawnPosition();
    newEnemy(pnt);
    resetEnemyPathfinding(playerX,playerY);
}
void unloadGame(){
    unloadMusic();
    unloadSounds();
    unloadAllTextures();
}