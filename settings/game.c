#include <stdio.h>
#include "raylib.h"
#include "string.h"
#include "map.h"
#include "character.h"
#include "lidar.h"
#include "sound.h"
#include "texture.h"
#include "enemy.h"
#include "node.h"
//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------------
void updateGame(){
    updateMusic();
    Vector2 offset = (Vector2){-playerX+GetScreenWidth()/2-playerWidth/2,-playerY+GetScreenHeight()/2-playerHeight/2};
    ctrlCharacter(offset);
    updatePlayerSound();
    updatePlayerPathfinding();
    BeginDrawing();
        ClearBackground(BLACK);
        updateEnemy(offset);
        DrawFPS(0,0);
        drawPoints(offset);
        drawCharacter();
        drawMap(offset);
    EndDrawing();
}
void loadGame(){
    loadMap();
    defineMusicStream("resources/jovial.wav");
    defineSound("resources/footstep.wav",0);
    saveTexture("images/character.png",0,5);
    Vector2 nodeMapSize=getRelativeMapSize();
    generateNodes(nodeMapSize);
    nodeMapper(nodeMapSize);
    newEnemy((Vector2){0,0});
    resetEnemyPathfinding();
}
void unloadGame(){
    unloadMusic();
    unloadSounds();
    unloadAllTextures();
}