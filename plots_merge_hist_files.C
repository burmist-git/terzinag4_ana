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

Double_t getLogLog_spline(TGraphErrors *gr1, Double_t el_in_PeV);
Double_t getLogLog_and_lin_spline(TGraphErrors *gr_eff_vs_e, Double_t e_In_PeV);
Double_t log_log_spline(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Double_t el_in_PeV);
void copyHistogram(TH1D *h1, TH1D *h1_copy, TString h1_name_g, TString h1_title_g, bool ifBinsOnly, double norm);

Double_t eff_Fit_func(Double_t *x, Double_t *par){
  Double_t k  = par[0];
  Double_t b  = par[1];
  return k*x[0] + b;
}

Int_t plots_merge_hist_files(){
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
  TGraph *gr1[n];
  TH1D *h1[n];
  TH1D *h1_distToEarth_cut[n];
  TH1D *h1_distToEarth_cut_tot = new TH1D("h1_distToEarth_cut_tot","distToEarth cut tot",100,0.0,50.0);
  TH1D *h1_distToTerzina_cut[n];
  TH1D *h1_distToTerzina_cut_tot = new TH1D("h1_distToTerzina_cut_tot","distToTerzina cut tot",80,0.0,40.0);
  for(Int_t i = 0;i<8;i++){
   f1[i] = new TFile(fileNarr[i].Data());
   h1[i] = (TH1D*)f1[i]->Get("h1_npe_th");
   h1_distToEarth_cut[i] = (TH1D*)f1[i]->Get("h1_distToEarth_cut");
   h1_distToTerzina_cut[i] = (TH1D*)f1[i]->Get("h1_distToTerzina_cut");
   gr1[i] = (TGraph*)f1[i]->Get("gr_npe_th");
  }
  //
  //
  //fileNarr[7]="./merg_hist/hist_merg_hist_3000PeV.root";
  //  
  //
  TFile *f1_cos_par_spec = new TFile("cosmique_particle_spectrum.root");
  TH1D *h1_particle_per_year = (TH1D*)f1_cos_par_spec->Get("h1_particle_per_year");
  TH1D *h1_particle_per_year_more = (TH1D*)f1_cos_par_spec->Get("h1_particle_per_year_more");  
  TH1D *h1_particle_per_year_tot = new TH1D();
  TH1D *h1_particle_per_year_eff = new TH1D();
  TH1D *h1_particle_per_year_eff_lin = new TH1D();
  //
  copyHistogram(h1_particle_per_year, h1_particle_per_year_tot, "h1_particle_per_year_tot", "h1_particle_per_year_tot", false, 1.0);
  copyHistogram(h1_particle_per_year, h1_particle_per_year_eff, "h1_particle_per_year_eff", "h1_particle_per_year_eff", true, 1.0);
  copyHistogram(h1_particle_per_year, h1_particle_per_year_eff_lin, "h1_particle_per_year_eff_lin", "h1_particle_per_year_eff_lin", true, 1.0);
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
  gPad->SetGridx();
  gPad->SetGridy();
  //
  //h1[0]->Draw();
  //h1[0]->SetMaximum(0.5);
  //h1[0]->SetMinimum(1.0e-8);
  //
  for(Int_t i = 0;i<n;i++){
    gr1[i]->SetLineWidth(3.0);
    gr1[i]->SetLineColor(kBlack);
    gr1[i]->SetMarkerStyle(20);
    gr1[i]->SetMarkerColor(kBlack);
  }
  //
  gr1[0]->SetMarkerStyle(6);
  gr1[0]->SetLineColor(kBlack);
  gr1[0]->SetMarkerColor(kBlack);
  //
  gr1[1]->SetMarkerStyle(6);
  gr1[1]->SetLineColor(kRed);
  gr1[1]->SetMarkerColor(kRed);
  //
  gr1[2]->SetMarkerStyle(6);
  gr1[2]->SetLineColor(kBlue);
  gr1[2]->SetMarkerColor(kBlue);
  //
  gr1[3]->SetMarkerStyle(6);
  gr1[3]->SetLineColor(kGreen+2);
  gr1[3]->SetMarkerColor(kGreen+2);
  //
  gr1[4]->SetMarkerStyle(20);
  gr1[4]->SetLineColor(kBlack);
  gr1[4]->SetMarkerColor(kBlack);
  //
  gr1[5]->SetMarkerStyle(20);
  gr1[5]->SetLineColor(kRed);
  gr1[5]->SetMarkerColor(kRed);
  //
  gr1[6]->SetMarkerStyle(20);
  gr1[6]->SetLineColor(kBlue);
  gr1[6]->SetMarkerColor(kBlue);
  //
  gr1[7]->SetMarkerStyle(20);
  gr1[7]->SetLineColor(kGreen+2);
  gr1[7]->SetMarkerColor(kGreen+2);

  TMultiGraph *mg = new TMultiGraph();
  for(Int_t i = 0;i<n;i++)
    mg->Add(gr1[i]);

  //mg->GetXaxis()->SetLimits(xMin,xMax);
  mg->Draw("APL");
  mg->SetMinimum(1.0e-8);
  mg->SetMaximum(1.0);
  //mg->SetMaximum(6.0);
  //mg->SetMaximum(5.0);
  mg->GetXaxis()->SetTitle("# p.e.");
  mg->GetYaxis()->SetTitle("efficiency");
  //
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr1[0], "10   PeV", "pl");
  leg->AddEntry(gr1[1], "35   PeV", "pl");
  leg->AddEntry(gr1[2], "70   PeV", "pl");
  leg->AddEntry(gr1[3], "100  PeV", "pl");
  leg->AddEntry(gr1[4], "350  PeV", "pl");
  leg->AddEntry(gr1[5], "700  PeV", "pl");
  leg->AddEntry(gr1[6], "1000 PeV", "pl");
  leg->AddEntry(gr1[7], "3000 PeV", "pl");
  leg->Draw();
  //
  //
  TCanvas *c2 = new TCanvas("c2","c2",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  //
  c2->SetRightMargin(0.01);
  c2->SetLeftMargin(0.08);
  c2->SetTopMargin(0.01);
  c2->SetBottomMargin(0.08);
  //
  //
  TGraphErrors *gr_eff_vs_e = new TGraphErrors();
  gr_eff_vs_e->SetName("gr_eff_vs_e");
  gr_eff_vs_e->SetTitle("gr_eff_vs_e");
  int pointID;
  //
  gr_eff_vs_e->SetMarkerStyle(20);
  gr_eff_vs_e->SetLineColor(kBlack);
  gr_eff_vs_e->SetLineWidth(3.0);
  gr_eff_vs_e->SetMarkerColor(kBlack);
  //
  pointID = gr_eff_vs_e->GetN();
  gr_eff_vs_e->SetPoint(pointID,10,1.0e-9);
  //gr_eff_vs_e->SetPointError(pointID,0.0,1.0e-9/10.0);
  gr_eff_vs_e->SetPointError(pointID,0.0,0.0);
  //
  pointID = gr_eff_vs_e->GetN();
  gr_eff_vs_e->SetPoint(pointID,35,h1[1]->GetBinContent(8));
  //gr_eff_vs_e->SetPointError(pointID,0.0,h1[1]->GetBinContent(8)/3.0);
  gr_eff_vs_e->SetPointError(pointID,0.0,0.0);
  //
  pointID = gr_eff_vs_e->GetN();
  gr_eff_vs_e->SetPoint(pointID,70,h1[2]->GetBinContent(8));
  //gr_eff_vs_e->SetPointError(pointID,0.0,h1[2]->GetBinContent(8)/3.0);
  gr_eff_vs_e->SetPointError(pointID,0.0,0.0);
  //
  pointID = gr_eff_vs_e->GetN();
  gr_eff_vs_e->SetPoint(pointID,100,h1[3]->GetBinContent(8));
  //gr_eff_vs_e->SetPointError(pointID,0.0,h1[3]->GetBinContent(8)/3.0);
  gr_eff_vs_e->SetPointError(pointID,0.0,0.0);
  //
  pointID = gr_eff_vs_e->GetN();
  gr_eff_vs_e->SetPoint(pointID,350,h1[4]->GetBinContent(8));
  //gr_eff_vs_e->SetPointError(pointID,0.0,h1[4]->GetBinContent(8)/100.0);
  gr_eff_vs_e->SetPointError(pointID,0.0,0.0);
  //
  pointID = gr_eff_vs_e->GetN();
  gr_eff_vs_e->SetPoint(pointID,700,h1[5]->GetBinContent(8));
  //gr_eff_vs_e->SetPointError(pointID,0.0,h1[5]->GetBinContent(8)/100.0);
  gr_eff_vs_e->SetPointError(pointID,0.0,0.0);
  //
  pointID = gr_eff_vs_e->GetN();
  gr_eff_vs_e->SetPoint(pointID,1000,h1[6]->GetBinContent(8));
  //gr_eff_vs_e->SetPointError(pointID,0.0,h1[6]->GetBinContent(8)/100.0);
  gr_eff_vs_e->SetPointError(pointID,0.0,0.0);
  //
  pointID = gr_eff_vs_e->GetN();
  gr_eff_vs_e->SetPoint(pointID,3000,h1[7]->GetBinContent(8));
  //gr_eff_vs_e->SetPointError(pointID,0.0,h1[7]->GetBinContent(8)/100.0);
  gr_eff_vs_e->SetPointError(pointID,0.0,0.0);
  //
  gr_eff_vs_e->SetTitle("");
  gr_eff_vs_e->Draw("APL");
  //
  gr_eff_vs_e->GetXaxis()->SetTitle("Energy, PeV");
  gr_eff_vs_e->GetYaxis()->SetTitle("efficiency");
  //
  //gPad->SetGridx();
  //gPad->SetGridy();
  //////////

  /*
  Double_t e_min01 = 100;
  Double_t e_max01 = 355;
  Int_t npar_eff_Fit_func = 2;
  TF1 *f_eff_vs_e01 = new TF1("f_eff_vs_e01", eff_Fit_func, e_min01, e_max01, npar_eff_Fit_func);
  f_eff_vs_e01->SetParameter(0,0.0);
  f_eff_vs_e01->SetParameter(1,1.0);  
  
  Double_t e_min02 = 65;
  Double_t e_max02 = 105;
  npar_eff_Fit_func = 2;
  TF1 *f_eff_vs_e02 = new TF1("f_eff_vs_e02", eff_Fit_func, e_min01, e_max01, npar_eff_Fit_func);
  f_eff_vs_e02->SetParameter(0,0.0);
  f_eff_vs_e02->SetParameter(1,1.0);  

  gr_eff_vs_e->Fit("f_eff_vs_e01","","",e_min01,e_max01);
  gr_eff_vs_e->Fit("f_eff_vs_e02","","",e_min02,e_max02);

  f_eff_vs_e01->Draw("same");
  f_eff_vs_e02->Draw("same");
  */
  
  ///////////////////
  Double_t e_min = 10;
  Double_t e_max = 3000;
  Double_t loge_min = TMath::Log10(e_min);
  Double_t loge_max = TMath::Log10(e_max);
  Double_t loge;
  Double_t el;
  ///////////////////

  ///////////////////
  Int_t nn = 1000;
  TGraph *gr_eff_vs_e_extrapolated = new TGraph();
  gr_eff_vs_e_extrapolated->SetName("gr_eff_vs_e_extrapolated");
  gr_eff_vs_e_extrapolated->SetTitle("gr_eff_vs_e_extrapolated");
  TGraph *gr_eff_vs_e_extrapolated_log = new TGraph();
  gr_eff_vs_e_extrapolated_log->SetName("gr_eff_vs_e_extrapolated_log");
  gr_eff_vs_e_extrapolated_log->SetTitle("gr_eff_vs_e_extrapolated_log");
  Double_t logLog_spline;
  for(Int_t i = 0;i<nn;i++){
    loge = loge_min + (loge_max-loge_min)/(nn-1)*i;
    el = TMath::Power(10,loge);
    gr_eff_vs_e_extrapolated->SetPoint(gr_eff_vs_e_extrapolated->GetN(),el,gr_eff_vs_e->Eval(el));
  }
  //
  e_min = 10;
  e_max = 2999;
  nn = 30;
  loge_min = TMath::Log10(e_min);
  loge_max = TMath::Log10(e_max);
  for(Int_t i = 0;i<nn;i++){
    loge = loge_min + (loge_max-loge_min)/(nn-1)*i;
    el = TMath::Power(10,loge);
    logLog_spline = getLogLog_spline(gr_eff_vs_e,el);
    gr_eff_vs_e_extrapolated_log->SetPoint(gr_eff_vs_e_extrapolated_log->GetN(),el,logLog_spline);
  }

  //
  gr_eff_vs_e_extrapolated->SetMarkerStyle(6);
  gr_eff_vs_e_extrapolated->SetLineColor(kRed);
  gr_eff_vs_e_extrapolated->SetLineWidth(3.0);
  gr_eff_vs_e_extrapolated->SetMarkerColor(kRed);
  //
  gr_eff_vs_e_extrapolated_log->SetMarkerStyle(20);
  gr_eff_vs_e_extrapolated_log->SetLineColor(kBlack);
  gr_eff_vs_e_extrapolated_log->SetLineWidth(3.0);
  gr_eff_vs_e_extrapolated_log->SetMarkerColor(kBlue);
  //
  
  TCanvas *c3 = new TCanvas("c3","c3",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  //
  c3->SetRightMargin(0.01);
  c3->SetLeftMargin(0.08);
  c3->SetTopMargin(0.01);
  c3->SetBottomMargin(0.08);
  //
  
  TMultiGraph *mg2 = new TMultiGraph();
  mg2->Add(gr_eff_vs_e);
  mg2->Add(gr_eff_vs_e_extrapolated);
  mg2->Add(gr_eff_vs_e_extrapolated_log);
  mg2->Draw("APL");
  mg2->SetMinimum(1.0e-9);
  mg2->SetMaximum(1.0);
  
  TLegend *leg03 = new TLegend(0.6,0.3,0.9,0.6,"","brNDC");
  leg03->AddEntry(gr_eff_vs_e, "MC.", "pl");
  leg03->AddEntry(gr_eff_vs_e_extrapolated, "Linear interpolation", "pl");
  leg03->AddEntry(gr_eff_vs_e_extrapolated_log, "Log log interpolation", "pl");
  leg03->Draw();

  mg2->GetXaxis()->SetTitle("Energy, PeV");
  mg2->GetYaxis()->SetTitle("Efficiency");
  //----------------------------------
  //
  //
  Double_t eff;
  Double_t e_In_GeV;
  Double_t e_In_PeV;
  for(Int_t i = 1;i<=h1_particle_per_year->GetNbinsX();i++){
    e_In_GeV = h1_particle_per_year->GetBinCenter(i);
    e_In_PeV = e_In_GeV/1.0e+6;
    //
    //cout<<"e_In_GeV "<<e_In_GeV<<endl
    //	<<"e_In_PeV "<<e_In_PeV<<endl;
    //
    if(e_In_PeV<3000){
      //eff = getLogLog_spline(gr_eff_vs_e,e_In_PeV);
      eff = getLogLog_and_lin_spline(gr_eff_vs_e,e_In_PeV);
      h1_particle_per_year_eff->SetBinContent(i,h1_particle_per_year->GetBinContent(i)*eff);
      eff = gr_eff_vs_e->Eval(e_In_PeV);
      h1_particle_per_year_eff_lin->SetBinContent(i,h1_particle_per_year->GetBinContent(i)*eff);
    }
    else{
      eff = getLogLog_spline(gr_eff_vs_e,2999);
      h1_particle_per_year_eff->SetBinContent(i,h1_particle_per_year->GetBinContent(i)*eff);
      eff = gr_eff_vs_e->Eval(2999);
      h1_particle_per_year_eff_lin->SetBinContent(i,h1_particle_per_year->GetBinContent(i)*eff);
    }
  }
  //
  //
  //----------------------------------
  //
  TCanvas *c4 = new TCanvas("c4","c4",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  //
  c4->SetRightMargin(0.01);
  c4->SetLeftMargin(0.08);
  c4->SetTopMargin(0.01);
  c4->SetBottomMargin(0.08);
  //h1_particle_per_year_eff->Draw();
  ////////////////////////////////////

  h1_particle_per_year_tot->SetTitle("");

  h1_particle_per_year_tot->SetName("Total");
  h1_particle_per_year_eff->SetName("Log-log ");
  h1_particle_per_year_eff_lin->SetName("Linear");

  h1_particle_per_year_tot->SetLineColor(kBlack);
  h1_particle_per_year_eff->SetLineColor(kRed);
  h1_particle_per_year_eff_lin->SetLineColor(kBlue);

  h1_particle_per_year_tot->SetLineWidth(3.0);
  h1_particle_per_year_eff->SetLineWidth(3.0);
  h1_particle_per_year_eff_lin->SetLineWidth(3.0);

  h1_particle_per_year_tot->Draw();
  h1_particle_per_year_eff->Draw("sames");
  //h1_particle_per_year_eff_lin->Draw("sames");

  h1_particle_per_year_tot->GetXaxis()->SetTitle("Energy, GeV");
  h1_particle_per_year_tot->GetYaxis()->SetTitle("Number of events during 3 years");
  
  TLegend *leg04 = new TLegend(0.6,0.3,0.9,0.6,"","brNDC");
  leg04->AddEntry(h1_particle_per_year_tot, "Total", "l");
  leg04->AddEntry(h1_particle_per_year_eff, "Log - linear interpolation","l");
  //leg04->AddEntry(h1_particle_per_year_eff_lin, "Linear interpolation", "l");
  leg04->Draw();
  //
  //----------------------------------
  //
  TCanvas *c5 = new TCanvas("c5","c5",10,10,800,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  //gStyle->SetOptStat(kFALSE);
  //
  c5->SetRightMargin(0.02);
  c5->SetLeftMargin(0.1);
  c5->SetTopMargin(0.01);
  c5->SetBottomMargin(0.08);
  //h1_particle_per_year_eff->Draw();  
  //  
  cout<<100<<" "<<h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(100*1.0e+6))<<endl;
  Double_t val = 0;
  Double_t ww = 0;
  Double_t ee_in_pev = 0;
  for(Int_t ii = 1;ii<=h1_distToEarth_cut_tot->GetNbinsX();ii++){
    //val = h1_distToEarth_cut_tot->GetBinContent(ii);
    //
    val = 0.0;
    //10
    ee_in_pev = 10;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val = h1_distToEarth_cut[0]->GetBinContent(ii)*ww;
    //35
    ee_in_pev = 35;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToEarth_cut[1]->GetBinContent(ii)*ww;
    //70
    ee_in_pev = 70;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToEarth_cut[2]->GetBinContent(ii)*ww;
    //100
    ee_in_pev = 100;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToEarth_cut[3]->GetBinContent(ii)*ww;
    //350
    ee_in_pev = 350;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToEarth_cut[4]->GetBinContent(ii)*ww;
    //700
    ee_in_pev = 700;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToEarth_cut[5]->GetBinContent(ii)*ww;
    //1000
    ee_in_pev = 1000;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToEarth_cut[6]->GetBinContent(ii)*ww;
    //1000
    ee_in_pev = 3000;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToEarth_cut[7]->GetBinContent(ii)*ww;
    //
    h1_distToEarth_cut_tot->SetBinContent(ii,val);
  }
  h1_distToEarth_cut_tot->SetTitle("");
  h1_distToEarth_cut_tot->SetLineColor(kBlack);
  h1_distToEarth_cut_tot->SetLineWidth(3.0);
  h1_distToEarth_cut_tot->Draw();
  h1_distToEarth_cut_tot->GetXaxis()->SetTitle("Altitude, km");
  ////////////////////////////////////////////////////////////////////  
  //cout<<h1_distToEarth_cut_tot->Integral("width");

  //
  //----------------------------------
  //
  TCanvas *c6 = new TCanvas("c6","c6",10,10,800,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  //gStyle->SetOptStat(kFALSE);
  //
  c6->SetRightMargin(0.02);
  c6->SetLeftMargin(0.1);
  c6->SetTopMargin(0.01);
  c6->SetBottomMargin(0.08);
  //
  for(Int_t ii = 1;ii<=h1_distToTerzina_cut_tot->GetNbinsX();ii++){
    //val = h1_distToEarth_cut_tot->GetBinContent(ii);
    //
    val = 0.0;
    //10
    ee_in_pev = 10;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val = h1_distToTerzina_cut[0]->GetBinContent(ii)*ww;
    //35
    ee_in_pev = 35;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToTerzina_cut[1]->GetBinContent(ii)*ww;
    //70
    ee_in_pev = 70;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToTerzina_cut[2]->GetBinContent(ii)*ww;
    //100
    ee_in_pev = 100;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToTerzina_cut[3]->GetBinContent(ii)*ww;
    //350
    ee_in_pev = 350;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToTerzina_cut[4]->GetBinContent(ii)*ww;
    //700
    ee_in_pev = 700;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToTerzina_cut[5]->GetBinContent(ii)*ww;
    //1000
    ee_in_pev = 1000;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToTerzina_cut[6]->GetBinContent(ii)*ww;
    //1000
    ee_in_pev = 3000;
    ww = h1_particle_per_year_eff->GetBinContent(h1_particle_per_year_eff->FindBin(ee_in_pev*1.0e+6));
    val += h1_distToTerzina_cut[7]->GetBinContent(ii)*ww;
    //
    h1_distToTerzina_cut_tot->SetBinContent(ii,val);
  }
  h1_distToTerzina_cut_tot->SetTitle("");
  h1_distToTerzina_cut_tot->SetLineColor(kBlack);
  h1_distToTerzina_cut_tot->SetLineWidth(3.0);
  h1_distToTerzina_cut_tot->Draw();
  h1_distToTerzina_cut_tot->GetXaxis()->SetTitle("Distance to Terzina, km");
  ////////////////////////////////////////////////////////////////////  
  
  return 0;
}

Double_t getLogLog_spline(TGraphErrors *gr1, Double_t el_in_PeV){
  Double_t x1;
  Double_t y1;
  Double_t x2;
  Double_t y2;
  for(Int_t i = 0;i<(gr1->GetN()-1);i++){
    gr1->GetPoint(i,x1,y1);
    gr1->GetPoint(i+1,x2,y2);
    if(el_in_PeV>=x1 && el_in_PeV<=x2)
      return log_log_spline(x1,y1,x2,y2,el_in_PeV);
  }
  return 0.5e-8;
}

Double_t getLogLog_and_lin_spline(TGraphErrors *gr1, Double_t e_In_PeV){
  Double_t x1;
  Double_t y1;
  Double_t x2;
  Double_t y2;
  //
  Double_t x_lin_window_min = 100;//PeV
  Double_t x_lin_window_max = 400;//PeV
  //
  for(Int_t i = 0;i<(gr1->GetN()-1);i++){
    gr1->GetPoint(i,x1,y1);
    gr1->GetPoint(i+1,x2,y2);
    if(e_In_PeV>=x_lin_window_min && e_In_PeV<=x_lin_window_max)
      return gr1->Eval(e_In_PeV);      
    if(e_In_PeV>=x1 && e_In_PeV<=x2)
      return log_log_spline(x1,y1,x2,y2,e_In_PeV);
  }
  return 0.5e-8;
}

Double_t log_log_spline(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Double_t el_in_PeV){
  Double_t k = TMath::Log(y1/y2)/TMath::Log(x1/x2);
  Double_t a = y1/TMath::Power(x1,k);
  return a*TMath::Power(el_in_PeV,k);
}

void copyHistogram(TH1D *h1, TH1D *h1_copy, TString h1_name_g, TString h1_title_g, bool ifBinsOnly, double norm){
  TString h1_name = h1_name_g;
  TString h1_title = h1_title_g;
  h1_copy->SetName(h1_name.Data());
  h1_copy->SetTitle(h1_title.Data());
  const int n_bins_max = 1000;
  double bins_low_edge[n_bins_max];
  int nBins = h1->GetNbinsX();
  if((nBins+1)>n_bins_max)
    cout<<"ERROR --> (nBins+1)  > n_bins_max"<<endl
        <<"          nBins      = "<<nBins<<endl
        <<"          n_bins_max = "<<n_bins_max<<endl;
  for(int i = 0;i<nBins;i++)
    bins_low_edge[i] = h1->GetBinLowEdge(i+1);
  bins_low_edge[nBins] = h1->GetBinLowEdge(nBins) + h1->GetBinWidth(nBins);
  h1_copy->SetBins(nBins,bins_low_edge);
  if(!ifBinsOnly && norm>0.0)
    for(int i = 1;i<=nBins;i++)
      h1_copy->SetBinContent(i,h1->GetBinContent(i)/norm);
}
