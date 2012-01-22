#include "3dworld.h"

//////////////////////////////// Pick Ball ////////////////////////////////////

Vect3d World3d::pickball(float rad)
{
Vect3d v;
float rsq;

 do {
 rsq = 0.0;

  v.x = xrand(-1.0, 1.0);
  v.y = xrand(-1.0, 1.0);
  v.z = xrand(-1.0, 1.0);

  rsq = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);

    } while (rsq > 1.0);

  v.x = v.x * rad;
  v.y = v.y * rad;
  v.z = v.z * rad;

 return(v);
}

////////////////////////////// Pick Sphere ////////////////////////////////////

Vect3d World3d::picksphere(float rad)
{
Vect3d v;

float rsq, rscale;

 do {
 rsq = 0.0;

  v.x = xrand(-1.0, 1.0);
  v.y = xrand(-1.0, 1.0);
  v.z = xrand(-1.0, 1.0);

  rsq = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);

   } while (rsq > 1.0);

rscale = rad / sqrt(rsq);

  v.x = v.x * rscale;
  v.y = v.y * rscale;
  v.z = v.z * rscale;

  return(v);
}

///////////////////////////////// Pick Box ////////////////////////////////////

Vect3d World3d::pickinbox(float rad)
{
Vect3d v;

  v.x = xrand(-rad, rad);
  v.y = xrand(-rad, rad);
  v.z = xrand(-rad, rad);

  return(v);
}
