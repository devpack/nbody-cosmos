#include <allegro.h>
#include "InitPlayfield.h"

////////////////////////////// Init Playfield /////////////////////////////////

InitPlayfield::InitPlayfield(int GFXOPENARG, int ScrW, int ScrH)
{
 allegro_init();
 set_gfx_mode(GFXOPENARG, ScrW, ScrH, 0, 0);
 install_timer();
 install_keyboard();
 install_mouse();
 srand(time(NULL));
 dothepalette();
 screen1 = create_bitmap(InitPlayfield::ScrW, InitPlayfield::ScrH);
}

InitPlayfield::~InitPlayfield()
{
 destroy_bitmap(screen1);
 poll_mouse();
 poll_keyboard();
 allegro_exit();
}

//////////////////////////// Init palette colors //////////////////////////////

void  InitPlayfield::dothepalette()
{
int c;

      palette[0].r = 0;
      palette[0].g = 0;
      palette[0].b = 0;

      palette[1].r = 255;
      palette[1].g = 0;
      palette[1].b = 0;

   for (c=2; c<255; c++)
   {
      palette[c].r = c;
      palette[c].g = c;
      palette[c].b = c;
   }

 set_palette(palette);
}

//////////////////////////////// Allocate Mem /////////////////////////////////

void*InitPlayfield::allocate(int nb)
{
void *mem;

 mem = calloc(nb, 1);
  if (mem == NULL)
   error("Allocate Error");
 return (mem);
}

/////////////////////////////////// Error /////////////////////////////////////

void InitPlayfield::error(char *c)
{
 textout(screen, font, c, (ScrW/2)-30, ScrH/2, makecol(255,255,255));
 rest(2000);
 exit(1);
}

////////////////////////////// Draw big pixel /////////////////////////////////

void  InitPlayfield::putbigpixel(BITMAP *bmp, int x, int y, int color)
{
 putpixel(bmp, x, y, color);
 putpixel(bmp, x+1, y, color);
 putpixel(bmp, x, y-1, color);
 putpixel(bmp, x+1, y-1, color);
}
