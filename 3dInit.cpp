#include "3dworld.h"

////////////////////////////// Init Variable //////////////////////////////////

void World3d::InitVariable()
{
 freecell=NULL;
 rsize=1.0;
 zobs = 850;
 aox=0.0; aoy=0.0; aoz=0.0;
 ScaleFactor = InitWorldSize;
 bodyz = (bodyptr) allocate(NbBody * sizeof(Body));
}

/////////////////////////////// Init Body /////////////////////////////////////

void World3d::InitBody()
{
 switch(model)
 {
 case 0:
  InitBodyUniform();
   break;
 case 1:
  InitBodySpiral();
    break;
 case 2:
  InitBodyTwoPart();
    break;
 case 3:
  InitBodyTwoPartSpiral();
    break;      
 case 4:
  InitBodySolarSys();
    break;   
 case 5:
  InitBodySTL();
    break;   
 case 6:
  InitBodySSP();
    break;   
 case 7:
  InitBody2Body();  
    break;             
 };

 if(blackhole)
  InitBodyBlackHole();
}

////////////////////////////////// 2 Body /////////////////////////////////////

void World3d::InitBody2Body()
{
bodyptr p;
float   Ms;
float   Mt;

 p = bodyz;
 
 // Systeme param
 Ms = 80.0;
 Mt  = 1.0; 
    
 // P1
 
 Type(p) = BODY;
 Mass(p) = Ms;
 XPos(p) = 0.0;
 YPos(p) = 0.0;                        
 ZPos(p) = 0.0;
 Vel(p)  = clrv();
 Acc(p)  = clrv();
    
 // P2
 p++; 
 
 Type(p) = BODY;
 Mass(p) = Mt;
 XPos(p) = 0.8;
 YPos(p) = 0.03;                         
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = 0.03 ;
 Vel(p).y = -8.1;
 Vel(p).z = 0.0;
    
}

///////////////////////// Soleil Soleil Planete(s) ////////////////////////////

void World3d::InitBodySSP()
{
bodyptr p;
float   Ms;
float   Mt, Mlu, Mlu2;

 p = bodyz;
 
 // Systeme param
 Ms = 80.0;
 Mt  = 80.0; 
 Mlu = 1.0;   
 Mlu2 = 1.0;   
     
 // P1
 
 Type(p) = BODY;
 Mass(p) = Ms;
 XPos(p) = -0.45;
 YPos(p) = 0.0;                        
 ZPos(p) = 0.0;
 Vel(p)  = clrv();
 Acc(p)  = clrv();
    
 // P2
 p++; 
 
 Type(p) = BODY;
 Mass(p) = Mt;
 XPos(p) = 0.45;
 YPos(p) = 0.0;                        
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = 0.0 ;
 Vel(p).y = 0.0;
 Vel(p).z = 0.0;
 
 // P3
 p++; 
 
 Type(p) = BODY;
 Mass(p) = Mlu;
 XPos(p) = 0.25;
 YPos(p) = 0.35;                       
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = 0.0;
 Vel(p).y = 0.0;
 Vel(p).z = 0.0;      

 // P4  
 if(NbBody==4)
 { 
  p++; 
 
  Type(p) = BODY;
  Mass(p) = Mlu2;
  XPos(p) = 0.2501;
  YPos(p) = 0.35;                       
  ZPos(p) = 0.0;
  Acc(p)  = clrv(); 
  Vel(p).x = 0.0;
  Vel(p).y = 0.0;
  Vel(p).z = 0.0;     
 }   
       
}

/////////////////////////// Soleil Terre Lune /////////////////////////////////

void World3d::InitBodySTL()
{
bodyptr p;
float   Ms;
float   Mt, Mlu;
float   rt, rlu;
float   vt, vlu;

 p = bodyz;
 
 // Systeme param
 Ms = 1.0;
 
 rt  = 1.0        ; Mt  = Ms /80.0  ; vt  = 0.71 ; //rt=2.0 vt=0.71/1.414 rlu=*1.06 vlu=*1.1
 rlu = rt * 1.1  ;  Mlu = Mt / 81.0 ; vlu = vt*1.2  ;     
    
 // Soleil
 
 Type(p) = BODY;
 Mass(p) = Ms;
 XPos(p) = 0.0;
 YPos(p) = 0.0;                         
 ZPos(p) = 0.0;
 Vel(p)  = clrv();
 Acc(p)  = clrv();
    
 // Terre
 p++; 
 
 Type(p) = BODY;
 Mass(p) = Mt;
 XPos(p) = rt;
 YPos(p) = 0.0;                         
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = 0.0 ;
 Vel(p).y = -vt;
 Vel(p).z = 0.0;
 
 // Lune
 p++; 
 
 Type(p) = BODY;
 Mass(p) = Mlu;
 XPos(p) = rlu;
 YPos(p) = 0.0;                         
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = -0.0;
 Vel(p).y = -vlu;
 Vel(p).z = 0.0;      
       
}

////////////////////////////// Solar System ///////////////////////////////////

void World3d::InitBodySolarSys()
{
bodyptr p;
float   Ms;
float   Mt, Mme, Mve, Mma, Mju, Msa, Mur, Mne, Mpl;
float   rt, rme, rve, rma, rju, rsa, rur, rne, rpl;
float   vt, vme, vve, vma, vju, vsa, vur, vne, vpl;

 p = bodyz;
 
 // Systeme param
 Ms = 1.0;
 
 rt  = 1.0        ; Mt  = Ms/333333.0 ; vt  = 0.71 ;  
 rme = rt * 0.387 ; Mme = Mt * 0.0553 ; vme = vt * 48.0 / 30.0 ;
 rve = rt * 0.723 ; Mve = Mt * 0.815  ; vve = vt * 35.0 / 30.0 ;
 rma = rt * 1.524 ; Mma = Mt * 0.1074 ; vma = vt * 24.0 / 30.0 ;
 rju = rt * 5.203 ; Mju = Mt * 317.89 ; vju = vt * 13.0 / 30.0 ;
 rsa = rt * 9.509 ; Msa = Mt * 95.168 ; vsa = vt * 10.0 / 30.0 ;
 rur = rt * 19.18 ; Mur = Mt * 14.559 ; vur = vt * 7.0  / 30.0 ;
 rne = rt * 30.07 ; Mne = Mt * 17.617 ; vne = vt * 5.0  / 30.0 ;
 rpl = rt * 39.44 ; Mpl = Mt * 0.17   ; vpl = vt * 5.0  / 30.0 ;       
 
 // Soleil
 
 Type(p) = BODY;
 Mass(p) = Ms;
 XPos(p) = 0.0;
 YPos(p) = 0.0;                         
 ZPos(p) = 0.0;
 Vel(p)  = clrv();
 Acc(p)  = clrv();
    
 // Terre
 p++; 
 
 Type(p) = BODY;
 Mass(p) = Mt;
 XPos(p) = rt;
 YPos(p) = 0.0;                         
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = 0.0 ;
 Vel(p).y = -vt;
 Vel(p).z = 0.0;
 
 // Mercure
 p++; 
 
 Type(p) = BODY;
 Mass(p) = Mme;
 XPos(p) = rme;
 YPos(p) = 0.0;                         
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = 0.0;
 Vel(p).y = -vme;
 Vel(p).z = 0.0;      
          
 // Venus
 p++; 
 
 Type(p) = BODY;
 Mass(p) = Mve;
 XPos(p) = rve;
 YPos(p) = 0.0;                         
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = 0.0;
 Vel(p).y = -vve;
 Vel(p).z = 0.0;    
    
 // Mars
 p++; 

 Type(p) = BODY;
 Mass(p) = Mma;
 XPos(p) = rma;
 YPos(p) = 0.0;                         
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = 0.0;
 Vel(p).y = -vma;
 Vel(p).z = 0.0;
  
 // Jupiter
 p++; 

 Type(p) = BODY;
 Mass(p) = Mju;
 XPos(p) = rju;
 YPos(p) = 0.0;                         
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = 0.0;
 Vel(p).y = -vju;
 Vel(p).z = 0.0;  
 
 // Saturne
 p++; 

 Type(p) = BODY;
 Mass(p) = Msa;
 XPos(p) = rsa;
 YPos(p) = 0.0;                         
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = 0.0;
 Vel(p).y = -vsa;
 Vel(p).z = 0.0;  
 
 // Uranus
 p++; 

 Type(p) = BODY;
 Mass(p) = Mur;
 XPos(p) = rur;
 YPos(p) = 0.0;                         
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = 0.0;
 Vel(p).y = -vur;
 Vel(p).z = 0.0;  
 
 // Neptune
 p++; 

 Type(p) = BODY;
 Mass(p) = Mne;
 XPos(p) = rne;
 YPos(p) = 0.0;                         
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = 0.0;
 Vel(p).y = -vne;
 Vel(p).z = 0.0;  
 
 // Pluton
 p++; 

 Type(p) = BODY;
 Mass(p) = Mpl;
 XPos(p) = rpl;
 YPos(p) = 0.0;                         
 ZPos(p) = 0.0;
 Acc(p)  = clrv(); 
 Vel(p).x = 0.0;
 Vel(p).y = -vpl;
 Vel(p).z = 0.0;                 
}

////////////////////////////////// Spiral /////////////////////////////////////

void World3d::InitBodySpiral()
{
bodyptr p;

float   rmin  = 0.0;
float   rmax  = 1.0;
float   tmp;
Vect3d  acc_i;

float   cost, sint, theta_i;
float   r_i, vcir_i;
float   rmin2, rmax2;

 rmin2  = rmin * rmin;
 rmax2  = rmax * rmax;

 for(p = bodyz; p < bodyz+NbBody; p++)
 {
  Type(p) = BODY;
  Acc(p)  = clrv();
  Mass(p) = 1.0/NbBody;

  tmp     =  xrand(1.0,16.0);
  tmp     *= tmp ; tmp--;
  tmp     /= 16*16-1;
  //tmp     = xrand(0.0,1.0);                      // uniform
  r_i     = sqrt(rmin2 + tmp * (rmax2 - rmin2));

  theta_i = xrand(0.0, 2*PI);

  cost    = cos(theta_i);
  sint    = sin(theta_i);

  XPos(p) = r_i * sint;
  if(p< bodyz+NbBody/2)
   YPos(p) = r_i/6 * cost;                         
  else
   YPos(p) = r_i/10 * cost;                       
  ZPos(p) = 0.0;

  tmp     = 1.0/(1.0 + XPos(p)*XPos(p) + YPos(p)*YPos(p) + ZPos(p)*ZPos(p));
  tmp    *= -sqrt(tmp);

  acc_i   = mulvs(Pos(p), tmp);

  vcir_i  = sqrt(r_i * absv(acc_i));

  Vel(p).x = vcir_i * cost ;
  Vel(p).y = -vcir_i * sint ;
  Vel(p).z = 0.0;

 } // all body

}

//////////////////////////////// Black Hole ///////////////////////////////////

void World3d::InitBodyBlackHole()
{
bodyptr p;

  p = bodyz+NbBody-1;

  Type(p)= BODY;
  XPos(p) = 0.0;
  YPos(p) = 0.0;
  ZPos(p) = 0.0;
  Vel(p) = clrv();
  Acc(p) = clrv();
  Mass(p)= NbBody/1000.0;
}

//////////////////////////////// Uniform //////////////////////////////////////

void World3d::InitBodyUniform()
{
bodyptr p;

 for(p = bodyz; p < bodyz+NbBody; p++)
 {

   switch(BallSphere)
   {
   case 0:
     Pos(p) = pickball(1.0);
     break;
   case 1:
     Pos(p) = picksphere(1.0);
      break;
   case 2:
     Pos(p) = pickinbox(1.0);
   }

   Type(p)= BODY;
   //float vabs=0.5;
   //Vel(p) = setvs(xrand(-vabs,vabs),xrand(-vabs,vabs),xrand(-vabs,vabs));
   Vel(p) = clrv();
   Acc(p) = clrv();
   Mass(p)= 1.0/NbBody;
 }
}

/////////////////////////// Two Part -> Spiral ////////////////////////////////

void World3d::InitBodyTwoPartSpiral()
{
bodyptr p;

float centre1   = 0.4;
float diametre1 = 0.6;
float centre2   = - 0.4;
float diametre2 = 0.6;

 for(p = bodyz; p < bodyz+NbBody; p++)
 {
  if(p< bodyz+NbBody/2)
  {

   switch(BallSphere)
   {
   case 0:
     Pos(p) = pickball(diametre1/2.0);
     break;
   case 1:
     Pos(p) = picksphere(diametre1/2.0);
      break;
   case 2:
     Pos(p) = pickinbox(diametre1/2.0);
   }

   XPos(p) += centre1;

   Type(p)= BODY;
   Vel(p).x = 0.0;
   Vel(p).y = 0.4 ;
   Vel(p).z = 0.0;
   Acc(p) = clrv();
   Mass(p)= 1.0/NbBody;
  }
 else
  {
   switch(BallSphere)
   {
   case 0:
     Pos(p) = pickball(diametre2/2.0);
     break;
   case 1:
     Pos(p) = picksphere(diametre2/2.0);
      break;
   case 2:
     Pos(p) = pickinbox(diametre2/2.0);
   }

   XPos(p) += centre2;

   Type(p)= BODY;
   Vel(p).x = 0.0;
   Vel(p).y = -0.4 ;
   Vel(p).z = 0.0;
   Acc(p) = clrv();
   Mass(p)= 1.0/NbBody;
  }

 }
}

////////////////////////////////// Two Part ///////////////////////////////////

void World3d::InitBodyTwoPart()
{
bodyptr p;

float centre1   = 0.5;
float diametre1 = 0.7;
float centre2   = - 0.5;
float diametre2 = 0.7;


 for(p = bodyz; p < bodyz+NbBody; p++)
 {
  if(p< bodyz+NbBody/2)
  {

   switch(BallSphere)
   {
   case 0:
     Pos(p) = pickball(diametre1/2.0);
     break;
   case 1:
     Pos(p) = picksphere(diametre1/2.0);
      break;
   case 2:
     Pos(p) = pickinbox(diametre1/2.0);
   }

   XPos(p) += centre1; YPos(p) += centre1; ZPos(p) += centre1;

   Type(p)= BODY;
   Vel(p) = clrv();
   Acc(p) = clrv();
   Mass(p)= 1.0/NbBody;
  }
 else
  {
   switch(BallSphere)
   {
   case 0:
     Pos(p) = pickball(diametre2/2.0);
     break;
   case 1:
     Pos(p) = picksphere(diametre2/2.0);
      break;
   case 2:
     Pos(p) = pickinbox(diametre2/2.0);
   }

   XPos(p) += centre2; YPos(p) += centre2; ZPos(p) += centre2;

   Type(p)= BODY;
   Vel(p) = clrv();
   Acc(p) = clrv();
   Mass(p)= 1.0/NbBody;
  }

 }
}

