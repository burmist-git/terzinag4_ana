//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>

#include <time.h>

using namespace std;


Int_t plots_PSF(){
  TString fileName;
  //fileName = "./hist_GeomID11/hist_terzina_PSF_with_corrector_0.0deg.root";
  fileName = "./hist_GeomID11/hist_terzina_PSF_with_corrector_3.5deg.root";
  TFile *f1 = new TFile(fileName.Data());
  //
  TH2D *h2_1 = (TH2D*)f1->Get("h2_primPosY_vs_primPosX");
  TH1D *h1_2 = (TH1D*)f1->Get("h1_thetaPhotons_deg");
  TH1D *h1_3 = (TH1D*)f1->Get("h1_phiPhotons_deg");
  TH1D *h1_4 = (TH1D*)f1->Get("h1_Time");
  //    
  TH1D *h1_5 = (TH1D*)f1->Get("h1_Wavelength");
  TH1D *h1_6 = (TH1D*)f1->Get("h1_PosX");
  TH1D *h1_7 = (TH1D*)f1->Get("h1_PosY");
  TH2D *h2_8 = (TH2D*)f1->Get("h2_PosY_vs_PosX");
  //
  TH2D *h2_9 = (TH2D*)f1->Get("h2_PosX_vs_primPosX");
  TProfile *pr_10 = (TProfile*)f1->Get("pr_PosX_vs_primPosX");
  //
  TCanvas *c1 = new TCanvas("c1",fileName.Data(),10,10,1600,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  //
  c1->Divide(4,2);
  c1->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  h2_1->Draw("ZCOLOR");
  c1->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_2->Draw();
  c1->cd(3);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_3->Draw();
  c1->cd(4);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  h1_4->Draw();
  c1->cd(5);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_5->Draw();
  //h1_5->GetXaxis()->SetRangeUser(x_PosX_RangeMin,x_PosX_RangeMax);
  c1->cd(6);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_6->Draw();
  //h1_6->GetXaxis()->SetRangeUser(x_PosY_RangeMin,x_PosY_RangeMax);
  c1->cd(7);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogz();
  h1_7->Draw();
  //
  c1->cd(8);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogz();
  h2_8->Draw("ZCOLOR");
  //h2_8->GetXaxis()->SetRangeUser(x_PosX_RangeMin,x_PosX_RangeMax);
  //h2_8->GetYaxis()->SetRangeUser(x_PosY_RangeMin,x_PosY_RangeMax);
  //
  /*
  h2_1->GetXaxis()->SetTitle("Primary position x, mm");
  h2_1->GetYaxis()->SetTitle("Primary position y, mm");
  h1_2->GetXaxis()->SetTitle("Primary #theta, deg");
  h1_3->GetXaxis()->SetTitle("Primary #phi, deg");
  h1_41->GetXaxis()->SetTitle("Time, ns");
  h1_42->GetXaxis()->SetTitle("Time, ns");
  h1_5->GetXaxis()->SetTitle("x in projection plane, mm");
  h1_6->GetXaxis()->SetTitle("y in projection plane, mm");
  h2_7->GetXaxis()->SetTitle("x in projection plane, mm");
  h2_7->GetYaxis()->SetTitle("y in projection plane, mm");
  h2_8->GetXaxis()->SetTitle("x in projection plane, mm");
  h2_8->GetYaxis()->SetTitle("y in projection plane, mm");
  //
  //h2_1->GetXaxis()->SetRangeUser(-0.13,-0.12);
  */
  //
  //
  TCanvas *c2 = new TCanvas("c2",fileName.Data(),10,10,1200,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  c2->Divide(2,1);
  c2->cd(1);
  h2_9->Draw("ZCOLOR");
  c2->cd(2);
  pr_10->Draw();
  
  return 0;
}
