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

Int_t tvector2(){
  
  Double_t xMin = -5.0;
  Double_t xMax =  5.0;
  Double_t yMin = -5.0;
  Double_t yMax =  5.0;

  Double_t dleta_fit = 0.1;
  Double_t xFit_0 = -1.5;
  Double_t xFit_2 = 3.3;
  Double_t yFit_0;
  Double_t yFit_2;
  
  //1
  Double_t R1 = 2.0;
  Double_t x0_1 = 0.0;
  Double_t y0_1 = 0.0;
  TVector2 center1(x0_1,y0_1);
  Double_t phi1_start = 150.0/180.0*TMath::Pi();
  Double_t phi1_stop  =  90.0/180.0*TMath::Pi();
  const Int_t nn1 = 1000;

  //2
  Double_t R2 = 4.0;
  Double_t x0_2 = 0.0;
  Double_t y0_2 = -2.0;
  TVector2 center2(x0_2,y0_2);
  Double_t phi2_start = 90.0/180.0*TMath::Pi();
  Double_t phi2_stop  = 30.0/180.0*TMath::Pi();
  const Int_t nn2 = 1000;

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

  v1.SetMagPhi(R2,phi2_start);  
  for(Int_t i = 0;i<nn2;i++){
    phi = (phi2_stop - phi2_start)/(nn2 - 1)*i;
    TVector2 v2 = (v1.Rotate(phi) + center2);
    x[i+nn1] = v2.X();
    y[i+nn1] = v2.Y();
  }

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
  gr->Fit("pol5","","",xFit_0-dleta_fit,xFit_2+dleta_fit);
  TF1 *f_fit = (TF1*)gr->GetListOfFunctions()->FindObject("pol5");
  // http://kaj.uniwersytetradom.pl/docs/Biarcs.pdf
  yFit_0=f_fit->Eval(xFit_0);
  yFit_2=f_fit->Eval(xFit_2);

  Double_t yFitDer_0 = f_fit->Derivative(xFit_0,0,0.0000001);
  Double_t yFitDer_2 = f_fit->Derivative(xFit_2,0,0.0000001);
  
  Double_t xC = xFit_2 + (yFitDer_0*(xFit_2-xFit_0) + yFit_2 - yFit_0)/(yFitDer_2-yFitDer_0);
  Double_t yC = yFit_2 - yFitDer_2*(xFit_2 - xC);

  //Double_t xC = (yFitDer_2*xFit_2 - yFit_2 - yFitDer_0*xFit_0 + yFit_0)/(yFitDer_2-yFitDer_0);
  //Double_t yC = yFitDer_0*(xC - xFit_0) + yFit_0;


  //Double_t xC = (yFit_2 - yFit_0 + yFitDer_0*xFit_0 + yFitDer_2*xFit_2)/(yFitDer_0-yFitDer_2);
  //Double_t yC = yFit_2 + yFitDer_2*(xC-xFit_2);
  
  TGraph *gr_Biarc_spline = new TGraph();
  gr_Biarc_spline->SetPoint(0,0,0);
  gr_Biarc_spline->SetPoint(1,xFit_0,yFit_0);
  gr_Biarc_spline->SetPoint(2,xFit_2,yFit_2);
  gr_Biarc_spline->SetPoint(3,xC,yC);

  cout<<xC<<endl
      <<yC<<endl;
  gr_Biarc_spline->SetMarkerStyle(20);  
  gr_Biarc_spline->SetMarkerColor(kMagenta);  
  //TGraph *gr = new TGraph((nn1+nn2),x,y);

  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr);
  mg->Add(gr_Biarc_spline);
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
