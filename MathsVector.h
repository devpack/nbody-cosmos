#ifndef __MATHSVECTOR_H_
#define __MATHSVECTOR_H_

#include <allegro.h>
#include "MathsMacro.h"
#include "math.h"

//#define  LINUX 

///////////////////////////////////////////////////////////////////////////////
///                           CLASS Maths Vector                            ///
///////////////////////////////////////////////////////////////////////////////

struct Vect3d { float x, y, z; };
struct Vect2d { float x, y; };
struct Matrix { Vect3d c1, c2, c3; };

class MathsVector
{
public:
          static const float PI;
protected:
          Vect3d clrv();
          Vect3d setv(Vect3d v1);
          Vect3d setvs(float s1, float s2, float s3);
          Vect3d addv(Vect3d v1, Vect3d v2);
          Vect3d addvs(Vect3d v1, float s);
          Vect3d subv(Vect3d v1, Vect3d v2);
          Vect3d mulvs(Vect3d v1, float s);
          Vect3d divvs(Vect3d v1, float s);
          float  absv(Vect3d v1);
          float  dotvp(Vect3d v1, Vect3d v2);
          float  distv(Vect3d v1, Vect3d v2);
protected:
          Matrix clrm();
          Matrix setmi();
          Matrix setm(Matrix m1);
          Matrix mulms(Matrix m1, float s);
          Vect3d mulmv(Matrix m1, Vect3d v);
          Matrix addm(Matrix m1, Matrix m2);
          Matrix subm(Matrix m1, Matrix m2);
          Matrix outvp(Vect3d v1, Vect3d v2);
protected:
          float rsqr(float x);
          float xrand(float xl, float xh);
          float grand(float mean, float sdev);
};


#endif
