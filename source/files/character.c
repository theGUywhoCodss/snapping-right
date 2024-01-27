#include "raylib.h"
#include "map.h"
#include "collision.h"
#include "lidar.h"
#include "sound.h"
#include "texture.h"
double min(double a, double b) {
    return a<b ? a : b;
}
double max(double a, double b) {
    return a>b ? a : b;
}
//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
double playerX=300.0f;
double playerY=300.0f;
static int playerSpeed=10;
int playerWidth=20*5;
int playerHeight=13*5;
static Vector2 change= (Vector2){0,0};
static float gravity=9.807f*5;
static float jumpSpeed=20.0f;
static bool jumping=true;
static float friction=0.30f;
static float accSpeed=0.90f;
static bool col[4];
//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void horizontalC();
static void verticalC();
void drawCharacter();
void loadCharacter();
void ctrlCharacter(Vector2 offset);
static void verticalC();
static void horizontalC();
static Rectangle playerRect();
//----------------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------------
void drawCharacter(){
   DrawTexture(getTexture(0),GetScreenWidth()/2-playerWidth/2,GetScreenHeight()/2-playerHeight/2,RAYWHITE);
   //DrawRectangle(GetScreenWidth()/2-playerWidth/2,GetScreenHeight()/2-playerHeight/2,playerWidth,playerHeight,BROWN);
}
static void verticalC(){
   for(int i=0;i<blockAmount;i++){
         
        colInfo(playerRect(),blocks[i],col);
        if(col[1]==true){
            playerY=blocks[i].y-playerHeight;
            change.y=0;
            jumping=false;
        }if(col[0]){
            playerY=blocks[i].y+blocks[i].height;
            change.y=0;
        }
    }
}
static Rectangle playerRect(){
   return (Rectangle){playerX,playerY,playerWidth,playerHeight};
}
static void horizontalC(){
   for(int i=0;i<blockAmount;i++){
      colInfo(playerRect(),blocks[i],col);
      if(col[2]){
         change.x=0;
         playerX=blocks[i].x+blocks[i].width;
      }else if(col[3]){
         change.x=0;
         playerX=blocks[i].x-playerWidth;
      }
    }
}
void ctrlCharacter(Vector2 offset){
   Vector2 velo= (Vector2){0,0};
   if(IsKeyDown(KEY_D)){
      velo.x=1;
   }
   if(IsKeyDown(KEY_A)){
      velo.x=-1;
   }
   if(IsKeyPressed(KEY_W)){
      if(!jumping){
         velo.y=-1;
         jumping=true;
      }
   }
   if(IsKeyPressed(KEY_E)){
      addPing((Vector2){playerX+playerWidth/2,playerY+playerHeight/2});
   }
   if(IsKeyPressed(KEY_P)){
      musicStreamProperties(0);
   }
   if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
      newPoint((Vector2){playerX+playerWidth/2,playerY+playerHeight/2},(Vector2){GetMouseX()-offset.x,GetMouseY()-offset.y});
   }
   jumping=true;
   change.x+=velo.x*accSpeed;
   if(velo.x==0||(velo.x<0&&change.x>0)||(velo.x>0&&change.x<0))change.x*=friction;
   double productx=change.x*playerSpeed*GetFrameTime();
   playerX+=change.x<0?max(-playerSpeed,productx):min(playerSpeed,productx);
   horizontalC();
   change.y+=velo.y*jumpSpeed+gravity*GetFrameTime();
   playerY+=change.y;
   verticalC();
   if(change.x>.01||change.x<-.01)soundProperties(0,2);
   else soundProperties(0,0);
   /*DrawText(TextFormat("%f",change.x<0?max(-playerSpeed,productx):min(playerSpeed,productx)),50,0,10,RED);
   DrawText(TextFormat("%f",change.y),50,10,10,RED);*/
}
