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

Int_t plots(){

  TString fileN;
  //fileN = "./hist/hist_terzina_1.0e7.root";
  //fileN = "./hist/hist_terzina.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00.root";

  //fileN = "./hist/hist_terzina_PSF_v01.00.00_0theta_0phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_1theta_0phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_2theta_0phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_3theta_0phi.root";

  fileN = "./hist/hist_terzina_PSF_v01.00.00_3theta_20phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_3theta_45phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_3theta_90phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_3theta_135phi.root";
  //fileN = "./hist/hist_terzina_PSF_v01.00.00_3theta_180phi.root";
  
  TFile *f1 = new TFile(fileN.Data());

  TH2D *h2_1 = (TH2D*)f1->Get("h2_primPosY_vs_primPosX");
  TH1D *h1_2 = (TH1D*)f1->Get("h1_thetaPhotons_deg");
  TH1D *h1_3 = (TH1D*)f1->Get("h1_phiPhotons_deg");
  TH1D *h1_4 = (TH1D*)f1->Get("h1_PosX");
  TH1D *h1_5 = (TH1D*)f1->Get("h1_PosY");
  TH2D *h2_6 = (TH2D*)f1->Get("h2_PosY_vs_PosX");
    
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_Time");
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_PosX");
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_PosX_cut");
  
  //h1_1->Rebin(4);
  //h1_1->SetTitle("");

  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,1200,800);
  //TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,600,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  //
  //h1_1->SetLineColor(kBlack);
  //h1_1->SetLineWidth(3.0);
  h1_2->SetLineColor(kBlack);
  h1_2->SetLineWidth(3.0);
  //
  h1_3->SetLineColor(kBlack);
  h1_3->SetLineWidth(3.0);
  //
  h1_4->SetLineColor(kBlack);
  h1_4->SetLineWidth(3.0);
  //
  h1_5->SetLineColor(kBlack);
  h1_5->SetLineWidth(3.0);
  //
  c1->Divide(3,2);
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
  h1_4->Draw();
  c1->cd(5);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_5->Draw();
  c1->cd(6);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogz();
  h2_6->Draw("ZCOLOR");
  //
  h2_1->GetXaxis()->SetTitle("Primary position x, mm");
  h2_1->GetYaxis()->SetTitle("Primary position y, mm");
  h1_2->GetXaxis()->SetTitle("Primary #theta, deg");
  h1_3->GetXaxis()->SetTitle("Primary #phi, deg");
  h1_4->GetXaxis()->SetTitle("x in projection plane, mm");
  h1_5->GetXaxis()->SetTitle("y in projection plane, mm");
  h2_6->GetXaxis()->SetTitle("x in projection plane, mm");
  h2_6->GetYaxis()->SetTitle("y in projection plane, mm");
  //
  //h2_1->GetXaxis()->SetRangeUser(-0.13,-0.12);

  TString filePdfN = fileN;
  TString fileEpsN = fileN;
  TString filePngN = fileN;
  filePdfN += ".pdf";
  fileEpsN += ".eps";
  filePngN += ".png";

  c1->SaveAs(filePdfN.Data());
  c1->SaveAs(fileEpsN.Data());
  c1->SaveAs(filePngN.Data());
  
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
