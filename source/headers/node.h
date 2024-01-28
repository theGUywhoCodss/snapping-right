#ifndef NODE_H
#define NODE_H
void generateNodes(Vector2 scrDimensions);
void drawNodes();
void runNodes();
void nodeSetterXY(int node,bool mode);
int getNodeXY(int x,int y);
void unaliveNode(int node);
#endif