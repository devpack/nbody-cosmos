#ifndef __MATHSMACRO_H_
#define __MATHSMACRO_H_

#define   MAX(x,y)     (((x) > (y)) ? (x) : (y))
#define   MIN(x,y)     (((x) < (y)) ? (x) : (y))

#define DOTVP(s,v,u)                                                  \
{                                                                     \
    (s) = (v).x*(u).x + (v).y*(u).y + (v).z*(u).z;                    \
}

#define DOTPSUBV(s,v,u,w)                                             \
{                                                                     \
    (v).x = (u).x - (w).x ;    (s)  = (v).x * (v).x ;                 \
    (v).y = (u).y - (w).y ;    (s) += (v).y * (v).y ;                 \
    (v).z = (u).z - (w).z ;    (s) += (v).z * (v).z ;                 \
}

#define DOTPMULMV(s,v,p,u)                                            \
{                                                                     \
    DOTVP(v.x, p.c1, u);    (s)  = (v).x * (u).x;                     \
    DOTVP(v.y, p.c2, u);    (s) += (v).y * (u).y;                     \
    DOTVP(v.z, p.c3, u);    (s) += (v).z * (u).z;                     \
}

#define ADDMULVS(v,u,s)                                               \
{                                                                     \
    (v).x += (u).x * (s);                                             \
    (v).y += (u).y * (s);                                             \
    (v).z += (u).z * (s);                                             \
}

#define ADDMULVS2(v,u,s,w,r)                                          \
{                                                                     \
    (v).x += (u).x * (s) + (w).x * (r);                               \
    (v).y += (u).y * (s) + (w).y * (r);                               \
    (v).z += (u).z * (s) + (w).z * (r);                               \
}


#endif
