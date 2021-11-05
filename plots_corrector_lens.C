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

Double_t getAlpha_of_the_correction_surface(Double_t correctionAngle, Double_t n_reff);

Int_t plots_corrector_lens(){
  
  TString fileN;
  fileN = "./hist/hist_terzina_1.0e7.root";
  
  TFile *f1 = new TFile(fileN.Data());

  TH1D *h1_1 = (TH1D*)f1->Get("h1_PosX");
  TH1D *h1_2 = (TH1D*)f1->Get("h1_thetaPhotons_deg");
  TH2D *h2_3 = (TH2D*)f1->Get("h2_thetaPhotons_deg_vs_primPosX");
  TH1D *h1_4 = (TH1D*)f1->Get("h1_PosX_cut");
  TH2D *h2_5 = (TH2D*)f1->Get("h2_thetaPhotons_deg_vs_primPosX_cut");
  TProfile *pr_6 = (TProfile*)f1->Get("pr_thetaPhotons_deg_vs_primPosX_cut");

  //TH1D *h1_1 = (TH1D*)f1->Get("h1_Time");
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_PosX");
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_PosX_cut");

  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,1200,800);
  //TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,600,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  
  //h1_1->Rebin(4);
  //h1_1->SetTitle("");

  //
  //h1_1->SetLineColor(kBlack);
  //h1_1->SetLineWidth(3.0);
  //
  //h1_2->SetLineColor(kBlack);
  //h1_2->SetLineWidth(3.0);
  //
  //h1_3->SetLineColor(kBlack);
  //h1_3->SetLineWidth(3.0);
  //
  //h1_4->SetLineColor(kBlack);
  //h1_4->SetLineWidth(3.0);
  //
  //h1_5->SetLineColor(kBlack);
  //h1_5->SetLineWidth(3.0);
  //
  c1->Divide(3,2);
  c1->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_1->Draw();
  c1->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_2->Draw();
  c1->cd(3);
  gPad->SetGridx();
  gPad->SetGridy();
  h2_3->Draw("ZCOLOR");
  c1->cd(4);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_4->Draw();
  c1->cd(5);
  gPad->SetGridx();
  gPad->SetGridy();
  h2_5->Draw("ZCOLOR");
  c1->cd(6);
  gPad->SetGridx();
  gPad->SetGridy();
  //gPad->SetLogz();
  pr_6->Draw();
  //

  TCanvas *c2 = new TCanvas("c2",fileN.Data(),10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);

  pr_6->Draw();
  pr_6->SetLineWidth(3);
  pr_6->SetLineColor(kBlack);  
  pr_6->Fit("pol5","","",-278,278);
  TF1 *f_fit = (TF1*)pr_6->GetListOfFunctions()->FindObject("pol5");

  cout<<f_fit->Eval(0.0)<<endl
      <<f_fit->Eval(200.0)<<endl
      <<f_fit->Eval(-200.0)<<endl;

  Double_t xMin = -300;
  Double_t xMax =  300;
  const Int_t nPoints = 1000;

  Double_t x_lens[nPoints];
  Double_t x2_lens[nPoints];
  Double_t tan_alpha_lens_1[nPoints];
  Double_t tan_alpha_lens_2[nPoints];
  Double_t y_lens_1[nPoints];
  Double_t y_lens_2[nPoints];
  Double_t correctionAngle;

  Double_t n_reff_1 = 1.4;
  Double_t n_reff_2 = 1.6;
  
  for(Int_t ii = 0;ii<nPoints;ii++){
    x_lens[ii] = xMin + (xMax - xMin)/(nPoints - 1)*ii;
    correctionAngle = f_fit->Eval(x_lens[ii])/180.0*TMath::Pi();
    tan_alpha_lens_1[ii] = TMath::Tan(getAlpha_of_the_correction_surface(correctionAngle,n_reff_1));
    tan_alpha_lens_2[ii] = TMath::Tan(getAlpha_of_the_correction_surface(correctionAngle,n_reff_2));
  }

  TCanvas *c3 = new TCanvas("c3",fileN.Data(),10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);

  //
  TGraph *gr_1 = new TGraph(nPoints,x_lens,tan_alpha_lens_1);
  gr_1->Draw("APL same");
  gr_1->Fit("pol5","","",-300,300);
  TF1 *gr_fit_1 = (TF1*)gr_1->GetListOfFunctions()->FindObject("pol5");

  TCanvas *c4 = new TCanvas("c4",fileN.Data(),10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);

  
  //
  TGraph *gr_2 = new TGraph(nPoints,x_lens,tan_alpha_lens_2);
  gr_2->Draw("APL same");
  gr_2->Fit("pol5","","",-300,300);
  TF1 *gr_fit_2 = (TF1*)gr_2->GetListOfFunctions()->FindObject("pol5");

  
  for(Int_t ii = 0;ii<nPoints;ii++){
    x2_lens[ii] = xMin + (xMax - xMin)/(nPoints - 1)*ii;
    y_lens_1[ii] = gr_fit_1->Integral(xMin,x2_lens[ii]) + 20;
    y_lens_2[ii] = gr_fit_2->Integral(xMin,x2_lens[ii]) + 20;
  }

  TCanvas *c5 = new TCanvas("c5",fileN.Data(),10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  
  TGraph *gr_lens_1 = new TGraph(nPoints,x2_lens,y_lens_1);
  gr_lens_1->SetLineWidth(3.0);
  gr_lens_1->SetLineColor(kRed);
  gr_lens_1->SetMarkerColor(kRed);
  //gr_lens_1->Draw("APL same");
  //gr_lens_1->GetYaxis()->SetRangeUser(0,25.0);

  TGraph *gr_lens_2 = new TGraph(nPoints,x2_lens,y_lens_2);
  gr_lens_2->SetLineWidth(3.0);
  gr_lens_2->SetLineColor(kBlack);
  //gr_lens_2->Draw("APL same");
  //gr_lens_2->GetYaxis()->SetRangeUser(0,25.0);

  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_lens_1);
  mg->Add(gr_lens_2);

  mg->Draw("apl");
  
  mg->GetXaxis()->SetTitle("lens x, mm");
  mg->GetYaxis()->SetTitle("lens thickness, mm");

  mg->GetYaxis()->SetRangeUser(0,25.0);
  
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_lens_1, "n = 1.4", "l");
  leg->AddEntry(gr_lens_2, "n = 1.6", "l");
  leg->Draw();

  
  //*/
  
  /*

  Double_t x[1000];
  Double_t y[1000];
  Double_t yerr[1000];

  Double_t binCenter;
  Double_t binContent;
  Double_t binError;


  Int_t nn = 0;
  for(Int_t i = 1;i <= pr_6->GetNbinsX();i++){
    binCenter = pr_6->GetBinCenter(i);
    binContent = pr_6->GetBinContent(i);
    binError = pr_6->GetBinError(i);
    if(binError>0){
      x[nn] = binCenter;
      y[nn] = binContent;
      yerr[nn] = binError;
      nn++;
    }
  }

  cout<<nn<<endl;

  //TGraph *gr = new TGraph(nn,x,y);
  //gr->Draw("AP");
  */
  
  //h1_1->GetXaxis()->SetTitle("Time, ns");
  //h1_2->GetXaxis()->SetTitle("Photon path length, mm");
  //h1_3->GetXaxis()->SetTitle("x in projection plane, mm");
  //h1_4->GetXaxis()->SetTitle("Primary #theta, deg");
  //h1_5->GetXaxis()->SetTitle("Primary position x, mm");
  //h2_6->GetXaxis()->SetTitle("Primary position x, mm");
  //h2_6->GetYaxis()->SetTitle("Primary #theta, deg");
  //x in projection plane, mm
  //y in projection plane, mm
  //
  //h2_1->GetXaxis()->SetRangeUser(-0.13,-0.12);
  /*
  TString filePdfN = fileN;
  TString fileEpsN = fileN;
  TString filePngN = fileN;
  filePdfN += ".pdf";
  fileEpsN += ".eps";
  filePngN += ".png";

  c1->SaveAs(filePdfN.Data());
  c1->SaveAs(fileEpsN.Data());
  c1->SaveAs(filePngN.Data());
  */  
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

Double_t getAlpha_of_the_correction_surface(Double_t correctionAngle, Double_t n_reff){
  Double_t S = TMath::Sin(correctionAngle);
  Double_t A = n_reff - TMath::Cos(correctionAngle);
  return TMath::ASin(S/TMath::Sqrt(A*A + S*S));
}
