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

Int_t plots_merge_hist(){
  //
  TString fileN;
  fileN="./merg_hist/hist_merg_hist_1000PeV.root";
  //fileN="./merg_hist/hist_merg_hist_350PeV.root";
  TFile *f1 = new TFile(fileN.Data());
  //TH2D *h2_1 = (TH2D*)f1->Get("h2_wf_tm_mean_vs_wf_am_mean");
  TH2D *h2_1 = (TH2D*)f1->Get("h2_wf_am_mean_vs_npe_mean");
  //
  TGraph *gr_npe_th = (TGraph*)f1->Get("gr_npe_th");
  TGraph *gr_wf_am_th = (TGraph*)f1->Get("gr_wf_am_th");
  //
  h2_1->SetTitle("");
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,800,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  //
  c1->SetRightMargin(0.13);
  c1->SetLeftMargin(0.13);
  c1->SetTopMargin(0.05);
  c1->SetBottomMargin(0.1);
  //
  gPad->SetGridx();
  gPad->SetGridy();
  //
  //h2_1->GetXaxis()->SetRangeUser(0,25);
  //h2_1->GetYaxis()->SetRangeUser(500,800);
  //h2_1->GetXaxis()->SetTitle("Mean maximum amplitude, single p.e.");
  //h2_1->GetYaxis()->SetTitle("Time, ns");
  //
  //h2_1->GetXaxis()->SetRangeUser(0,25);
  //h2_1->GetYaxis()->SetRangeUser(500,800);
  h2_1->GetXaxis()->SetTitle("Mean maximum amplitude, single p.e.");
  h2_1->GetYaxis()->SetTitle("Number of p.e., Maximum amplitude, single p.e.");
  //
  //gPad->SetLogy();
  //gPad->SetGridx();
  //gPad->SetGridy();
  //
  h2_1->Draw("ZCOLOR");
  //
  TCanvas *c2 = new TCanvas("c2","c2",20,20,1000,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  //
  c2->SetRightMargin(0.02);
  c2->SetLeftMargin(0.09);
  c2->SetTopMargin(0.05);
  c2->SetBottomMargin(0.08);
  //
  gPad->SetGridx();
  gPad->SetGridy();
  //
  gr_npe_th->SetLineColor(kBlack);
  gr_wf_am_th->SetLineColor(kRed);
  gr_npe_th->SetMarkerColor(kBlack);
  gr_wf_am_th->SetMarkerColor(kRed);
  gr_npe_th->SetLineWidth(2);
  gr_wf_am_th->SetLineWidth(2);
  //
  //
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_npe_th);
  mg->Add(gr_wf_am_th);
  //mg->GetXaxis()->SetLimits(xMin,xMax);
  mg->GetXaxis()->SetTitle("Threshold, singel p.e.");
  mg->GetYaxis()->SetTitle("Relative efficiency");
  mg->Draw("APL");
  mg->SetMinimum(1.0e-4);
  //mg->SetMaximum(yMax);
  //
  return 0;
}
