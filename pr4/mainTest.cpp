
#include <iostream>
#include <memory>
#include <ctime>

#include "BasicsRender.hpp"
#include "Matrix.hpp"
#include "2DObjects.hpp"
#include "3DObjects.hpp"
#include "PLYObject.hpp"
#include "Scene.hpp"

//g++ -std=c++11 -I ../libs2 mainTest.cpp -O3 -fopenmp -o main

using namespace std;

int main(){
  unsigned t0, t1;
  double read_time;

  //Camera c(Point(-3, 0, 0), Direction(0,0,1), Direction(0,1,0), Direction(1,0,0));
  Camera c(Point(-14, 0, 0), 140, true);
  //Camera c(Point(-14, 0, 0), 105, 120, true);
  //Camera c(Point(-14, 0, 0));

  Scene scn(c);
  shared_ptr<Object> pared_fr (new FinitePlane( Point(4,0,0) , Direction(0,6,0), Direction(0,0,6) ));  pared_fr->mt().kd = RGB255(55, 156, 156);
  shared_ptr<Object> pared_iz (new FinitePlane( Point(0,0,4) , Direction(6,0,0), Direction(0,6,0) ));  pared_iz->mt().kd = RGB255(173, 207, 116);
  shared_ptr<Object> pared_de (new FinitePlane( Point(0,0,-4), Direction(6,0,0), Direction(0,6,0) ));  pared_de->mt().kd = RGB255(116, 116, 207);
  shared_ptr<Object> pared_up (new FinitePlane( Point(0,4,2) , Direction(1.5,0,0), Direction(0,0,1.5) ));  pared_up->mt().kd = RGB255(204, 74, 74);
  shared_ptr<Object> pared_upp (new FinitePlane( Point(0,4,-2) , Direction(1.5,0,0), Direction(0,0,1.5) ));  pared_up->mt().kd = RGB255(204, 74, 74);
  shared_ptr<Object> pared_up2 (new FinitePlane( Point(0,4,0) , Direction(6,0,0), Direction(0,0,6) ));  pared_up->mt().kd = RGB255(204, 74, 74);
  shared_ptr<Object> pared_do (new FinitePlane( Point(0,-4,0), Direction(6,0,0), Direction(0,0,6) ));  pared_do->mt().kd = RGB255(156, 156, 156);
  shared_ptr<Object> ftl (new FinitePlane( Point(3,-3,-3), Direction(1,0.3,0), Direction(0,0,1) ));  ftl->mt().ks = RGB(0.6); ftl->mt().kd = RGB(0.1);

  pared_up->mt().kd = RGB255(80*255,80*20,80*20); pared_up->emit = true;
  pared_upp->mt().kd = RGB255(80*20,80*20,80*255); pared_upp->emit = true;
  shared_ptr<Object> espejo (new FinitePlane( Point(2,0,2) , Direction(0,6,0), Direction(3,0,-3) ));
  espejo->mt().ks = RGB(0.7); espejo->mt().kd = RGB(0.1);
  /*pared_do->mt().ks = RGB(0.2);*/ pared_do->mt().kd = RGB255(150, 74, 74);

  shared_ptr<Object> pelota1 ( new Pelota( Point(3, 0, 0), 2.5) );   pelota1->mt().kd = RGB255(204, 55, 55); //pelota1->mt().ks = RGB(0.3);// RGB255(204, 55, 55)
  shared_ptr<Object> pelota2 ( new Pelota( Point(1, 0, -2.5), 1.5) );  pelota2->mt().kd = RGB255(55, 204, 55); //pelota2->mt().ks = RGB(0.2);
  shared_ptr<Object> pelota3 ( new Pelota( Point(1, -2.1, 2), 1.5) );    pelota3->mt().kd = RGB255(55, 55, 204);
  pelota2->mt().is_dielectric = true; pelota1->mt().kd = 0; pelota1->mt().ks = 0; pelota1->mt().kt = 0.9;
  pelota3->mt().is_dielectric = true; pelota1->mt().kd = 0; pelota1->mt().ks = 0; pelota1->mt().kt = 0.9;
  //pelota2->mt().ks = RGB(0.35);
  shared_ptr<Object> ico ( new PLYObject("../objects/icosahedron.ply") );
  //scn.addObj(ico);

  scn.addObj(pared_fr);
  scn.addObj(pared_iz);
  scn.addObj(pared_de);
  scn.addObj(pared_up);
  scn.addObj(pared_upp);
  scn.addObj(pared_up2);
  scn.addObj(pared_do);
  //scn.addObj(espejo);

  //scn.addObj(pelota1);
  scn.addObj(pelota2);
  scn.addObj(pelota3);

  //LightPoint lp(Point(2,0,0)); lp.force = RGB(30);//RGB(3,3,5)
  //LightPoint luz_up(Point(0,3.5,0)); luz_up.force = RGB(300);
  //scn.addLight(luz_up);
  //scn.addObj(ftl);
  //scn.addLight(lp);
  int g[] = {15,100,1000};//{20,50,100,200,500,1000};//{10,50,100,150,200,250,300,400,500,750,1000,1500,2000,2500,3000,5000};
  string gg[] = {"15w","100w","1000w"};//{"20f","50f","100f","200f","500f","1000f"};//{"10","50","100","150","200","250","300","400","500","750","1000","1500","2000","2500","3000","5000"};
  int i;
  for (i=0;i<3;i++){//16


  t0 = clock();
  scn.PathTracing(1000, 1000, g[i]);//g[i]
  //scn.PathTracing(600, 600, 40);
  t1 = clock();
  read_time = (double(t1-t0)/CLOCKS_PER_SEC);
  cout << gg[i] << " RT: " << read_time << " segundos" << endl;

  t0 = clock();
  Tone_Mapper tm = scn.getTonerImg();
  tm.apply_tone_mapper(clamp_gamma, 255, 0.6);
  tm.exportBMP(gg[i]);
  //scn.exportHDR(gg[i]);
  //scn.exportImg("loqsea.bpm");
  t1 = clock();
  read_time = (double(t1-t0)/CLOCKS_PER_SEC);
  cout << "Tone mapping && Export: " << read_time << " segundos" << endl;
  };
}
