#ifndef sim_trk_info_str_hh
#define sim_trk_info_str_hh 1

#include <iostream>
#include <vector>

//root
#include "TMath.h" 

struct sim_trk_info_str {
  //
  double theta;
  double phi;
  double x_int;
  double y_int;
  double z_int;
  double xe0;
  double ye0;
  double ze0;
  double distToEarth;
  double distToTerzina;
  double angleTrzinaTrk;
  double nphotons_per_m2;  
  //
  sim_trk_info_str(){
    theta = -999.0;
    phi = -999.0;
    x_int = -999.0;
    y_int = -999.0;
    z_int = -999.0;
    xe0 = -999.0;
    ye0 = -999.0;
    ze0 = -999.0;
    distToEarth = -999.0;
    distToTerzina = -999.0;
    angleTrzinaTrk = -999.0;
    nphotons_per_m2 = 0.0;
  }
  void printInfo(){
    std::cout<<"theta                      "<<theta<<std::endl
	     <<"phi                        "<<phi<<std::endl
	     <<"x_int                      "<<x_int<<std::endl
	     <<"y_int                      "<<y_int<<std::endl
	     <<"z_int                      "<<z_int<<std::endl
	     <<"xe0                        "<<xe0<<std::endl
      	     <<"ye0                        "<<ye0<<std::endl
      	     <<"ze0                        "<<ze0<<std::endl;
    std::cout<<"distToEarth                "<<distToEarth<<std::endl
	     <<"distToTerzina              "<<distToTerzina<<std::endl
	     <<"angleTrzinaTrk             "<<angleTrzinaTrk<<std::endl
      	     <<"180 - angleTrzinaTrk (deg) "<<180.0 - angleTrzinaTrk/TMath::Pi()*180.0<<std::endl
	     <<"nphotons_per_m2            "<<nphotons_per_m2<<std::endl;
  }
};

#endif
