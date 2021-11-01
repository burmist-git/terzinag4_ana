//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "TString.h"
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "TStyle.h"
#include "TROOT.h"


#include <time.h>

using namespace std;

Int_t plots_mirror_small(TString fileN = "./hist/hist_lhcBrich_mirror_small_z0m0.root", TString dz_str = "0"){

  cout<<"fileN  = "<<fileN<<endl
      <<"dz_str = "<<dz_str<<endl;
  
  TString objectName;

  TFile *f1 = new TFile(fileN.Data());

  TH1D *h1_1 = (TH1D*)f1->Get("h1_PosX");

  //h1_1->Rebin(4);
  //h1_1->SetTitle("");

  //TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,800,800);
  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,600,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
 
  h1_1->SetTitle(dz_str.Data());
  h1_1->SetLineColor(kBlack);
  h1_1->SetLineWidth(3.0);
  h1_1->Draw();

  TString nameOut = "small_mirror_calib_";
  nameOut += dz_str;
  nameOut += ".gif";
  
  c1->SaveAs(nameOut.Data());
  
  /*
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
