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

Int_t plots_single(){

  TString fileN;
  //fileN = "./hist/hist_terzina_1.0e7.root";
  //fileN = "./hist/hist_terzina.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00.root";

  //fileN = "./hist/hist_terzina_PSF_v01.00.00_0theta_0phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_1theta_0phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_2theta_0phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_3theta_0phi.root";

  //fileN = "./hist/hist_terzina_PSF_v01.00.00_3theta_20phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_3theta_45phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_3theta_90phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_3theta_135phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_3theta_180phi.root";

  //fileN = "./hist_fresnel/hist_terzina.root";
  //fileN = "./hist_fresnel/hist_terzina.root";
  fileN = "./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_0.0deg.root";
  //fileN = "./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_1.0deg.root";
  //fileN = "./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_2.0deg.root";
  //fileN = "./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_3.0deg.root";
  //fileN = "./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_4.0deg.root";
  
  TFile *f1 = new TFile(fileN.Data());

  //TH2D *h1_1 = (TH2D*)f1->Get("h2_PosX_vs_primPosX");
  TH2D *h2_1 = (TH2D*)f1->Get("h2_PosY_vs_PosX");

  //TH1D *h1_1 = (TH1D*)f1->Get("h1_photPathLen");

  //TH1D *h1_1 = (TH1D*)f1->Get("h1_Time");
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_PosX");
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_PosX_cut");
  
  //h1_1->Rebin(4);
  //h1_1->SetTitle("");
  
  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,800,800);
  //TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,600,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //
  gPad->SetGridy();
  gPad->SetGridx();
  gStyle->SetOptStat(kFALSE);
  //
  //h1_1->SetLineColor(kBlack);
  //h1_1->SetLineWidth(3.0);
  //h1_1->SetLineColor(kBlack);
  //h1_1->SetLineWidth(3.0);
  h2_1->SetTitle("");
  h2_1->Draw("ZCOLOR");
  //h1_1->Draw();
  h2_1->GetXaxis()->SetRangeUser(-60,60);
  h2_1->GetYaxis()->SetRangeUser(-60,60);
  h2_1->GetXaxis()->SetTitle("PosX, mm");
  h2_1->GetYaxis()->SetTitle("PosY, mm");
  
  //h1_1->GetXaxis()->SetTitle("primPosX, mm");
  //h1_1->GetXaxis()->SetTitle("PosX, mm");
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


  return 0;
}
