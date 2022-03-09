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

Int_t plots_sim_camera(){
  //
  TString fileN = "run_sim_camera_flt.root";
  TFile *f1 = new TFile(fileN.Data());
  TH1D *h1 = (TH1D*)f1->Get("h1_theta");
  //
  h1->SetMarkerColor(kBlack);
  h1->SetLineColor(kBlack);
  //
  h1->SetLineWidth(3);
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

  h1->GetXaxis()->SetTitle("Theta, deg");

  h1->Draw();
  
  //
  //TLegend *leg_po = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  //leg_po->AddEntry(gr_poemma_rms_radius, "POEMMA", "pl");
  //leg_po->AddEntry(gr_rms_radius,        "Terzina", "pl");
  //leg_po->Draw();
  //  
  return 0;
}
