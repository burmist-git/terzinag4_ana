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

Int_t tvector2_circle(){
  
  Double_t xMin = -5.0;
  Double_t xMax =  5.0;
  Double_t yMin = -5.0;
  Double_t yMax =  5.0;

  Double_t x0 = 0.0;
  Double_t y0 = 0.0;

  Double_t xL = -1.5;
  Double_t yL;
  Double_t xR = 1.0;
  Double_t yR;
  Double_t dleta_fit = 0.1;
  
  //1
  Double_t R1 = 2.0;
  TVector2 center1(x0,y0);
  Double_t phi1_start = 145.0/180.0*TMath::Pi();
  Double_t phi1_stop  =  35.0/180.0*TMath::Pi();
  //Double_t phi1_start = 180.0/180.0*TMath::Pi();
  //Double_t phi1_stop  =   0.0/180.0*TMath::Pi();
  const Int_t nn1 = 1000;

  /*
  //2
  Double_t R2 = 4.0;
  Double_t x0_2 = 0.0;
  Double_t y0_2 = -2.0;
  TVector2 center2(x0_2,y0_2);
  Double_t phi2_start = 90.0/180.0*TMath::Pi();
  Double_t phi2_stop  = 30.0/180.0*TMath::Pi();
  */
  const Int_t nn2 = 0;
  
  TVector2 v1;
  Double_t phi;
  Double_t x[nn1+nn2];
  Double_t y[nn1+nn2];

  v1.SetMagPhi(R1,phi1_start);  
  for(Int_t i = 0;i<nn1;i++){
    phi = (phi1_stop - phi1_start)/(nn1 - 1)*i;
    TVector2 v2 = (v1.Rotate(phi) + center1);
    x[i] = v2.X();
    y[i] = v2.Y();
  }

  /*
  v1.SetMagPhi(R2,phi2_start);  
  for(Int_t i = 0;i<nn2;i++){
    phi = (phi2_stop - phi2_start)/(nn2 - 1)*i;
    TVector2 v2 = (v1.Rotate(phi) + center2);
    x[i+nn1] = v2.X();
    y[i+nn1] = v2.Y();
  }
  */
  
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1000,1000);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  gPad->SetGridx();
  gPad->SetGridy();
  
  TGraph *gr = new TGraph((nn1+nn2),x,y);
  gr->SetLineWidth(3.0);
  gr->Fit("pol8","","",xL-dleta_fit,xR+dleta_fit);
  TF1 *f_fit = (TF1*)gr->GetListOfFunctions()->FindObject("pol8");
  // http://kaj.uniwersytetradom.pl/docs/Biarcs.pdf
  yL=f_fit->Eval(xL);
  yR=f_fit->Eval(xR);

  Double_t yLDer = f_fit->Derivative(xL);
  Double_t yRDer = f_fit->Derivative(xR);  

  //Double_t xC = xR + (yLDer*(xR-xL) + yR - yL)/(yRDer-yLDer);
  //Double_t yC = yR - yRDer*(xR - xC);

  Double_t xC = (yRDer*xR - yR - yLDer*xL + yL)/(yRDer - yLDer);
  Double_t yC = yLDer*(xC - xL) + yL;
  
  TGraph *gr_Biarc_spline = new TGraph();
  gr_Biarc_spline->SetPoint(0,0,0);
  gr_Biarc_spline->SetPoint(1,xL,yL);
  gr_Biarc_spline->SetPoint(2,xR,yR);
  gr_Biarc_spline->SetPoint(3,xC,yC);
  //
  gr_Biarc_spline->SetMarkerStyle(20);  
  gr_Biarc_spline->SetMarkerColor(kMagenta);  

  // Tangent line L
  const Int_t nn_tl_L = 1000;  
  Double_t xMin_tl_L = -3.0;
  Double_t xMax_tl_L =  3.0; 
  //
  Double_t x_tl_L[nn_tl_L];
  Double_t y_tl_L[nn_tl_L]; 
  //
  for(Int_t i = 0;i<nn_tl_L;i++){
    x_tl_L[i] = xMin_tl_L + (xMax_tl_L - xMin_tl_L)/(nn_tl_L-1)*i;
    y_tl_L[i] = yLDer*(x_tl_L[i] - xL) + yL; 
  }
  TGraph *gr_tl_L = new TGraph(nn_tl_L,x_tl_L,y_tl_L);
  //
  // Tangent line R
  const Int_t nn_tl_R = 1000;  
  Double_t xMin_tl_R = -3.0;
  Double_t xMax_tl_R =  3.0; 
  //
  Double_t x_tl_R[nn_tl_R];
  Double_t y_tl_R[nn_tl_R]; 
  //
  for(Int_t i = 0;i<nn_tl_R;i++){
    x_tl_R[i] = xMin_tl_R + (xMax_tl_R - xMin_tl_R)/(nn_tl_R-1)*i;
    y_tl_R[i] = yRDer*(x_tl_R[i] - xR) + yR; 
  }
  TGraph *gr_tl_R = new TGraph(nn_tl_R,x_tl_R,y_tl_R);
  
  //
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr);
  mg->Add(gr_Biarc_spline);
  mg->Add(gr_tl_L);
  mg->Add(gr_tl_R);
  mg->GetXaxis()->SetLimits(xMin,xMax);
  mg->Draw("AP");
  mg->SetMinimum(yMin);
  mg->SetMaximum(yMax);

  /*
  TCanvas *c2 = new TCanvas("c2","c2",10,10,1000,1000);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  gPad->SetGridx();
  gPad->SetGridy();

  f_fit->Draw();

  f_fit
  */
  
  return 0;
}
