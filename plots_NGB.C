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

Int_t plots_NGB(){

  TString fileN;
  fileN = "../hist_root_NGB/hist_NGB_0.189deg_00100.root";
  //fileN = "../hist_root_NGB/hist_NGB_00000.root";
  //fileN = "../hist_root_NGB/hist_NGB_10deg_00000.root";
  
  TFile *f1 = new TFile(fileN.Data());
  TH2D *h2_1 = (TH2D*)f1->Get("h2_PosY_vs_PosX");
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_photPathLen");
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_Time");
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_PosX");
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_PosX_cut");
  TH1D *h1_1 = (TH1D*)f1->Get("h1_nPhot");
  TH1D *h1_2 = (TH1D*)f1->Get("h1_npe");
  
  //h1_1->Rebin(4);
  
  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,800,800);
  //TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,600,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //
  c1->SetRightMargin(0.03);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.01);
  c1->SetBottomMargin(0.08);
  //
  gPad->SetGridy();
  gPad->SetGridx();
  //gStyle->SetOptStat(kFALSE);
  //
  h1_1->SetTitle("");
  h1_1->SetLineColor(kBlack);
  h1_1->SetLineWidth(3.0);
  h1_2->SetTitle("");
  h1_2->SetLineColor(kBlack);
  h1_2->SetLineWidth(3.0);
  //h1_1->SetLineColor(kBlack);
  //h1_1->SetLineWidth(3.0);
  h2_1->SetTitle("");
  h2_1->SetMinimum(10);
  //h2_1->Draw("ZCOLOR");
  //h1_1->Draw();
  h1_2->Draw();
  //
  h2_1->GetXaxis()->SetRangeUser(-70,70);
  h2_1->GetYaxis()->SetRangeUser(-70,70);
  h2_1->GetXaxis()->SetTitle("PosX, mm");
  h2_1->GetYaxis()->SetTitle("PosY, mm");
  
  //h1_1->GetXaxis()->SetRangeUser(0,100);
  h1_2->GetXaxis()->SetRangeUser(0,20);
  //h1_1->GetYaxis()->SetRangeUser(-70,70);
  h1_1->GetXaxis()->SetTitle("Number of photons in SiPM camera in 1000 ns");
  h1_2->GetXaxis()->SetTitle("Number of p.e. in SiPM camera in 1000 ns");
  //h1_1->GetYaxis()->SetTitle("PosY, mm");

  return 0;
}
