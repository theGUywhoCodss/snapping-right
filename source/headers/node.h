#ifndef NODE_H
#define NODE_H
void generateNodes(Vector2 scrDimensions);
int* runNodes(int customStart,int customGoal,int range,int* returnNodes);
int getNodeXY(int x,int y);
Vector2 getNodePos(int node);
extern int nodesInit;
void unaliveNode(int node);
#endif