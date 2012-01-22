#include "3dworld.h"

////////////////////////////////// Tree ///////////////////////////////////////

void World3d::tree()
{
bodyptr p;
int i;

 newtree();                                  
 racine = makecell();                         
 Pos(racine) = clrv();                         
 maxbox();                                

 for(p = bodyz; p < bodyz+NbBody; p++)
  newbody(p);                               

 prof = 0;                                 
 treeGpoint(racine, rsize, 0);                   
 linktree((nodeptr) racine, NULL);  
 
 if (quad)                                
  adjustforce(racine);                                                                        
}

//////////////////////////////// New Tree /////////////////////////////////////

void World3d::newtree()
{
static bool fc = TRUE;
nodeptr p;

 if (!fc) 
 {                          
  p = (nodeptr) racine;                    
 
  while (p != NULL)                      
   if (Type(p) == CELL) 
   {             
    Next(p) = freecell;             
    freecell = p;                  
    p = More(p);                    
   } 
   else                              
    p = Next(p);                    
 } 
 else                                      
  fc = FALSE;                    
    
 racine = NULL;                                
 ncell = 0;                                  
}

/////////////////////////////// Make Cell /////////////////////////////////////

cellptr World3d::makecell()
{
cellptr c;
int i;

 if (freecell == NULL)                       
  c = (cellptr) allocate(sizeof(Cell));   
 else 
 {                                      
  c = (cellptr) freecell;                 
  freecell = Next(c);                    
 }

 Type(c) = CELL;                             
 Update(c) = FALSE;                         

  for (i = 0; i < 8; i++)                  
   Subp(c)[i] = NULL;                     

 ncell++;                                    
 return (c);                                
}

//////////////////////////////// maxbox ///////////////////////////////////////

void World3d::maxbox()
{
bodyptr p;

float dmax=0.0;
float d;

 for(p = bodyz; p < bodyz+NbBody; p++)
 {
  d = MAX (XPos(p), MAX (YPos(p), ZPos(p)) );

  if (d > dmax)
   dmax = d;
 }

 while (rsize < 2 * dmax)
  rsize = 2 * rsize;
}

/////////////////////////////// New Body /////////////////////////////////////

void World3d::newbody(bodyptr p)
{
cellptr q, c;
int qind, k;
float qsize, dist2;
Vect3d distv;

 q = racine;                                   
 qind = octant(p, q);                      
 qsize = rsize;                              
   
 while (Subp(q)[qind] != NULL) 
 {             
  if (Type(Subp(q)[qind]) == BODY) 
  {      
   distv = subv(Pos(p), Pos(Subp(q)[qind]));
   dist2 = dotvp(distv, distv);
  
   if (dist2 == 0.0)                   
    error("Newbody Error");

   c = makecell();                     

   XPos(c) = XPos(q) + (XPos(p) < XPos(q) ? - qsize : qsize) / 4.0;
   YPos(c) = YPos(q) + (YPos(p) < YPos(q) ? - qsize : qsize) / 4.0;
   ZPos(c) = ZPos(q) + (ZPos(p) < ZPos(q) ? - qsize : qsize) / 4.0;

   Subp(c)[octant((bodyptr) Subp(q)[qind], c)] = Subp(q)[qind];
   Subp(q)[qind] = (nodeptr) c;       
  }

  q = (cellptr) Subp(q)[qind];            
  qind = octant(p, q);                  
  qsize = qsize / 2.0;                   
 }
 
 Subp(q)[qind] = (nodeptr) p;                
}

///////////////////////////////// Octant //////////////////////////////////////

int World3d::octant(bodyptr p, cellptr q)
{
int ind=0;

 if (XPos(q) <= XPos(p))
  ind += 4;
 if (YPos(q) <= YPos(p))
  ind += 2;
 if (ZPos(q) <= ZPos(p))
  ind += 1;

return (ind);
}

//////////////////////////////// treeGpoint ///////////////////////////////////

void World3d::treeGpoint(cellptr p, float psize, int lev)
{
Vect3d cmpos, tmpv;
int i, k;
nodeptr q;
float dpq;

 prof = MAX(prof, lev);                  
 Mass(p) = 0.0;                             
 cmpos=clrv();                               

 for (i = 0; i < 8; i++)                     
  if ((q = Subp(p)[i]) != NULL) 
  {         
   if (Type(q) == CELL)                
    treeGpoint((cellptr) q, psize/2.0, lev+1);
                                               
   Update(p) |= Update(q);             
   Mass(p) += Mass(q);                 
   tmpv=mulvs(Pos(q), Mass(q));        
   cmpos=addv(cmpos, tmpv);            
  }
  
 if (Mass(p) > 0.0)                       
  cmpos=divvs(cmpos, Mass(p));            
 else                                     
  cmpos=setv(Pos(p));                     

 distancelimite(p, cmpos, psize);                  
 Pos(p)=setv(cmpos);                      
}

/////////////////////////////// distancelimite ////////////////////////////////

void World3d::distancelimite(cellptr p, Vect3d cmpos, float psize)
{
float bmax2, d;
int k;

 if (theta == 0.0)                         
  Rcrit2(p) = rsqr(2 * rsize);                  
 else 
 {                                      
  d=distv(cmpos, Pos(p));                 
  Rcrit2(p) = rsqr(psize / theta + d);    
 }
}

///////////////////////////////// link tree ///////////////////////////////////

void World3d::linktree(nodeptr p, nodeptr n)
{
int ndesc, i;
nodeptr desc[8+1];

 Next(p) = n;                               

 if (Type(p) == CELL) 
 {                      
  ndesc = 0;                              
 
  for (i = 0; i < 8; i++)                 
   if (Subp(p)[i] != NULL)            
    desc[ndesc++] = Subp(p)[i];     
        
  More(p) = desc[0];                      
  desc[ndesc] = n;                        
  
  for (i = 0; i < ndesc; i++)            
   linktree(desc[i], desc[i+1]);     
 }
}

//////////////////////////////// adjustforce //////////////////////////////////

void World3d::adjustforce(cellptr p)
{
int ndesc, i;
nodeptr desc[8], q;
Vect3d dr;
float drsq;
Matrix drdr, Idrsq, tmpm;

 ndesc = 0;                                 

 for (i = 0; i < 8; i++)                     
  if (Subp(p)[i] != NULL)                
   desc[ndesc++] = Subp(p)[i];         
  
 Quad(p)=clrm();                             
 for (i = 0; i < ndesc; i++) 
 {               
  q = desc[i];                             
   if (Type(q) == CELL)                    
    adjustforce((cellptr) q);               
  dr = subv(Pos(q), Pos(p));              
  drdr = outvp(dr, dr);                   
  drsq = dotvp(dr, dr);                   
  Idrsq = setmi();                       
  Idrsq = mulms(Idrsq, drsq);             
  tmpm = mulms(drdr, 3.0);                
  tmpm = subm(tmpm, Idrsq);               
  tmpm = mulms(tmpm, Mass(q));            
   if (Type(q) == CELL)                   
    tmpm = addm(tmpm, Quad(q));        
  Quad(p) = addm(Quad(p), tmpm);          
 }
}


