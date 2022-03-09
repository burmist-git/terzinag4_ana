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

Int_t plots_two_sim_camera(){
  //
  TString fileN01 = "run_sim_camera_spr.root";
  TString fileN02 = "run_sim_camera_flt.root";
  TFile *f01 = new TFile(fileN01.Data());
  TFile *f02 = new TFile(fileN02.Data());
  //TH1D *h1_01 = (TH1D*)f01->Get("h1_nchannels");
  //TH1D *h1_02 = (TH1D*)f02->Get("h1_nchannels");
  TH1D *h1_01 = (TH1D*)f01->Get("h1_npe");
  TH1D *h1_02 = (TH1D*)f02->Get("h1_npe");
  //
  h1_01->SetMarkerColor(kBlack);
  h1_01->SetLineColor(kBlack);
  h1_01->SetLineWidth(3);
  //
  h1_02->SetMarkerColor(kRed);
  h1_02->SetLineColor(kRed);
  h1_02->SetLineWidth(3);
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,800,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  //gStyle->SetOptStat(kFALSE);
  //
  c1->SetRightMargin(0.01);
  c1->SetLeftMargin(0.08);
  c1->SetTopMargin(0.01);
  c1->SetBottomMargin(0.08);
  //
  gPad->SetGridx();
  gPad->SetGridy();

  //h1_01->GetXaxis()->SetTitle("Theta, deg");
  //h1_01->GetXaxis()->SetTitle("Number of channels");
  h1_01->GetXaxis()->SetTitle("Number of p.e.");

  h1_01->SetTitle("");
  h1_01->Draw();
  h1_02->Draw("same");

  //
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(h1_01, "Spherical", "pl");
  leg->AddEntry(h1_02, "Flat", "pl");
  leg->Draw();
  // 
  return 0;
}
