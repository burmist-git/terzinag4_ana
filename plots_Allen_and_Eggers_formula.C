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

Double_t allen_and_Eggers_formula(Double_t x);

Int_t plots_Allen_and_Eggers_formula() {
  
  const Int_t n = 1000;
  Double_t x[n];
  Double_t y[n];

  Double_t xMin =  100000.0;
  Double_t xMax = 1000000.0;
  
  for(Int_t i = 0; i < n; i++){
    x[i] = xMin + (xMax - xMin)/(n-1)*i;
    y[i] = allen_and_Eggers_formula(x[i]);
  }
  
  TCanvas *c1 = new TCanvas("c1","c1",10,10,600,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);

  TGraph* gr1 = new TGraph(n,x,y);
  gr1->SetName("gr1");
  gr1->SetTitle("Light collection efficiency vs. small mirror radius");

  gr1->SetLineColor(kBlack);
  gr1->SetLineWidth(3.0);

  gr1->Draw("APL");
  
  gr1->GetXaxis()->SetTitle("Small mirror radius, mm");
  gr1->GetYaxis()->SetTitle("Light collection efficiency");


  return 0;
}

Double_t allen_and_Eggers_formula(Double_t x){
  return 1735*TMath::Exp(-x/6700.0);
}
