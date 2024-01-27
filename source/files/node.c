#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
struct node
{
    Vector2 rect;
    int g;
    int h;
    int closest[4];
    bool alive;
    bool search;
    bool processed;
    bool efficient;
};

static struct node nodes[100];
static int nodeArrSize=100;
static int nodesInit=0;
static Vector2 nodeSize=(Vector2){75,75};
static Vector2 nodeDrawSize=(Vector2){25,25};
static int rowSize;
static int start=10;
static int goal=49;
//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
void generateNodes(Vector2 scrDimensions);
void drawNodes();
void runNodes();
static void closestNodes();
static int processBestNode();
static int nodeRequest(int x,int y,int currentNode);
static void makeProcessed(int currentNode);
static void drawNodeInformation(int currentNode,Vector2 rect);
static void setNodeInformation(int currentNode);
static Vector2 NodeDistence(int node1,int node2);
//----------------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------------
static int nodeRequest(int x,int y,int currentNode){
    int node=currentNode;
    int rowPos=currentNode%rowSize;
    node+=rowSize*y+x;
    if(node>=nodesInit||node<0||rowPos+x>=rowSize||rowPos+x<0){
        return -1;
    }
    return node;
}
void runNodes(){
    int recentNode=-1;
    while (recentNode!=goal){
        recentNode=processBestNode();
    }
    //get most effient route by tracking back
    recentNode=goal;
    int count=0;
    while (recentNode!=start&&count<100){
        int bestPNode=0;
        int bestG=10000;
        for(int i=0;i<4;i++){
            int closestNode=nodes[recentNode].closest[i];
            if(nodes[closestNode].processed&&nodes[closestNode].g<bestG&&
            !nodes[closestNode].efficient){
                bestPNode=closestNode;
                bestG=nodes[closestNode].g;
            }
        }
        nodes[bestPNode].efficient=true;
        recentNode=bestPNode;
        count++;
    }
}
void generateNodes(Vector2 scrDimensions){
    int currentNode=0;
    rowSize=scrDimensions.x/nodeSize.x;
    for(int u=0;u<scrDimensions.y/nodeSize.y;u++){
        for(int i=0;i<scrDimensions.x/nodeSize.x;i++){
            int realPos=i+u*(scrDimensions.x/nodeSize.x);
            if(currentNode<nodeArrSize){
                int testOffset=50;
                nodes[currentNode].rect=(Vector2){i*nodeSize.x+testOffset,u*nodeSize.y+testOffset};
                nodes[currentNode].alive=true;
                if(realPos>12&&realPos<20)nodes[currentNode].alive=false;
                currentNode++;
                nodesInit++;
            }
        }
    }
    closestNodes();
    makeProcessed(start);
}
void drawNodes(){
    for(int i=0;i<nodesInit;i++){
        Color nodeColor=RED;
        Vector2 rect= nodes[i].rect;
        if(nodes[i].efficient)nodeColor=YELLOW;
        if(!nodes[i].alive)nodeColor=LIGHTGRAY;
        if(i==goal)nodeColor=ORANGE;
        rect.x-=nodeDrawSize.x/2;
        rect.y-=nodeDrawSize.y/2;
        DrawRectangleV(rect,nodeDrawSize,nodeColor);
        DrawText(TextFormat("%d",i),rect.x,rect.y,20,BLUE);
    }
}
static int processBestNode(){
    int bestNode=-1;
    int bestScore=10000;
    Vector2 bestInfo;
    for(int i=0;i<nodesInit;i++){
        if(nodes[i].search&&nodes[i].alive){
            int calc=nodes[i].g+nodes[i].h;
            if(calc<bestScore){
                bestInfo.x=nodes[i].g;
                bestInfo.y=nodes[i].h;
                bestScore=calc;
                bestNode=i;
            }else if(calc==bestScore&&nodes[i].h<bestInfo.y){
                bestInfo.x=nodes[i].g;
                bestInfo.y=nodes[i].h;
                bestScore=calc;
                bestNode=i;
            }
        }
    }
    makeProcessed(bestNode);
    return bestNode;
}
static void drawNodeInformation(int currentNode,Vector2 rect){
    if(nodes[currentNode].search||nodes[currentNode].processed){
        DrawText(TextFormat("%d",nodes[currentNode].g),rect.x,rect.y,20,BLUE);
        DrawText(TextFormat("%d",nodes[currentNode].h),rect.x,rect.y+20,20,BLUE);
    }
}
static void setNodeInformation(int currentNode){
    if(nodes[currentNode].search||nodes[currentNode].processed){
        Vector2 startDist=NodeDistence(currentNode,start);
        Vector2 goalDist=NodeDistence(currentNode,goal);
        nodes[currentNode].g=startDist.x+startDist.y;
        nodes[currentNode].h=goalDist.x+goalDist.y;
    }
}
static void makeProcessed(int currentNode){
    nodes[currentNode].processed=true;
    if(nodes[currentNode].search)nodes[currentNode].search=false;
    for(int i=0;i<4;i++){
        int closestNode=nodes[currentNode].closest[i];
        if(!nodes[closestNode].processed&&!nodes[closestNode].search){
            nodes[closestNode].search=true;
            setNodeInformation(nodes[currentNode].closest[i]);
        }
    }
}
static Vector2 NodeDistence(int node1,int node2){
    return (Vector2){abs((node1%rowSize)-(node2%rowSize)),abs((node1/rowSize)-(node2/rowSize))};
}
void closestNodes(){
    for(int i=0;i<nodesInit;i++){
        int x=nodeRequest(0,-1,i);
        if(x){
            nodes[i].closest[0]=x;
        }
        x=nodeRequest(0,1,i);
        if(x){
            nodes[i].closest[1]=x;
        }
        x=nodeRequest(-1,0,i);
        if(x){
            nodes[i].closest[2]=x;
        }
        x=nodeRequest(1,0,i);
        if(x){
            nodes[i].closest[3]=x;
        }
    }
}