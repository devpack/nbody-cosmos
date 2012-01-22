#include "3dworld.h"

//////////////////////////// 3D Class Init ////////////////////////////////////

World3d::World3d(int GFXOPENARG, int ScrW, int ScrH)
        :InitPlayfield(GFXOPENARG, ScrW, ScrH)
{
 InitVariable();
 InitBody();
 InitCube();
}


World3d::~World3d()
{
 free(bodyz);
 free(racine);
}

//////////////////////////////// Simulation ///////////////////////////////////

void World3d::Simulation()
{
bodyptr p;

Vect3d dvel;
Vect3d dpos;

/////// Integration time leap-frog 1/2 ///////

 for(p = bodyz; p < bodyz+NbBody; p++)
 {
  dvel = mulvs(Acc(p), 0.5 * dt);
  Vel(p) = addv(Vel(p), dvel);
  dpos = mulvs(Vel(p), dt);
  Pos(p) = addv(Pos(p), dpos);
 }

///////  PP algo ou BH-Tree algo /////// 

 if(BhTree)
  Treecode();          // O(NlogN)
 else
  PPforce();           // O(N²)

/////// Integration time leap-frog 1/2 ///////

 for(p = bodyz; p < bodyz+NbBody; p++)
 {
  dvel = mulvs(Acc(p), 0.5 * dt);
  Vel(p) = addv(Vel(p), dvel);

  Acc(p) = clrv();
 }

}

//////////////////////////////// O(N²) Algo ///////////////////////////////////

void World3d::PPforce()
{
bodyptr pi, pj;

Vect3d dr;
Vect3d acci;
float  eps2, dr2, drabs, phii;

 eps2=eps*eps;

 for(pi = bodyz; pi < bodyz+NbBody; pi++)
  for(pj = bodyz; pj < bodyz+NbBody; pj++)
  {
   if(pi!=pj)
   {
    dr      = subv(Pos(pj), Pos(pi));
    dr2     = dotvp(dr, dr);
    dr2    += eps2;
    drabs   = sqrt(dr2);
    phii    = (Mass(pj))/(drabs*dr2);
    acci    = mulvs(dr, phii);
    Acc(pi) = addv(Acc(pi), acci);
   }
  } // all couple i!=j
}

////////////////////////////// O(NlogN) Algo //////////////////////////////////

void World3d::Treecode()
{
bodyptr p;

 for(p = bodyz; p< bodyz+NbBody; p++)
  Update(p) = TRUE;                    

 tree();                           
 force();                          
}

///////////////////////////////// Rotate //////////////////////////////////////

void World3d::Rotate()
{
 if(key[KEY_LEFT]) aox+=4;
 if(key[KEY_RIGHT]) aoy+=4;
 if(key[KEY_DOWN]) aoz+=4;
 if(key[KEY_LEFT]&&key[KEY_UP]) aox-=8;
 if(key[KEY_RIGHT]&&key[KEY_UP]) aoy-=8;
 if(key[KEY_DOWN]&&key[KEY_UP]) aoz-=8;
}

////////////////////////////////// Zoom ///////////////////////////////////////

void World3d::Zoom()
{
 if (key[KEY_LCONTROL])
 ScaleFactor /= 1.1;
 if (key[KEY_LSHIFT])
 ScaleFactor *= 1.1;
}

///////////////////////////////// Expand //////////////////////////////////////

void World3d::Expand()
{
bodyptr p;

 if(Zexpand!=1.0)
  for(p = bodyz; p < bodyz+NbBody; p++)
   Pos(p) = mulvs(Pos(p), Zexpand);

}

/////////////////////////////// Space Size ////////////////////////////////////

void World3d::MaxSpaceSize()
{
bodyptr p;
int     i;
float   maxlocal;

 SpaceLenght=0.0;

 for(p = bodyz; p < bodyz+NbBody; p++)
 {
  maxlocal = MAX (ABS(XPos(p)), MAX (ABS(YPos(p)), ABS(ZPos(p))) );
   if (maxlocal > SpaceLenght) SpaceLenght = maxlocal;
 }

}

////////////////////////////// Display Info ///////////////////////////////////

void World3d::DisplayInfo()
{/*
 if(BhTree)
 {
 sprintf(buffer, "NbBody: %i", NbBody);
 textout(screen1, font, buffer, 5, 10, makecol(225,225,225));
 sprintf(buffer, "Eps   : %fl", eps);
 textout(screen1, font, buffer, 5, 20, makecol(225,225,225));
 sprintf(buffer, "Dt    : %fl", dt);
 textout(screen1, font, buffer, 5, 30, makecol(225,225,225));
 sprintf(buffer, "Time  : %i", cycles);
 textout(screen1, font, buffer, 5, 40, makecol(225,225,225));
 }
 else
 {
 sprintf(buffer, "NbBody:      %i", NbBody);
 textout(screen1, font, buffer, 5, 10, makecol(225,225,225));
 sprintf(buffer, "Eps   :      %fl", eps);
 textout(screen1, font, buffer, 5, 20, makecol(225,225,225));
 sprintf(buffer, "Dt    :      %fl", dt);
 textout(screen1, font, buffer, 5, 30, makecol(225,225,225));
 sprintf(buffer, "Time  :      %i", cycles);
 textout(screen1, font, buffer, 5, 40, makecol(225,225,225));

 sprintf(buffer, "ExpandCoef : %fl", Zexpand);
 textout(screen1, font, buffer, 5, 60, makecol(225,225,225));
 sprintf(buffer, "ScaleFactor: %fl", ScaleFactor/InitWorldSize);
 textout(screen1, font, buffer, 5, 70, makecol(225,225,225));

 sprintf(buffer, "SpaceSize  : %fl", SpaceLenght);
 textout(screen1, font, buffer, 5, 90, makecol(225,225,225));
 }
*/
}

/////////////////////////////// Svg Bitmap ////////////////////////////////////

void World3d::svgbmp()
{
 //sprintf(buffer, "Frame%i.bmp", cycles);
 //save_bitmap(buffer, screen1, palette);
}

