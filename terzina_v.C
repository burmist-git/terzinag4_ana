//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <time.h>

using namespace std;

const Double_t Re = 6371300;       //m
const Double_t Me = 5.9742*1.0e24; //kg

Double_t g_gravity(Double_t R);
Double_t v_satellite(Double_t R, Double_t G);

Int_t terzina_v(){
  
  Double_t R_s = Re+525000;
  Double_t v_s = v_satellite(R_s, g_gravity(R_s));
  cout<<v_s<<endl;

  Double_t v_s_e = 2*TMath::Pi()*(Re+525000)/95/60.0;

  cout<<v_s_e<<endl;
  
  return 0;
}

Double_t g_gravity(Double_t R){
  return TMath::G()*Me/R/R;
}

Double_t v_satellite(Double_t R, Double_t G){
  return TMath::Sqrt(TMath::G()*Me/R);
}
