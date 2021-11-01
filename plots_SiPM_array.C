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

///////////////////////////////////////
const Int_t nSiPM_x = 37;            //
const Int_t nSiPM_y = 37;            //
const Int_t nSiPM = nSiPM_x*nSiPM_y; //
//                                   //
const Int_t xDim = 800;              // pixels
const Int_t yDim = 800;              // pixels
const Int_t delta = 50;              // pixels
//                                   //
const Int_t n_pjs_enge = 100;        //
const Double_t r_pjs   = 65;         // mm
const Double_t dx_sipm = 3;          // mm
const Double_t dy_sipm = 3;          // mm
const Double_t delta_sipm = 0.5;     // mm
const Double_t delta_x0   = 0.1;     // mm
const Double_t delta_y0   = 0.1;     // mm
//                                   //
const Double_t x_pixel_per_mm = (xDim - 2*delta)/2.0/r_pjs;    // pixel/mm
const Double_t y_pixel_per_mm = (yDim - 2*delta)/2.0/r_pjs;    // pixel/mm
//
const Int_t xDim_mm = xDim/x_pixel_per_mm;                     // mm
const Int_t yDim_mm = yDim/y_pixel_per_mm;                     // mm
const Int_t delta_mm = delta/x_pixel_per_mm;                   // mm
//
const Double_t r_pjs_pixel   = x_pixel_per_mm*r_pjs;           // pixel
const Double_t dx_sipm_pixel = x_pixel_per_mm*dx_sipm;         // pixel
const Double_t dy_sipm_pixel = y_pixel_per_mm*dy_sipm;         // pixel
//const Double_t delta_sipm_pixel = x_pixel_per_mm*delta_sipm; // pixel
/////////////////////////////////////////////////////////////////

TRandom3 *rnd = new TRandom3(112312);

void buildProjectionPlaneEdge(TLine *ln_pjs[n_pjs_enge]);
void addSiPM(TLine *ln[nSiPM][4], Int_t sipmID, Double_t x0, Double_t y0);
bool if_SiPM_is_in(TLine *ln[4]);
bool if_point_is_in_circle(TLine *ln);

using namespace std;

Int_t plots_SiPM_array() {

  //cout<<r_pjs_pixel<<endl
  //  <<dx_sipm_pixel<<endl
  //  <<dy_sipm_pixel<<endl;

  //projection plane edge
  TLine *ln_pjs[n_pjs_enge];
  buildProjectionPlaneEdge(ln_pjs);

  //SiPM
  TLine *ln_sipm[nSiPM][4];

  //addSiPM( ln_sipm, 0, 0, 0);
  //addSiPM( ln_sipm, 1, (3 + delta_sipm), (3 + delta_sipm));
  
  //build SiPM
  for(Int_t i = 0;i<nSiPM_x;i++){
    for(Int_t j = 0;j<nSiPM_y;j++){
      Int_t k = i*nSiPM_x + j;
      addSiPM( ln_sipm, k, (dx_sipm + delta_sipm)*i - xDim_mm/2.0 + delta_mm + delta_x0, (dy_sipm + delta_sipm)*j - yDim_mm/2.0 + delta_mm + delta_y0);
    }
  }
  
  TCanvas *c1 = new TCanvas("c1","c1",10,10,xDim,yDim);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);

  Int_t n_tot_SiPM = 0;
  
  for(Int_t i = 0;i<nSiPM;i++){  
    if(if_SiPM_is_in(ln_sipm[i])){
      ln_sipm[i][0]->Draw();
      ln_sipm[i][1]->Draw();
      ln_sipm[i][2]->Draw();
      ln_sipm[i][3]->Draw();
      n_tot_SiPM++;
    }
  }
  
  for(Int_t i = 0;i<n_pjs_enge;i++){
    ln_pjs[i]->Draw();
  }

  c1->SaveAs("c1_SiPM_projection_plane.pdf");

  /*
  cout<<"n tot SiPM               = "<<n_tot_SiPM<<endl
      <<"projection plane radius  = "<<r_pjs<<" mm"<<endl
      <<"SiPM size                = "<<dx_sipm<<"x"<<dy_sipm<<" mm"<<endl
      <<"Pitch size               = "<<dx_sipm + delta_sipm<<" mm"<<endl
      <<"projection plane surface = "<<TMath::Pi()*r_pjs*r_pjs<<" mm^2"<<endl
      <<"effective area surface   = "<<dx_sipm*dx_sipm*n_tot_SiPM<<" mm^2"<<endl
      <<"fill factor              = "<<dx_sipm*dx_sipm*n_tot_SiPM/(TMath::Pi()*r_pjs*r_pjs)<<endl;
  */

  printf("n tot SiPM               : %10d \n",n_tot_SiPM);
  printf("projection plane radius  : %10.2f %5s \n",r_pjs,"mm");
  printf("SiPM size                : %6d %1s %1d %5s \n",(int)dx_sipm,"x",(int)dy_sipm,"mm^2");
  printf("Pitch size               : %10.2f %5s \n",dx_sipm + delta_sipm,"mm");
  printf("Projection plane surface : %10.2f %5s \n",TMath::Pi()*r_pjs*r_pjs,"mm^2");
  printf("Effective area surface   : %10.2f %5s \n",dx_sipm*dx_sipm*n_tot_SiPM,"mm^2");
  printf("Fill factor              : %10.2f\n",dx_sipm*dx_sipm*n_tot_SiPM/(TMath::Pi()*r_pjs*r_pjs));
  

  cout<<endl;
  return 0;
}

bool if_SiPM_is_in(TLine *ln[4]){
  if(if_point_is_in_circle(ln[0]) &&
     if_point_is_in_circle(ln[1]) &&
     if_point_is_in_circle(ln[2]) &&
     if_point_is_in_circle(ln[3])){
    return true;
  }
  return false;
}

bool if_point_is_in_circle(TLine *ln){
  //
  Double_t x1 = ln->GetX1() - 0.5;
  Double_t y1 = ln->GetY1() - 0.5;
  Double_t x2 = ln->GetX2() - 0.5;
  Double_t y2 = ln->GetY2() - 0.5;
  //
  //cout<<x1<<endl
  //  <<y1<<endl
  //  <<x2<<endl
  //  <<y2<<endl;
  //
  Double_t r = (Double_t)(xDim - 2*delta)/xDim/2.0;
  //cout<<r<<endl;
  //
  if( (x1*x1 + y1*y1)<r*r && (x2*x2 + y2*y2)<r*r)
    return true;
  return false;
}
  
void addSiPM(TLine *ln[nSiPM][4], Int_t sipmID, Double_t x0, Double_t y0){
  ln[sipmID][0] = new TLine();
  ln[sipmID][1] = new TLine();
  ln[sipmID][2] = new TLine();
  ln[sipmID][3] = new TLine();
  //
  ln[sipmID][0]->SetX1((x0*x_pixel_per_mm + dx_sipm_pixel/2.0)/xDim + 0.5);
  ln[sipmID][0]->SetY1((y0*y_pixel_per_mm - dy_sipm_pixel/2.0)/yDim + 0.5);
  ln[sipmID][0]->SetX2((x0*x_pixel_per_mm + dx_sipm_pixel/2.0)/xDim + 0.5);
  ln[sipmID][0]->SetY2((y0*y_pixel_per_mm + dy_sipm_pixel/2.0)/yDim + 0.5);
  ln[sipmID][0]->SetLineWidth(2.0);
  //
  ln[sipmID][1]->SetX1((x0*x_pixel_per_mm + dx_sipm_pixel/2.0)/xDim + 0.5);
  ln[sipmID][1]->SetY1((y0*y_pixel_per_mm + dy_sipm_pixel/2.0)/yDim + 0.5);
  ln[sipmID][1]->SetX2((x0*x_pixel_per_mm - dx_sipm_pixel/2.0)/xDim + 0.5);
  ln[sipmID][1]->SetY2((y0*y_pixel_per_mm + dy_sipm_pixel/2.0)/yDim + 0.5);
  ln[sipmID][1]->SetLineWidth(2.0);
  //
  ln[sipmID][2]->SetX1((x0*x_pixel_per_mm - dx_sipm_pixel/2.0)/xDim + 0.5);
  ln[sipmID][2]->SetY1((y0*y_pixel_per_mm + dy_sipm_pixel/2.0)/yDim + 0.5);
  ln[sipmID][2]->SetX2((x0*x_pixel_per_mm - dx_sipm_pixel/2.0)/xDim + 0.5);
  ln[sipmID][2]->SetY2((y0*y_pixel_per_mm - dy_sipm_pixel/2.0)/yDim + 0.5);
  ln[sipmID][2]->SetLineWidth(2.0);
  //
  ln[sipmID][3]->SetX1((x0*x_pixel_per_mm - dx_sipm_pixel/2.0)/xDim + 0.5);
  ln[sipmID][3]->SetY1((y0*y_pixel_per_mm - dy_sipm_pixel/2.0)/yDim + 0.5);
  ln[sipmID][3]->SetX2((x0*x_pixel_per_mm + dx_sipm_pixel/2.0)/xDim + 0.5);
  ln[sipmID][3]->SetY2((y0*y_pixel_per_mm - dy_sipm_pixel/2.0)/yDim + 0.5);
  ln[sipmID][3]->SetLineWidth(2.0);
}

void buildProjectionPlaneEdge(TLine *ln_pjs[n_pjs_enge]){
  //
  Double_t phi  = 0;
  Double_t phi0 = 0;
  Double_t r = r_pjs_pixel;
  //
  Double_t x = 0;
  Double_t y = 0;
  Double_t xold = r*TMath::Cos(phi0);
  Double_t yold = r*TMath::Sin(phi0);
  //
  for(Int_t i = 1; i <= n_pjs_enge; i++){
    phi = phi0 + (2.0*TMath::Pi() - phi0)/n_pjs_enge*i;
    x = r*TMath::Cos(phi);
    y = r*TMath::Sin(phi);
    ln_pjs[i-1] = new TLine();
    ln_pjs[i-1]->SetX1(xold/xDim + 0.5);
    ln_pjs[i-1]->SetY1(yold/yDim + 0.5);
    ln_pjs[i-1]->SetX2(x/xDim + 0.5);
    ln_pjs[i-1]->SetY2(y/yDim + 0.5);
    ln_pjs[i-1]->SetLineWidth(3.0);
    xold = x;
    yold = y;
  }
}

#ifdef PLOTS_SIPM_ARRAY
# ifndef __CINT__
int main(int argc, char *argv[]){
  plots_SiPM_array();
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef PLOTS_SIPM_ARRAY
