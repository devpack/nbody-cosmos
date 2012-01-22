#include "MathsVector.h"

const float MathsVector::PI = 3.14159265358979323846;

// float ²
float MathsVector::rsqr(float x)
{
 return (x * x);
}

// float rand
float MathsVector::xrand(float xl, float xh)
{
#if defined(LINUX)
 return (xl + (xh - xl) *  drand48() ); 
#else
 return (xl + (xh - xl) *  rand() / 32767.0 );
#endif 
}

// float rand
float MathsVector::grand(float mean, float sdev)
{
float v1, v2, s;

 do
 {
  v1 = xrand(-1.0, 1.0);
  v2 = xrand(-1.0, 1.0);
  s = v1*v1 + v2*v2;
 } while (s >= 1.0);

 return (mean + sdev * v1 * sqrt(-2.0 * log(s) / s));
}


// Vector Operations

Vect3d MathsVector::clrv()
{
Vect3d v;

 v.x = 0.0;
 v.y = 0.0;
 v.z = 0.0;

 return(v);
}


Vect3d MathsVector::setv(Vect3d v1)
{
Vect3d v;

 v.x = v1.x;
 v.y = v1.y;
 v.z = v1.z;

 return(v);
}


Vect3d MathsVector::setvs(float s1, float s2, float s3)
{
Vect3d v;

 v.x = s1;
 v.y = s2;
 v.z = s3;

 return(v);
}


Vect3d MathsVector::addv(Vect3d v1, Vect3d v2)
{
Vect3d v;

 v.x = v1.x + v2.x;
 v.y = v1.y + v2.y;
 v.z = v1.z + v2.z;

 return(v);
}


Vect3d MathsVector::addvs(Vect3d v1, float s)
{
Vect3d v;

 v.x = v1.x + s;
 v.y = v1.y + s;
 v.z = v1.z + s;

 return(v);
}


Vect3d MathsVector::subv(Vect3d v1, Vect3d v2)
{
Vect3d v;

 v.x = v1.x - v2.x;
 v.y = v1.y - v2.y;
 v.z = v1.z - v2.z;

 return(v);
}


Vect3d MathsVector::mulvs(Vect3d v1, float s)
{
Vect3d v;

 v.x = v1.x * s;
 v.y = v1.y * s;
 v.z = v1.z * s;

 return(v);
}


Vect3d MathsVector::divvs(Vect3d v1, float s)
{
Vect3d v;

 v.x = v1.x / s;
 v.y = v1.y / s;
 v.z = v1.z / s;

 return(v);
}


float MathsVector::absv(Vect3d v1)
{
 return(sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}


float MathsVector::dotvp(Vect3d v1, Vect3d v2)
{
 return(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}


float MathsVector::distv(Vect3d v1, Vect3d v2)
{
 return(sqrt((v1.x - v2.x)*(v1.x - v2.x) +
             (v1.y - v2.y)*(v1.y - v2.y) +
             (v1.z - v2.z)*(v1.z - v2.z)));
}


// Matrix Operations

Matrix MathsVector::clrm()
{
Matrix m;

 m.c1.x = 0.0 ; m.c2.x = 0.0 ; m.c3.x = 0.0 ;
 m.c1.y = 0.0 ; m.c2.y = 0.0 ; m.c3.y = 0.0 ;
 m.c1.z = 0.0 ; m.c2.z = 0.0 ; m.c3.z = 0.0 ;

 return(m);
}


Matrix MathsVector::setmi()
{
Matrix m;

 m.c1.x = 1.0 ; m.c2.x = 0.0 ; m.c3.x = 0.0 ;
 m.c1.y = 0.0 ; m.c2.y = 1.0 ; m.c3.y = 0.0 ;
 m.c1.z = 0.0 ; m.c2.z = 0.0 ; m.c3.z = 1.0 ;

 return(m);
}


Matrix MathsVector::setm(Matrix m1)
{
Matrix m;

 m.c1.x = m1.c1.x ; m.c2.x = m1.c2.x ; m.c3.x = m1.c3.x ;
 m.c1.y = m1.c1.y ; m.c2.y = m1.c2.y ; m.c3.y = m1.c3.y ;
 m.c1.z = m1.c1.z ; m.c2.z = m1.c2.z ; m.c3.z = m1.c3.z ;

 return(m);
}


Matrix MathsVector::mulms(Matrix m1, float s)
{
Matrix m;

 m.c1.x = m1.c1.x * s ; m.c2.x = m1.c2.x * s ; m.c3.x = m1.c3.x * s ;
 m.c1.y = m1.c1.y * s ; m.c2.y = m1.c2.y * s ; m.c3.y = m1.c3.y * s ;
 m.c1.z = m1.c1.z * s ; m.c2.z = m1.c2.z * s ; m.c3.z = m1.c3.z * s ;

 return(m);
}


Vect3d MathsVector::mulmv(Matrix m1, Vect3d v1)
{
Vect3d v;

 v.x = m1.c1.x * v1.x + m1.c2.x * v1.y + m1.c3.x * v1.z ;
 v.y = m1.c1.y * v1.x + m1.c2.y * v1.y + m1.c3.y * v1.z ;
 v.z = m1.c1.z * v1.x + m1.c2.z * v1.y + m1.c3.z * v1.z ;

 return(v);
}


Matrix MathsVector::addm(Matrix m1, Matrix m2)
{
Matrix m;

 m.c1.x = m1.c1.x + m2.c1.x ; m.c2.x = m1.c2.x + m2.c2.x ; m.c3.x = m1.c3.x + m2.c3.x;
 m.c1.y = m1.c1.y + m2.c1.y ; m.c2.y = m1.c2.y + m2.c2.y ; m.c3.y = m1.c3.y + m2.c3.y;
 m.c1.z = m1.c1.z + m2.c1.z ; m.c2.z = m1.c2.z + m2.c2.z ; m.c3.z = m1.c3.z + m2.c3.z;

 return(m);
}


Matrix MathsVector::subm(Matrix m1, Matrix m2)
{
Matrix m;

 m.c1.x = m1.c1.x - m2.c1.x ; m.c2.x = m1.c2.x - m2.c2.x ; m.c3.x = m1.c3.x - m2.c3.x;
 m.c1.y = m1.c1.y - m2.c1.y ; m.c2.y = m1.c2.y - m2.c2.y ; m.c3.y = m1.c3.y - m2.c3.y;
 m.c1.z = m1.c1.z - m2.c1.z ; m.c2.z = m1.c2.z - m2.c2.z ; m.c3.z = m1.c3.z - m2.c3.z;

 return(m);
}


Matrix MathsVector::outvp(Vect3d v1, Vect3d v2)
{
Matrix m;

 m.c1.x = v1.x * v2.x ; m.c2.x = v1.x * v2.y ; m.c3.x = v1.x * v2.z ;
 m.c1.y = v1.y * v2.x ; m.c2.y = v1.y * v2.y ; m.c3.y = v1.y * v2.z ;
 m.c1.z = v1.z * v2.x ; m.c2.z = v1.z * v2.y ; m.c3.z = v1.z * v2.z ;

 return(m);
}
