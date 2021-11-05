//ROOT
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TRandom3.h"

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>

using namespace std;

Double_t get_cos_alpha_par_2(Double_t L, Double_t R, Double_t d);

Int_t plots_SiPM_array_alpha2() {

  Double_t L = 3.0;
  Double_t R = 208.0;
  Double_t d = 0.5;

  Double_t cos_alpha_par_2;

  cos_alpha_par_2 = get_cos_alpha_par_2(L,R,d);

  cout<<"alpha1 = "<<2.0*TMath::ACos(cos_alpha_par_2)*180.0/TMath::Pi()<<endl;
  
  return 0;
}

Double_t get_cos_alpha_par_2(Double_t L, Double_t R, Double_t d){
  //
  Double_t A;
  Double_t B;
  Double_t C;
  Double_t D;
  //
  Double_t cos1;
  Double_t cos2;
  //
  A = (1.0 + L*L/4.0/R/R);
  B = (d*L/2/R/R);
  C = -(1.0 - d*d/4.0/R/R);
  D = B*B - 4.0*A*C;
  //
  if(D >= 0){
    cos1 = (-B + TMath::Sqrt(D))/2.0/A;
    cos2 = (-B - TMath::Sqrt(D))/2.0/A;  
  }
  else{
    cos1 = -999.0;
    cos2 = -999.0;
  }
  //  
  //cout<<"cos1 = "<<cos1<<endl
  //    <<"cos2 = "<<cos2<<endl;
  //cout<<"alpha1 = "<<2.0*TMath::ACos(cos1)*180.0/TMath::Pi()<<endl
  //    <<"alpha2 = "<<2.0*TMath::ACos(cos2)*180.0/TMath::Pi()<<endl;
  //
  return cos1;
}
