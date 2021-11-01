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

Double_t projection_sphere_segment_area(Double_t R, Double_t theta);

Int_t plots_projection_sphere_segment_area() {

  Double_t R_sphere = 208.0;         //mm
  Double_t theta_opening = 16.7;     //deg
  Double_t theta_opening_min = 0.0;  //deg
  Double_t theta_opening_max = 20.0; //deg
  
  const Int_t n = 100;
  Double_t x1[n];
  Double_t y1[n];
  Double_t x2[n];
  Double_t y2[n];
  Double_t x3[n];
  Double_t y3[n];

  Double_t xMin =  0.0;
  Double_t xMax = 300.0;
  
  for(Int_t i = 0; i < n; i++){
    //
    x1[i] = theta_opening_min + (theta_opening_max - theta_opening_min)/(n-1)*i;
    y1[i] = projection_sphere_segment_area(200,x1[i]);
    //
    x2[i] = theta_opening_min + (theta_opening_max - theta_opening_min)/(n-1)*i;
    y2[i] = projection_sphere_segment_area(R_sphere,x2[i]);
    //
    x3[i] = theta_opening_min + (theta_opening_max - theta_opening_min)/(n-1)*i;
    y3[i] = projection_sphere_segment_area(220,x3[i]);
  }
  
  TCanvas *c1 = new TCanvas("c1","c1",10,10,600,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);

  TGraph* gr1 = new TGraph(n,x1,y1);
  gr1->SetName("gr1");
  gr1->SetTitle(" ");
  TGraph* gr2 = new TGraph(n,x2,y2);
  gr2->SetName("gr2");
  gr2->SetTitle(" ");
  TGraph* gr3 = new TGraph(n,x3,y3);
  gr3->SetName("gr3");
  gr3->SetTitle(" ");

  gr1->SetLineColor(kBlue);
  gr1->SetMarkerColor(kBlue);
  gr1->SetLineWidth(3.0);
  gr2->SetLineColor(kBlack);
  gr2->SetMarkerColor(kBlack);
  gr2->SetLineWidth(3.0);
  gr3->SetLineColor(kRed);
  gr3->SetMarkerColor(kRed);
  gr3->SetLineWidth(3.0);

  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr1);
  mg->Add(gr2);
  mg->Add(gr3);
  mg->Draw("apl");
  
  mg->GetXaxis()->SetTitle("Opening angle, deg");
  mg->GetYaxis()->SetTitle("Sphere segment area, mm^{2}");
  
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr1, "R = 200 mm", "apl");
  leg->AddEntry(gr2, "R = 208 mm", "apl");
  leg->AddEntry(gr3, "R = 220 mm", "apl");
  leg->Draw();
  
  
  //gr1->Draw("APL");
  //gr1->GetXaxis()->SetTitle("Opening angle, deg");
  //gr1->GetYaxis()->SetTitle("Sphere segment area, mm^2");

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

Double_t projection_sphere_segment_area(Double_t R, Double_t theta){
  return 2*TMath::Pi()*R*R*(1.0-TMath::Cos(theta/180.0*TMath::Pi()));
}
