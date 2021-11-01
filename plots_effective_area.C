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


Int_t plots_effective_area() {

  Double_t R_entrance = 300.0;
  
  const Int_t n = 100;
  Double_t x[n];
  Double_t y[n];

  Double_t xMin =  0.0;
  Double_t xMax = 300.0;
  
  for(Int_t i = 0; i < n; i++){
    x[i] = xMin + (xMax - xMin)/(n-1)*i;
    y[i] = (R_entrance*R_entrance - x[i]*x[i])/(R_entrance*R_entrance);
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

  /*
  for(i = 0;i<nChannels;i++){
    h1_Arr[i]->SetLineColor(colorArr[i]);
    h1_Arr[i]->SetLineWidth(3.0);
    if(i == 0){
      h1_Arr[i]->Draw();
      h1_Arr[i]->GetXaxis()->SetTitle("Value, Unit");
      //h1_1->GetXaxis()->SetRangeUser(-0.13,-0.12);
    }
    else
      h1_Arr[i]->Draw("same");
  }
  
  //h1_1->Fit("gaus");
  TString legInfo;
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  for(i = 0;i<nChannels;i++){
    legInfo = "ch ";legInfo += i;
    leg->AddEntry(h1_Arr[i], legInfo.Data(), "l");
  }
  leg->Draw();
  */
  /*
  TMultiGraph *mg = new TMultiGraph();
  
  for(i = 0;i<nChannels;i++){
    gr_Arr[i]->SetLineColor(colorArr[i]);
    gr_Arr[i]->SetLineWidth(3.0);
    gr_Arr[i]->SetMarkerColor(colorArr[i]);
    gr_Arr[i]->SetMarkerStyle(markerArr[i]);
    mg->Add(gr_Arr[i]);
  }

  mg->Draw("apl");
  
  mg->GetXaxis()->SetTitle("ValueX, Unit");
  mg->GetYaxis()->SetTitle("ValueY, Unit");
  
  TString legInfo;
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  for(i = 0;i<nChannels;i++){
    legInfo = "ch ";legInfo += i;
    leg->AddEntry(gr_Arr[i], legInfo.Data(), "apl");
  }
  leg->Draw();
*/  

  return 0;
}

/*
TString getObjectName(TString namein, Int_t i){
  TString h1nameh = namein; h1nameh += "_"; h1nameh += "ch_"; h1nameh += i;
  return h1nameh;
}
*/
