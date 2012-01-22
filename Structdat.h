#ifndef __STRUCTDAT_H_
#define __STRUCTDAT_H_

#include "MathsVector.h"

struct Node 
{
short  type;                  
short  update;               
float  mass;                  
Vect3d pos;                   
struct Node *next;            
};
typedef Node *nodeptr;

#define Type(a)   (((nodeptr) (a))->type)
#define Update(a) (((nodeptr) (a))->update)
#define Mass(a)   (((nodeptr) (a))->mass)
#define Pos(a)    (((nodeptr) (a))->pos)
#define XPos(a)   (((nodeptr) (a))->pos.x)
#define YPos(a)   (((nodeptr) (a))->pos.y)
#define ZPos(a)   (((nodeptr) (a))->pos.z)
#define Next(a)   (((nodeptr) (a))->next)

#define BODY 01
#define CELL 02

struct Body 
{
 Node   bodynode;              
 Vect3d vel;                   
 Vect3d acc;                   
 float  phi;                  
};
typedef Body *bodyptr;

#define Vel(a)    (((bodyptr) (a))->vel)
#define Acc(a)    (((bodyptr) (a))->acc)
#define Phi(a)    (((bodyptr) (a))->phi)

struct Cell
{
Node    cellnode;             
float   rcrit2;               
nodeptr more;                
 union 
 {
  nodeptr subp[8];       
  Matrix  quad;         
 } sorq;
};
typedef Cell *cellptr;

#define Rcrit2(a) (((cellptr) (a))->rcrit2)
#define More(a)   (((cellptr) (a))->more)
#define Subp(a)   (((cellptr) (a))->sorq.subp)
#define Quad(a)   (((cellptr) (a))->sorq.quad)

struct Cube
{
Vect3d points3d[8];
Vect2d points2d[8];
short  faces[24];
Vect2d Bigcube2d[8];
};

#endif
