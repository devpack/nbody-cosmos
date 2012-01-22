///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                   SIMULATION DES STRUCTURES DE L'UNIVERS                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include <allegro.h>
#include "InitPlayfield.h"
#include "3dWorld.h"

///////////////////// Constantes Class InitPlayfield //////////////////////////

const int   InitPlayfield::ScrW = 1024;
const int   InitPlayfield::ScrH = 768;
const int   InitPlayfield::GFXOPENARG = GFX_SAFE; // WINDOWED
//const int   InitPlayfield::GFXOPENARG = GFX_AUTODETECT; // FULLSCREEN

///////////////////////// Constantes Class World3d ////////////////////////////

const bool  World3d::BhTree     = 1;        // 0=PP 1=Oct-Tree
const short World3d::model      = 1;        // models
const bool  World3d::blackhole  = 0;        // 1=blackhole
const short World3d::BallSphere = 1;        // 0=ball 1=sphere 2=box

const short World3d::Shape      = 0;        // 0=nil 2=circle 1=cube
const bool  World3d::FreeSpace  = 0;        // 1=free

const float World3d::eps        = 0.36;     // softening
const float World3d::dt         = 1.0/32.0; // time step
const float World3d::Zexpand    = 1.0;      // Coef expension 1.0=nil

const float World3d::theta      = 1.0;
const bool  World3d::quad       = 1;
const bool  World3d::big        = 0;

///////////////////////////////////////////////////////////////////////////////
///                                  MAIN                                   ///
///////////////////////////////////////////////////////////////////////////////

int main() 
{
 World3d *Cosmos=new World3d(InitPlayfield::GFXOPENARG, InitPlayfield::ScrW, InitPlayfield::ScrH);

 if(World3d::BhTree)
  Cosmos->Treecode();                     

while(! key[KEY_ESC] && !mouse_b&1)
{
 Cosmos->clearscreen1();                    // Clear screen

 if (!key[KEY_RCONTROL])
 {
  Cosmos->Simulation();                     // step time + force calc
  Cosmos->Expand();                         // expension coef action
  Cosmos->IncCycles();                      // cycles count
 }

 Cosmos->Rotate();                          // rotate all
 Cosmos->Zoom();                            // zoom ScaleFactor

 if(World3d::Shape)
  Cosmos->MaxSpaceSize();                   // Space limit

 if(!World3d::FreeSpace)
 {
 Cosmos->RotateScaleCube();                 // Cube action
 Cosmos->DisplayCube();                     // Display cube
 }

 Cosmos->RotateScaleDisplayBody();          // Body rotate + display
 Cosmos->DisplayInfo();                     // Info param
 Cosmos->blitscreen1();                     // screen1->screen
 
 if (key[KEY_S])
  Cosmos->svgbmp();                         // Screenshots

 vsync();
}

 delete Cosmos;
 return 0;

}
END_OF_MAIN();
