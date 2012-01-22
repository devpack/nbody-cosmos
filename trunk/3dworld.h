#ifndef __3DWORLD_H_
#define __3DWORLD_H_

#include "InitPlayfield.h"
#include "Structdat.h"

const int NbBody        = 3000;
const int InitWorldSize = 180;

///////////////////////////////////////////////////////////////////////////////
///                            CLASS World3D                                ///
///////////////////////////////////////////////////////////////////////////////

class World3d : public InitPlayfield, public MathsVector
{
private:
        //      Global Structure
        Cube    cube[1];
        bodyptr bodyz;

public:
        //      3D var
        char    buffer[50];
        int     cycles;
        static const bool    big;
        
        int     zobs;
        float   aox, aoy, aoz;
        float   ScaleFactor;
        static  const short Shape;
        static  const bool FreeSpace;

public:
        //      Modele var
        static  const bool  BhTree;
        static  const short model;
        static  const bool  blackhole;

        static  const float dt;
        static  const float eps;
        static  const float Zexpand;

public:
        //      Constructeur
        World3d(int GFXOPENARG, int ScrW, int ScrH);
        virtual ~World3d();
        inline  void IncCycles() { cycles++; }

public:
        //      Motion Part
        void    Simulation();
        void    Treecode();
        void    PPforce();

        void    Zoom();
        void    Expand();
        void    Rotate();

private:
        //      Tree
        cellptr racine;
        float   rsize;
        int     ncell;
        int     prof;
        nodeptr freecell;
        static  const float theta;
        static  const bool  quad;

        void    tree();

        void    newtree();
        cellptr makecell();
        void    maxbox();
        void    newbody(bodyptr p);
        int     octant(bodyptr p, cellptr q);
        void    treeGpoint(cellptr p, float psize, int lev);
        void    distancelimite(cellptr p, Vect3d cmpos, float psize);
        void    linktree(nodeptr p, nodeptr n);
        void    adjustforce(cellptr p);
        
private:
        //      force
        int     actmax;
        int     nbbcalc;
        int     nbccalc;
        int     actlen;
        nodeptr *active;
        cellptr interact;

        void    force();
        void    calcforce(nodeptr *aptr, nodeptr *nptr, cellptr cptr, cellptr bptr, nodeptr p, float psize, Vect3d pmid);
        bool    enoughfar(nodeptr c, float psize, Vect3d pmid);
        void    calcforcerec(nodeptr *nptr, nodeptr *np, cellptr cptr, cellptr bptr, nodeptr p, float psize, Vect3d pmid);
        void    totalforce(bodyptr p0, cellptr cptr, cellptr bptr);
        Vect3d  nodeforce(cellptr start, cellptr finish, Vect3d pos0, float *phi0, Vect3d acc0);
        Vect3d  cellforce(cellptr start, cellptr finish, Vect3d pos0, float *phi0, Vect3d acc0);

private:
        //      Init Part
        static  const short BallSphere;

        void    InitCube();
        void    InitBody();
        void    InitVariable();
        void    InitBodyBlackHole();
        void    InitBodyUniform();
        void    InitBodyTwoPart();
        void    InitBodyTwoPartSpiral();        
        void    InitBodySpiral();
        void    InitBodySolarSys();
        void    InitBodySTL();
        void    InitBodySSP();
        void    InitBody2Body();

public:
        //      Display Part
        float   SpaceLenght;
        void    MaxSpaceSize();

        void    RotateScaleDisplayBody();
        void    RotateScaleCube();
        void    DisplayCube();
        void    DisplayInfo();

public:
        //      Util Part
        void    svgbmp();
        Vect3d  pickball(float rad);
        Vect3d  picksphere(float rad);
        Vect3d  pickinbox(float rad);
};

#endif
