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

Double_t getEkin(Double_t p, Double_t m);

Int_t plots_Ekin_mom() {
  
  const Int_t n = 10000;
  Double_t p[n];
  Double_t p_val;
  Double_t Ekin_e[n];
  Double_t Ekin_p[n];

  Double_t pMin =   0.1; //MeV
  Double_t pMax = 50000; //MeV

  Double_t me = 0.51099895000; //MeV/c/c
  Double_t mp = 938.272088160; //MeV/c/c

  for(Int_t i = 0; i < n; i++){
    p_val = pMin + (pMax - pMin)/(n-1)*i;
    p[i] = p_val/1000;
    Ekin_e[i] = getEkin(p_val,me)/p_val;
    Ekin_p[i] = getEkin(p_val,mp)/p_val;
  }
  
  TCanvas *c1 = new TCanvas("c1","c1",10,10,600,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);

  TGraph* gr_e = new TGraph(n,p,Ekin_e);
  TGraph* gr_p = new TGraph(n,p,Ekin_p);
  
  gr_e->SetName("");
  gr_e->SetTitle("");
  gr_e->SetLineColor(kBlack);
  gr_e->SetLineWidth(3.0);
  gr_p->SetName("");
  gr_p->SetTitle("");
  gr_p->SetLineColor(kRed);
  gr_p->SetLineWidth(3.0);

  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_e);
  mg->Add(gr_p);  
  
  mg->Draw("AL");
  
  mg->GetXaxis()->SetTitle("Momentum, GeV/c");
  mg->GetYaxis()->SetTitle("Ekin/Momentum, c");

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

Double_t getEkin(Double_t p, Double_t m){
  return TMath::Sqrt(p*p+m*m) - m;
}
