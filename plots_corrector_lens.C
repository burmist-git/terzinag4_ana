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
void curvatureCalculation(TF1 *f_lens, const Int_t nn, const Double_t xMin, const Double_t xMax, Double_t *x, Double_t *y, Double_t *r);
Double_t pol7_asymmetric(Double_t *x, Double_t *par);
Double_t pol8_symmetric(Double_t *x, Double_t *par);

Int_t plots_corrector_lens(){

  ////////////////////////////////////////////////
  
  TString fileN;
  TString outDataFitParFileIn;
  //fileN = "./hist/hist_terzina_1.0e7.root";
  //fileN = "./hist_v02.00.00b/hist_terzina_1e7.0.root";
  //fileN = "./hist_v02.00.00b/hist_terzina_1e7.0.root";
  //fileN = "./hist_small_pat/hist_terzina_corrector.root";
  fileN = "./hist_pat/hist_terzina_geomid_1_corrector.root";
  
  //outDataFitParFileIn = "./hist_v02.00.00b/lens_n_reff_1.47.dat";
  //outDataFitParFileIn = "./hist_small_pat/lens_n_reff_1.47.dat";
  outDataFitParFileIn = "./hist_pat/lens_n_reff_1.47.dat";

  Double_t lens_Thickness = 10.0;
  
  const Int_t nPoints = 1000;
  Double_t x_lens[nPoints];
  Double_t tan_alpha_lens_1[nPoints];
  Double_t y_lens_1[nPoints];
  Double_t correctionAngle;
  Double_t n_reff_1 = 1.47;
  
  Double_t xMin = -300 + 4;
  Double_t xMax =  300 - 4;
  //Double_t xMin = -197 + 1;
  //Double_t xMax =  197 - 1;
  //Double_t xMin = -252 + 1;
  //Double_t xMax =  252 - 1;

  ///////////////////////////////////////////////

  
  TFile *f1 = new TFile(fileN.Data());

  TH1D *h1_1 = (TH1D*)f1->Get("h1_PosX");
  TH1D *h1_2 = (TH1D*)f1->Get("h1_thetaPhotons_deg");
  TH2D *h2_3 = (TH2D*)f1->Get("h2_thetaPhotons_deg_vs_primPosX");
  TH1D *h1_4 = (TH1D*)f1->Get("h1_PosX_cut");
  TH1D *h2_5 = (TH1D*)f1->Get("h1_thetaPhotons_deg_cut");
  TH2D *h2_6 = (TH2D*)f1->Get("h2_thetaPhotons_deg_vs_primPosX_cut");

  TProfile *pr = (TProfile*)f1->Get("pr_thetaPhotons_vs_primPosX_cut");
  TProfile *pr_tmp = (TProfile*)pr->Clone("pr_tmp");
  pr_tmp->Fit("pol7","Q");
  TF1 *f_fit_tmp = (TF1*)pr_tmp->GetListOfFunctions()->FindObject("pol7");
  
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
  h2_5->Draw();
  c1->cd(6);
  gPad->SetGridx();
  gPad->SetGridy();
  h2_6->Draw("ZCOLOR");
  //
  //
  TCanvas *c2 = new TCanvas("c2",fileN.Data(),10,10,1600,900);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //
  c2->Divide(3,2);
  c2->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  //
  pr->SetMarkerStyle(20);
  pr->Draw();
  pr->SetLineWidth(3);
  pr->SetLineColor(kBlack);  
  //fit
  Int_t npar_pol7_asymmetric = 5;
  TF1 *f_pol7_asymmetric = new TF1("f_pol7_asymmetric", pol7_asymmetric, xMin, xMax, npar_pol7_asymmetric);
  f_pol7_asymmetric->SetParameter(0,f_fit_tmp->GetParameter(0));
  f_pol7_asymmetric->SetParameter(1,f_fit_tmp->GetParameter(1));
  f_pol7_asymmetric->SetParameter(2,f_fit_tmp->GetParameter(3));
  f_pol7_asymmetric->SetParameter(3,f_fit_tmp->GetParameter(5));
  f_pol7_asymmetric->SetParameter(4,f_fit_tmp->GetParameter(7));
  pr->Fit("f_pol7_asymmetric","Q","",xMin,xMax);
  pr->GetXaxis()->SetTitle("lens x, mm");
  pr->GetYaxis()->SetTitle("#theta_{corr}, rad");
  pr->SetTitle("Fit with odd polynomial of power 7");
  //
  //
  for(Int_t ii = 0;ii<nPoints;ii++){
    x_lens[ii] = xMin + (xMax - xMin)/(nPoints - 1)*ii;
    correctionAngle = f_pol7_asymmetric->Eval(x_lens[ii]);
    tan_alpha_lens_1[ii] = TMath::Tan(getAlpha_of_the_correction_surface(correctionAngle,n_reff_1));
  }
  //
  TGraph *gr_tan = new TGraph(nPoints,x_lens,tan_alpha_lens_1);
  TGraph *gr_tmp = new TGraph(nPoints,x_lens,tan_alpha_lens_1);
  gr_tmp->Fit("pol7","Q");
  TF1 *f_fit_tan_tmp = (TF1*)gr_tmp->GetListOfFunctions()->FindObject("pol7");
  //
  TF1 *f_pol7_asymmetric_tan = new TF1("f_pol7_asymmetric_tan", pol7_asymmetric, xMin, xMax, npar_pol7_asymmetric);
  f_pol7_asymmetric_tan->SetParameter(0,f_fit_tan_tmp->GetParameter(0));
  f_pol7_asymmetric_tan->SetParameter(1,f_fit_tan_tmp->GetParameter(1));
  f_pol7_asymmetric_tan->SetParameter(2,f_fit_tan_tmp->GetParameter(3));
  f_pol7_asymmetric_tan->SetParameter(3,f_fit_tan_tmp->GetParameter(5));
  f_pol7_asymmetric_tan->SetParameter(4,f_fit_tan_tmp->GetParameter(7));
  //
  gr_tan->Fit("f_pol7_asymmetric_tan","Q","",xMin,xMax);
  //
  c2->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  gr_tan->SetMarkerStyle(20);
  gr_tan->Draw("APL");
  gr_tan->SetTitle("Fit with odd polynomial of power 7");
  gr_tan->GetXaxis()->SetTitle("lens x, mm");
  gr_tan->GetYaxis()->SetTitle("tangent of the lens tangent line");
  //
  Double_t CC = lens_Thickness - f_pol7_asymmetric_tan->Integral(xMin,x_lens[0]);
  for(Int_t ii = 0;ii<nPoints;ii++){
    y_lens_1[ii] = f_pol7_asymmetric_tan->Integral(xMin,x_lens[ii]) + CC;
  }

  TGraph *gr_lens_1 = new TGraph(nPoints,x_lens,y_lens_1);
  TGraph *gr_lens_tmp = new TGraph(nPoints,x_lens,y_lens_1);
  gr_lens_tmp->Fit("pol8","Q");
  TF1 *f_fit_lens_tmp = (TF1*)gr_lens_tmp->GetListOfFunctions()->FindObject("pol8");
  Int_t npar_pol8_symmetric = 5;
  TF1 *f_pol8_symmetric_lens = new TF1("f_pol8_symmetric_lens", pol8_symmetric, xMin, xMax, npar_pol8_symmetric);
  f_pol8_symmetric_lens->SetParameter(0,f_fit_lens_tmp->GetParameter(0));
  f_pol8_symmetric_lens->SetParameter(1,f_fit_lens_tmp->GetParameter(2));
  f_pol8_symmetric_lens->SetParameter(2,f_fit_lens_tmp->GetParameter(4));
  f_pol8_symmetric_lens->SetParameter(3,f_fit_lens_tmp->GetParameter(6));
  f_pol8_symmetric_lens->SetParameter(4,f_fit_lens_tmp->GetParameter(8));
  //
  gr_lens_1->Fit("f_pol8_symmetric_lens","Q","",xMin,xMax);
  //
  c2->cd(3);
  gPad->SetGridx();
  gPad->SetGridy();
  gr_lens_1->SetMarkerStyle(20);
  gr_lens_1->SetMinimum(0);
  gr_lens_1->Draw("APL");
  gr_lens_1->SetTitle("Fit with even polynomial of power 8");
  gr_lens_1->GetXaxis()->SetTitle("lens x, mm");
  gr_lens_1->GetYaxis()->SetTitle("lens thickness, mm");
  //
  c2->cd(4);
  gPad->SetGridx();
  gPad->SetGridy();
  gr_lens_1->Draw("APL");  
  //
  //
  c2->cd(5);
  gPad->SetGridx();
  gPad->SetGridy();
  //
  Double_t x_lens_curv[nPoints];
  Double_t curvature_lens[nPoints];
  Double_t r_lens[nPoints];
  //  
  curvatureCalculation( f_pol8_symmetric_lens, nPoints, xMin, xMax, x_lens_curv, curvature_lens, r_lens);
  TGraph *gr_curvature = new TGraph( nPoints, x_lens_curv, curvature_lens);
  TGraph *gr_r = new TGraph(nPoints,x_lens_curv, r_lens);
  gr_curvature->SetMarkerStyle(20);
  gr_curvature->Draw("APL");
  gr_curvature->SetTitle("lens curvature");
  gr_curvature->GetXaxis()->SetTitle("lens x, mm");
  gr_curvature->GetYaxis()->SetTitle("lens curvature, 1/mm");
  //
  c2->cd(6);
  gPad->SetGridx();
  gPad->SetGridy();
  //
  gr_r->SetMarkerStyle(20);
  gr_r->Draw("APL");
  gr_r->SetTitle("1/curvature = radius");
  gr_r->GetXaxis()->SetTitle("lens x, mm");
  gr_r->GetYaxis()->SetTitle("lens radius, mm");  
  gr_r->SetMinimum(-40000.0);
  gr_r->SetMaximum( 40000.0);
  //
  //
  //Output information : write parameters in the file
  //
  FILE *fp01;
  fp01 = fopen(outDataFitParFileIn.Data(), "w+");
  fprintf(fp01, "%15.5f \n",xMin);
  fprintf(fp01, "%15.5f \n",xMax);
  for(Int_t ii = 0;ii<npar_pol8_symmetric;ii++)
    fprintf(fp01, "%70.60f \n",f_pol8_symmetric_lens->GetParameter(ii));
  fclose(fp01);
  //
  //
  //
  /*
  cout<<f_fit->Eval(0.0)<<endl
      <<f_fit->Eval(200.0)<<endl
      <<f_fit->Eval(-200.0)<<endl;
  Double_t xMin = -300;
  Double_t xMax =  300;
  const Int_t nPoints = 1000;
  //
  Double_t x_lens[nPoints];
  Double_t x2_lens[nPoints];
  Double_t tan_alpha_lens_1[nPoints];
  Double_t tan_alpha_lens_2[nPoints];
  Double_t tan_alpha_lens_3[nPoints];
  Double_t y_lens_1[nPoints];
  Double_t y_lens_2[nPoints];
  Double_t y_lens_3[nPoints];
  Double_t correctionAngle;

  Double_t n_reff_1 = 1.4;
  Double_t n_reff_2 = 1.5;
  Double_t n_reff_3 = 1.6;
  
  for(Int_t ii = 0;ii<nPoints;ii++){
    x_lens[ii] = xMin + (xMax - xMin)/(nPoints - 1)*ii;
    correctionAngle = f_fit->Eval(x_lens[ii])/180.0*TMath::Pi();
    tan_alpha_lens_1[ii] = TMath::Tan(getAlpha_of_the_correction_surface(correctionAngle,n_reff_1));
    tan_alpha_lens_2[ii] = TMath::Tan(getAlpha_of_the_correction_surface(correctionAngle,n_reff_2));
    tan_alpha_lens_3[ii] = TMath::Tan(getAlpha_of_the_correction_surface(correctionAngle,n_reff_3));
  }

  TCanvas *c3_1 = new TCanvas("c3_1",fileN.Data(),10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //
  TGraph *gr_1 = new TGraph(nPoints,x_lens,tan_alpha_lens_1);
  gr_1->Draw("APL same");
  gr_1->Fit("pol5","","",-300,300);
  TF1 *gr_fit_1 = (TF1*)gr_1->GetListOfFunctions()->FindObject("pol5");

  TCanvas *c3_2 = new TCanvas("c3_2",fileN.Data(),10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //
  TGraph *gr_2 = new TGraph(nPoints,x_lens,tan_alpha_lens_2);
  gr_2->Draw("APL same");
  gr_2->Fit("pol5","","",-300,300);
  TF1 *gr_fit_2 = (TF1*)gr_2->GetListOfFunctions()->FindObject("pol5");

  TCanvas *c3_3 = new TCanvas("c3_3",fileN.Data(),10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //
  TGraph *gr_3 = new TGraph(nPoints,x_lens,tan_alpha_lens_3);
  gr_3->Draw("APL same");
  gr_3->Fit("pol5","","",-300,300);
  TF1 *gr_fit_3 = (TF1*)gr_3->GetListOfFunctions()->FindObject("pol5");

  TString fileN01 = "lens_profile_n1.4.dat";
  TString fileN02 = "lens_profile_n1.5.dat";
  TString fileN03 = "lens_profile_n1.6.dat";

  FILE *fp01;
  fp01 = fopen(fileN01.Data(), "w+");
  FILE *fp02;
  fp02 = fopen(fileN02.Data(), "w+");
  FILE *fp03;
  fp03 = fopen(fileN03.Data(), "w+");
  
  for(Int_t ii = 0;ii<nPoints;ii++){
    x2_lens[ii] = xMin + (xMax - xMin)/(nPoints - 1)*ii;
    y_lens_1[ii] = gr_fit_1->Integral(xMin,x2_lens[ii]) + 20;
    y_lens_2[ii] = gr_fit_2->Integral(xMin,x2_lens[ii]) + 20;
    y_lens_3[ii] = gr_fit_3->Integral(xMin,x2_lens[ii]) + 20;
    fprintf(fp01, "%20.10f %20.10f \n",x2_lens[ii],y_lens_1[ii]);
    fprintf(fp02, "%20.10f %20.10f \n",x2_lens[ii],y_lens_2[ii]);
    fprintf(fp03, "%20.10f %20.10f \n",x2_lens[ii],y_lens_3[ii]);
  }

  fclose(fp01);
  fclose(fp02);
  fclose(fp03);
  
  TCanvas *c4 = new TCanvas("c4",fileN.Data(),10,10,1200,800);
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

  TGraph *gr_lens_3 = new TGraph(nPoints,x2_lens,y_lens_3);
  gr_lens_3->SetLineWidth(3.0);
  gr_lens_3->SetLineColor(kGreen+2);
  gr_lens_3->SetMarkerColor(kGreen+2);
  
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_lens_1);
  mg->Add(gr_lens_2);
  mg->Add(gr_lens_3);

  mg->Draw("apl");
  
  mg->GetXaxis()->SetTitle("lens x, mm");
  mg->GetYaxis()->SetTitle("lens thickness, mm");

  mg->GetYaxis()->SetRangeUser(0,25.0);
  
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_lens_1, "n = 1.4", "l");
  leg->AddEntry(gr_lens_2, "n = 1.5", "l");
  leg->AddEntry(gr_lens_3, "n = 1.6", "l");
  leg->Draw();

  TCanvas *c5 = new TCanvas("c5",fileN.Data(),10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);

  gr_lens_2->Draw("APL same");
  gr_lens_2->Fit("pol6","","",-300,300);
  gr_lens_2->GetYaxis()->SetRangeUser(0,25.0);  
  TF1 *f_fit_gr_lens_2 = (TF1*)gr_lens_2->GetListOfFunctions()->FindObject("pol6");
  
  const Int_t nn = 1000;
  Double_t xMin_lens = -300.0;
  Double_t xMax_lens =  300.0;
  Double_t x_lens3[nn];
  Double_t curvature_lens[nn];
  Double_t r_lens[nn];
  
  curvatureCalculation( f_fit_gr_lens_2, nn, xMin_lens, xMax_lens, x_lens3, curvature_lens, r_lens);
  TGraph *gr_curvature = new TGraph(nn,x_lens3, curvature_lens);
  TGraph *gr_r = new TGraph(nn,x_lens3, r_lens);
  
  TCanvas *c6 = new TCanvas("c6",fileN.Data(),10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gr_curvature->Draw("APL");

  TCanvas *c7 = new TCanvas("c7",fileN.Data(),10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gr_r->Draw("APL");  
  */
  return 0;
}

Double_t getAlpha_of_the_correction_surface(Double_t correctionAngle, Double_t n_reff){
  Double_t S = TMath::Sin(correctionAngle);
  Double_t A = n_reff - TMath::Cos(correctionAngle);
  return TMath::ASin(S/TMath::Sqrt(A*A + S*S));
}

void curvatureCalculation(TF1 *f_lens, Int_t nn, Double_t xMin, Double_t xMax, Double_t *x, Double_t *curv, Double_t *r){
  for(Int_t i = 0;i<nn;i++){
    x[i] = xMin + (xMax - xMin)/(nn - 1)*i;
    curv[i] = f_lens->Derivative2(x[i])/(1.0 + TMath::Power((f_lens->Derivative(x[i])*f_lens->Derivative(x[i])),3.0/2.0));
    if(curv[i] != 0.0)
      r[i] = 1.0/curv[i];
    else
      r[i] = 0.0;
  }
} 

Double_t pol7_asymmetric(Double_t *x, Double_t *par){
  Double_t p0  = par[0];
  Double_t p1  = par[1];
  Double_t p3  = par[2];
  Double_t p5  = par[3];
  Double_t p7  = par[4];
  return p0 + p1*TMath::Power(x[0],1) + p3*TMath::Power(x[0],3) + p5*TMath::Power(x[0],5) + p7*TMath::Power(x[0],7);
}

Double_t pol8_symmetric(Double_t *x, Double_t *par){
  Double_t p0  = par[0];
  Double_t p2  = par[1];
  Double_t p4  = par[2];
  Double_t p6  = par[3];
  Double_t p8  = par[4];
  return p0 + p2*TMath::Power(x[0],2) + p4*TMath::Power(x[0],4) + p6*TMath::Power(x[0],6) + p8*TMath::Power(x[0],8);
}
