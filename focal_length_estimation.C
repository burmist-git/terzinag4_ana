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

Double_t focus_positive_lens(Double_t R, Double_t n, Double_t d);
Double_t focus_negative_lens(Double_t R, Double_t n, Double_t d);
bool get_lens_shape(TGraph *gr_lens_shape, Double_t lens_R, Double_t lens_d);

Int_t focal_length_estimation(){
  //
  ////////////////////////////////////////////////
  Double_t lens_n1 = 1.47;  
  Double_t lens_d1 = 0.0;  
  const Int_t n = 1000;
  Double_t RoC;
  Double_t RoC_min = 1.0;    //cm
  Double_t RoC_max = 300.0;  //cm
  Double_t RoC_positive_n1[n];
  Double_t RoC_negative_n1[n];
  Double_t f_pos_n1[n];
  Double_t f_neg_n1[n];
  //
  Double_t xMin = -50;
  Double_t xMax = 150;
  //
  Double_t yMin =-100;
  Double_t yMax = 100;
  //
  ///////////////////////////////////////////////

  //for(Int_t i = 0;i<n;i++){
  //RoC = RoC_min + (RoC_max - RoC_min)/(n-1)*i;
  //RoC_positive_n1[i] = RoC;
  //RoC_negative_n1[i] = RoC;
  //f_pos_n1[i] = focus_positive_lens(RoC, lens_n1, lens_d1);
  //f_neg_n1[i] = focus_negative_lens(RoC, lens_n1, lens_d1);
  //}
  //TGraph *gr_f_pos_n1 = new TGraph( n, RoC_positive_n1, f_pos_n1);
  TGraph *gr_lens_shape = new TGraph();
  TGraph *gr_support = new TGraph();
  Double_t lens_R = 30.0;
  Double_t lens_d = 4.0;
  get_lens_shape(gr_lens_shape, lens_R, lens_d);
  //
  cout<<"f = "<<focus_positive_lens(lens_R, lens_n1, lens_d)<<endl;
  gr_support->SetPoint(gr_support->GetN(),focus_positive_lens(lens_R, lens_n1, lens_d),0.0);
  gr_support->SetMarkerStyle(20);
  gr_support->SetLineColor(kBlack);
  //  
  TCanvas *c1 = new TCanvas("c1","c1",10,10,800,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  //gr_f_pos_n1->SetMarkerStyle(20);
  //gr_f_pos_n1->SetLineColor(kBlack);
  //gr_f_pos_n1->SetLineWidth(2.0);
  //gr_f_pos_n1->Draw("APL");
  //gr_lens_shape->GetXaxis()->SetLimits(-100,100);
  //gr_lens_shape->Draw("APL");
  //gr_lens_shape->GetYaxis()->SetRangeUser(-100,100);  
  //
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_lens_shape);
  mg->Add(gr_support);
  mg->GetXaxis()->SetLimits(xMin,xMax);
  mg->Draw("AP");
  mg->GetYaxis()->SetRangeUser(yMin,yMax);  

  
  return 0;
}

Double_t focus_positive_lens(Double_t R, Double_t n, Double_t d){
  Double_t one_over_f = (n-1.0)*(2.0/R - (n-1)*d/n/R/R);
  if(one_over_f == 0)
    return -999.0;
  return 1.0/one_over_f;
}

Double_t focus_negative_lens(Double_t R, Double_t n, Double_t d){
  Double_t one_over_f = (n-1.0)*(2.0/R + (n-1)*d/n/R/R);
  if(one_over_f == 0)
    return -999.0;
  return 1.0/one_over_f;
}

bool get_lens_shape(TGraph *gr, Double_t R, Double_t d){
  Double_t l = R - d/2.0;
  if(l>=R)
    return false;
  Double_t cosAlpha = l/R;
  Double_t alpha = TMath::ACos(cosAlpha);
  Double_t alphaDeg = alpha*180.0/TMath::Pi();
  if(d>=R)
    return false;
  Double_t lens_D_over_2 = d*TMath::Sqrt(R/d - 1.0);
  const Int_t n = 1000;
  Double_t phi;
  Double_t phi_min = -alpha+TMath::Pi();
  Double_t phi_max = TMath::Pi();
  for(Int_t i = 0;i<n;i++){
    TVector2 v;
    phi = phi_min + (phi_max - phi_min)/(n-1)*i;
    v.SetMagPhi(R,phi);
    gr->SetPoint(gr->GetN(),v.X()+l,v.Y());
  }
  phi_min = TMath::Pi();
  phi_max = TMath::Pi() + alpha;
  for(Int_t i = 0;i<n;i++){
    TVector2 v;
    phi = phi_min + (phi_max - phi_min)/(n-1)*i;
    v.SetMagPhi(R,phi);
    gr->SetPoint(gr->GetN(),v.X()+l,v.Y());
  }
  phi_min = alpha;
  phi_max = 0;
  for(Int_t i = 0;i<n;i++){
    TVector2 v;
    phi = phi_min + (phi_max - phi_min)/(n-1)*i;
    v.SetMagPhi(R,phi);
    gr->SetPoint(gr->GetN(),v.X()-l,v.Y());
  }
  phi_min = 0;
  phi_max = -alpha;
  for(Int_t i = 0;i<n;i++){
    TVector2 v;
    phi = phi_min + (phi_max - phi_min)/(n-1)*i;
    v.SetMagPhi(R,phi);
    gr->SetPoint(gr->GetN(),v.X()-l,v.Y());
  }
  return true;  
}
