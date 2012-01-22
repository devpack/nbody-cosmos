#include "3dworld.h"

///////////////////////// Rotate + Display Body ///////////////////////////////

void World3d::RotateScaleDisplayBody()
{
bodyptr p;

Vect3d pos3drot;
Vect2d pos2d;

float  tmp;
int    particol;
float cosaoz, cosaoy, cosaox, sinaoz, sinaoy, sinaox;

cosaoz = cos((aoz*PI)/float(180)); 
cosaoy = cos((aoy*PI)/float(180));
cosaox = cos((aox*PI)/float(180)); 
sinaoz = sin((aoz*PI)/float(180));
sinaoy = sin((aoy*PI)/float(180));
sinaox = sin((aox*PI)/float(180));

 for(p = bodyz; p < bodyz+NbBody; p++)
 {

// Rotation body

 pos3drot.x = XPos(p) * cosaoz - YPos(p) * sinaoz;
 pos3drot.y = YPos(p) * cosaoz + XPos(p) * sinaoz;
 pos3drot.z = ZPos(p);

 tmp = pos3drot.y;
 pos3drot.y = pos3drot.y * cosaox - pos3drot.z * sinaox;
 pos3drot.z = pos3drot.z * cosaox + tmp * sinaox;

 tmp = pos3drot.x;
 pos3drot.x = pos3drot.x * cosaoy - pos3drot.z * sinaoy;
 pos3drot.z = pos3drot.z * cosaoy + tmp * sinaoy;

// 3D->2D body

 pos2d.x = (- zobs * pos3drot.x*ScaleFactor)/(pos3drot.z*ScaleFactor - zobs);
 pos2d.y = (- zobs * pos3drot.y*ScaleFactor)/(pos3drot.z*ScaleFactor - zobs);

// Display body

 particol = (int)(pos3drot.z*ScaleFactor + (ScaleFactor)*sqrt(3));
 if(particol>255) particol=255; if(particol<130) particol=130;
 particol=255;
 if(!big)
  putpixel(screen1, (int)(pos2d.x) + ScrW/2, (int)(pos2d.y) + ScrH/2, makecol(particol,particol,particol));
 else
  putbigpixel(screen1, (int)(pos2d.x) + ScrW/2, (int)(pos2d.y) + ScrH/2, makecol(particol,particol,particol));
 } // all body

 if(blackhole==1)
 putbigpixel(screen1, (int)(pos2d.x) + ScrW/2, (int)(pos2d.y) + ScrH/2, makecol(255,0,0));


}
