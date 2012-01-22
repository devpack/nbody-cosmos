#ifndef __INITPLAYFIELD_H_
#define __INITPLAYFIELD_H_

#include <allegro.h>

///////////////////////////////////////////////////////////////////////////////
///                           CLASS InitPlayfield                           ///
///////////////////////////////////////////////////////////////////////////////

class InitPlayfield
{
public:
       static const int   ScrW;
       static const int   ScrH;
       static const int   GFXOPENARG;

       PALETTE palette;
       BITMAP *screen1;

public:
       InitPlayfield(int GFXOPENARG, int ScrW, int ScrH);
       virtual ~InitPlayfield();

       void        putbigpixel(BITMAP *bmp, int x, int y, int color);
       void        dothepalette();
       void*       allocate(int nb);
       void        error(char *c);
       inline void clearscreen1() { clear_bitmap(screen1); };
       inline void blitscreen1(){ blit(screen1, screen, 0, 0, 0, 0, screen1->w, screen1->h); };
};

#endif
