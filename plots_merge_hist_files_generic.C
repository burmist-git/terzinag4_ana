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

Int_t plots_merge_hist_files_generic(){
  const Int_t n = 8;
  TString fileNarr[n];
  fileNarr[0]="./merg_hist/hist_merg_hist_10PeV.root";
  fileNarr[1]="./merg_hist/hist_merg_hist_35PeV.root";
  fileNarr[2]="./merg_hist/hist_merg_hist_70PeV.root";
  fileNarr[3]="./merg_hist/hist_merg_hist_100PeV.root";
  fileNarr[4]="./merg_hist/hist_merg_hist_350PeV.root";
  fileNarr[5]="./merg_hist/hist_merg_hist_700PeV.root";
  fileNarr[6]="./merg_hist/hist_merg_hist_1000PeV.root";
  fileNarr[7]="./merg_hist/hist_merg_hist_3000PeV.root";
  //  
  //
  TFile *f1[n];
  TH1D *h1[n];
  for(Int_t i = 0;i<8;i++){
   f1[i] = new TFile(fileNarr[i].Data());
   h1[i] = (TH1D*)f1[i]->Get("h1_npe_mean");
   h1[i]->Rebin(4);
   h1[i]->SetLineWidth(2);
  }
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  //
  c1->SetRightMargin(0.01);
  c1->SetLeftMargin(0.08);
  c1->SetTopMargin(0.01);
  c1->SetBottomMargin(0.08);
  //
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  //
  h1[0]->SetLineColor(kBlack);
  h1[1]->SetLineColor(kRed);
  h1[2]->SetLineColor(kBlue);
  h1[3]->SetLineColor(kMagenta);
  h1[4]->SetLineColor(kGreen+2);
  h1[5]->SetLineColor(kRed+2);
  h1[6]->SetLineColor(kBlue+2);
  h1[7]->SetLineColor(kMagenta+2);
  //
  h1[0]->SetMinimum(0.1);
  h1[0]->SetTitle("");
  h1[0]->Draw();
  for(Int_t i = 0;i<8;i++)
    h1[i]->Draw("same");

  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(h1[0], "10   PeV", "pl");
  leg->AddEntry(h1[1], "35   PeV", "pl");
  leg->AddEntry(h1[2], "70   PeV", "pl");
  leg->AddEntry(h1[3], "100  PeV", "pl");
  leg->AddEntry(h1[4], "350  PeV", "pl");
  leg->AddEntry(h1[5], "700  PeV", "pl");
  leg->AddEntry(h1[6], "1000 PeV", "pl");
  leg->AddEntry(h1[7], "3000 PeV", "pl");
  leg->Draw();

  
  return 0;
}
