#include "3dworld.h"

//////////////////////////////// force ////////////////////////////////////////

void World3d::force()
{
Vect3d rmid;
    
 actlen = (int)( ((int)(162 * prof)) * pow(theta, -2.5));  
 active = (nodeptr *) allocate(actlen * sizeof(nodeptr));
 interact = (cellptr) allocate(actlen * sizeof(Cell));
 actmax = nbbcalc = nbccalc = 0;            
 active[0] = (nodeptr) racine;                
 rmid = clrv();                              
 calcforce(active, active + 1, interact, interact + actlen, (nodeptr) racine, rsize, rmid);      
 free(active);
 free(interact);
}

/////////////////////////////// calcforce /////////////////////////////////////

void World3d::calcforce(nodeptr *aptr, nodeptr *nptr, cellptr cptr, cellptr bptr, nodeptr p, float psize, Vect3d pmid)
{
nodeptr *np, *ap, q;
int actsafe;

 if (Update(p)) 
 {                           
  np = nptr;                             
  actsafe = actlen - 8;                   
 
  for (ap = aptr; ap < nptr; ap++)        
   if (Type(*ap) == CELL) 
   {            
    if (enoughfar(*ap, psize, pmid)) 
    { 
     Mass(cptr) = Mass(*ap);     
     Pos(cptr) = setv(Pos(*ap));
     Quad(cptr) = setm(Quad(*ap));
     cptr++;                     
    } 
    else 
    {                        
     for (q = More(*ap); q != Next(*ap); q = Next(q))
      *np++= q;               
    }
   }   
   else                              
    if (*ap != p) 
    {                
     --bptr;                    
     Mass(bptr) = Mass(*ap);    
     Pos(bptr) = setv(Pos(*ap));
    }

  actmax = MAX(actmax, np - active);    
    
  if (np != nptr)                         
   calcforcerec(nptr, np, cptr, bptr, p, psize, pmid);                                              
  else
  {                                  
   totalforce((bodyptr) p, cptr, bptr);   
  }
 }

}

//////////////////////////////// enoughfar ////////////////////////////////////

bool World3d::enoughfar(nodeptr c, float psize, Vect3d pmid)
{
float dmax, dsq, dk;
int k;

 dmax = psize;                               
 dsq = 0.0;                                 
 
 dk = XPos(c) - pmid.x;               
 if (dk < 0)                             
  dk = - dk;
 if (dk > dmax)                          
   dmax = dk;
    
 dk -= ((float) 0.5) * psize;             
 if (dk > 0)
  dsq += dk * dk;                     

 dk = YPos(c) - pmid.y;              
 if (dk < 0)                             
  dk = - dk;
    
 if (dk > dmax)                          
  dmax = dk;
 
 dk -= ((float) 0.5) * psize;             
 if (dk > 0)
  dsq += dk * dk;                     

 dk = ZPos(c) - pmid.z;               
 if (dk < 0)                            
  dk = - dk;
    
 if (dk > dmax)                          
  dmax = dk;
    
 dk -= ((float) 0.5) * psize;            
 if (dk > 0)
  dsq += dk * dk;                     

 return (dsq > Rcrit2(c) && dmax > ((float) 1.5) * psize);     
}

/////////////////////////////// calcforcerec //////////////////////////////////

void World3d::calcforcerec(nodeptr *nptr, nodeptr *np, cellptr cptr, cellptr bptr, nodeptr p, float psize, Vect3d pmid)
{
float poff;
nodeptr q;
int k;
Vect3d nmid;

 poff = psize / 4.0;                        

 if (Type(p) == CELL) 
 {                      
  for (q = More(p); q != Next(p); q = Next(q)) 
  {
   nmid.x = pmid.x + (XPos(q) < pmid.x ? - poff : poff);
   nmid.y = pmid.y + (YPos(q) < pmid.y ? - poff : poff);
   nmid.z = pmid.z + (ZPos(q) < pmid.z ? - poff : poff);

   calcforce(nptr, np, cptr, bptr, q, psize / 2.0, nmid);                                            
   }
  } 
 else 
 {                                   
  nmid.x = pmid.x + (XPos(p) < pmid.x ? - poff : poff);
  nmid.y = pmid.y + (YPos(p) < pmid.y ? - poff : poff);
  nmid.z = pmid.z + (ZPos(p) < pmid.z ? - poff : poff);

  calcforce(nptr, np, cptr, bptr, p, psize / 2.0, nmid);                                             
 }
}

//////////////////////////////// totalforce ///////////////////////////////////

void World3d::totalforce(bodyptr p0, cellptr cptr, cellptr bptr)
{
Vect3d pos0, acc0, acc0tmp, acc0tmp2;
float phi0;

 pos0 = setv(Pos(p0));                          
 phi0 = 0.0;                                    
 acc0 = clrv();                                                                  
                                               
 if (quad)                                                                                
  Acc(p0)= setv(addv(cellforce(interact, cptr, pos0, &phi0, acc0), nodeforce(bptr, interact + actlen, pos0, &phi0, acc0)));
  else                                          
  Acc(p0)= setv(addv(nodeforce(interact, cptr, pos0, &phi0, acc0), nodeforce(bptr, interact + actlen, pos0, &phi0, acc0)));                                                
 
 Phi(p0) = phi0;                              
 nbbcalc += interact + actlen - bptr;           
 nbccalc += cptr - interact;                   
}

//////////////////////////////// Node force ///////////////////////////////////

Vect3d World3d::nodeforce(cellptr start, cellptr finish, Vect3d pos0, float *phi0, Vect3d acc0)
{
cellptr p;
float eps2, dr2, drab, phi_p, mr3i;
Vect3d dr;

 eps2 = eps * eps;                           

 for (p = start; p < finish; p++) 
 {         
  DOTPSUBV(dr2, dr, Pos(p), pos0);        
  dr2 += eps2;                            
  drab = sqrt(dr2);                       
  phi_p = Mass(p) / drab;               
  *phi0 -= phi_p;                         
  mr3i = phi_p / dr2;                     
  ADDMULVS(acc0, dr, mr3i);               
 }
 return(acc0);
}

/////////////////////////////// Cell force ////////////////////////////////////

Vect3d World3d::cellforce(cellptr start, cellptr finish, Vect3d pos0, float *phi0, Vect3d acc0)
{
cellptr p;
float eps2, dr2, drab, phi_p, mr3i, drqdr, dr5i, phi_q;
Vect3d dr, qdr;

 eps2 = eps * eps;
    
 for (p = start; p < finish; p++) 
 {          
  DOTPSUBV(dr2, dr, Pos(p), pos0);       
  dr2 += eps2;
  drab = sqrt(dr2);
  phi_p = Mass(p) / drab;
  mr3i = phi_p / dr2;
  DOTPMULMV(drqdr, qdr, Quad(p), dr);     
  dr5i = ((float) 1.0) / (dr2 * dr2 * drab);
  phi_q = ((float) 0.5) * dr5i * drqdr;
  *phi0 -= phi_p + phi_q;                
  mr3i += ((float) 5.0) * phi_q / dr2;
  ADDMULVS2(acc0, dr, mr3i, qdr, -dr5i);  
 }
 return(acc0);
}
