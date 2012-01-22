#include "3dworld.h"

///////////////////////////// Init Cube Data //////////////////////////////////

void World3d::InitCube()
{
cube->points3d[0].x = -1; cube->points3d[0].y = 1;  cube->points3d[0].z = 1;
cube->points3d[1].x = 1;  cube->points3d[1].y = 1;  cube->points3d[1].z = 1;
cube->points3d[2].x = 1;  cube->points3d[2].y = -1; cube->points3d[2].z = 1;
cube->points3d[3].x = -1; cube->points3d[3].y = -1; cube->points3d[3].z = 1;
cube->points3d[4].x = -1; cube->points3d[4].y = 1;  cube->points3d[4].z = -1;
cube->points3d[5].x = 1;  cube->points3d[5].y = 1;  cube->points3d[5].z = -1;
cube->points3d[6].x = 1;  cube->points3d[6].y = -1; cube->points3d[6].z = -1;
cube->points3d[7].x = -1; cube->points3d[7].y = -1; cube->points3d[7].z = -1;

cube->faces[0]=0 ; cube->faces[1]=1 ; cube->faces[2]=2 ; cube->faces[3]=3 ;
cube->faces[4]=1 ; cube->faces[5]=5 ; cube->faces[6]=6 ; cube->faces[7]=2 ;
cube->faces[8]=5 ; cube->faces[9]=4 ; cube->faces[10]=7 ; cube->faces[11]=6 ;
cube->faces[12]=4 ; cube->faces[13]=0 ; cube->faces[14]=3 ; cube->faces[15]=7 ;
cube->faces[16]=4 ; cube->faces[17]=5 ; cube->faces[18]=1 ; cube->faces[19]=0 ;
cube->faces[20]=3 ; cube->faces[21]=2 ; cube->faces[22]=6 ; cube->faces[23]=7 ;

}

/////////////////////////////// Rotate Cube ///////////////////////////////////

void World3d::RotateScaleCube()
{
int    i;
Vect3d points3drot;
float  tmp;

//if( key[KEY_LEFT] || key[KEY_RIGHT] || key[KEY_DOWN] || cycles==0 )
{

// Rotate The Cube

 for(i=0; i<8; i++)
 {
 points3drot.x = cube->points3d[i].x * cos((aoz*PI)/180) - cube->points3d[i].y * sin((aoz*PI)/180);
 points3drot.y = cube->points3d[i].y * cos((aoz*PI)/180) + cube->points3d[i].x * sin((aoz*PI)/180);
 points3drot.z = cube->points3d[i].z;

 tmp = points3drot.y;
 points3drot.y = points3drot.y * cos((aox*PI)/180) - points3drot.z * sin((aox*PI)/180);
 points3drot.z = points3drot.z * cos((aox*PI)/180) + tmp * sin((aox*PI)/180);

 tmp = points3drot.x;
 points3drot.x = points3drot.x * cos((aoy*PI)/180) - points3drot.z * sin((aoy*PI)/180);
 points3drot.z = points3drot.z * cos((aoy*PI)/180) + tmp * sin((aoy*PI)/180);

// 3D->2D

 cube->points2d[i].x = (- zobs * points3drot.x*ScaleFactor)/(points3drot.z*ScaleFactor - zobs);
 cube->points2d[i].y = (- zobs * points3drot.y*ScaleFactor)/(points3drot.z*ScaleFactor - zobs);
 
 cube->Bigcube2d[i].x = (- zobs * points3drot.x*SpaceLenght*ScaleFactor)/(points3drot.z*SpaceLenght*ScaleFactor - zobs);
 cube->Bigcube2d[i].y = (- zobs * points3drot.y*SpaceLenght*ScaleFactor)/(points3drot.z*SpaceLenght*ScaleFactor - zobs);
 }

} // key pressed

}

/////////////////////////////// Affiche Cube //////////////////////////////////

void World3d::DisplayCube()
{
Vect2d *pt2d0, *pt2d1, *pt2d2, *pt2d3;
float  Znormal;
int    i;

 for(i=0; i<6; i++)
 {
 pt2d0 = &(cube->points2d[cube->faces[4*i]]);
 pt2d1 = &(cube->points2d[cube->faces[1+4*i]]);
 pt2d2 = &(cube->points2d[cube->faces[2+4*i]]);
 pt2d3 = &(cube->points2d[cube->faces[3+4*i]]);

 Znormal = (pt2d1->x - pt2d0->x)*(pt2d3->y - pt2d0->y) -
           (pt2d1->y - pt2d0->y)*(pt2d3->x - pt2d0->x) ;

  if(Znormal<0)
  {
  line(screen1, (int)(pt2d0->x) + ScrW/2, (int)(pt2d0->y) + ScrH/2, (int)(pt2d1->x) + ScrW/2, (int)(pt2d1->y) + ScrH/2, makecol(100,100,100));
  line(screen1, (int)(pt2d1->x) + ScrW/2, (int)(pt2d1->y) + ScrH/2, (int)(pt2d2->x) + ScrW/2, (int)(pt2d2->y) + ScrH/2, makecol(100,100,100));
  line(screen1, (int)(pt2d2->x) + ScrW/2, (int)(pt2d2->y) + ScrH/2, (int)(pt2d3->x) + ScrW/2, (int)(pt2d3->y) + ScrH/2, makecol(100,100,100));
  line(screen1, (int)(pt2d3->x) + ScrW/2, (int)(pt2d3->y) + ScrH/2, (int)(pt2d0->x) + ScrW/2, (int)(pt2d0->y) + ScrH/2, makecol(100,100,100));
  }

  if(Shape==1)
  {
  pt2d0 = &(cube->Bigcube2d[cube->faces[4*i]]);
  pt2d1 = &(cube->Bigcube2d[cube->faces[1+4*i]]);
  pt2d2 = &(cube->Bigcube2d[cube->faces[2+4*i]]);
  pt2d3 = &(cube->Bigcube2d[cube->faces[3+4*i]]);

  Znormal = (pt2d1->x - pt2d0->x)*(pt2d3->y - pt2d0->y) -
            (pt2d1->y - pt2d0->y)*(pt2d3->x - pt2d0->x) ;

  if(Znormal<0)
  {
  line(screen1, (int)(pt2d0->x) + ScrW/2, (int)(pt2d0->y) + ScrH/2, (int)(pt2d1->x) + ScrW/2, (int)(pt2d1->y) + ScrH/2, makecol(100,100,100));
  line(screen1, (int)(pt2d1->x) + ScrW/2, (int)(pt2d1->y) + ScrH/2, (int)(pt2d2->x) + ScrW/2, (int)(pt2d2->y) + ScrH/2, makecol(100,100,100));
  line(screen1, (int)(pt2d2->x) + ScrW/2, (int)(pt2d2->y) + ScrH/2, (int)(pt2d3->x) + ScrW/2, (int)(pt2d3->y) + ScrH/2, makecol(100,100,100));
  line(screen1, (int)(pt2d3->x) + ScrW/2, (int)(pt2d3->y) + ScrH/2, (int)(pt2d0->x) + ScrW/2, (int)(pt2d0->y) + ScrH/2, makecol(100,100,100));
  }
 }

 if(Shape==2)
  circle(screen1, ScrW/2, ScrH/2, (int)(SpaceLenght*ScaleFactor), makecol(100,100,100));

 } // for all faces

}
