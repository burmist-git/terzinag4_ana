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

void save_data_file(TString fileOutName, TGraph *gr);

Int_t plots_Flt_vs_Sph(){
  //
  const Int_t n = 8;
  //
  Double_t theta_arr[n];
  Double_t psf_flt_arr[n];
  Double_t psf_spr_arr[n];
  //
  //Double_t frac = 57.1/3.5;
  Double_t frac = 1.0;
  theta_arr[0] = 0.0*frac;
  theta_arr[1] = 0.5*frac;
  theta_arr[2] = 1.0*frac;
  theta_arr[3] = 1.5*frac;
  theta_arr[4] = 2.0*frac;
  theta_arr[5] = 2.5*frac;
  theta_arr[6] = 3.0*frac;
  theta_arr[7] = 3.5*frac;
  //
  Double_t frac_sigma = 1.0;
  psf_flt_arr[0] = 0.160*frac_sigma;
  psf_flt_arr[1] = 0.190*frac_sigma;
  psf_flt_arr[2] = 0.270*frac_sigma;
  psf_flt_arr[3] = 0.380*frac_sigma;
  psf_flt_arr[4] = 0.510*frac_sigma;
  psf_flt_arr[5] = 0.690*frac_sigma;
  psf_flt_arr[6] = 0.870*frac_sigma;
  psf_flt_arr[7] = 1.110*frac_sigma;
  //  
  psf_spr_arr[0] = 0.150*frac_sigma;
  psf_spr_arr[1] = 0.180*frac_sigma;
  psf_spr_arr[2] = 0.244*frac_sigma;
  psf_spr_arr[3] = 0.330*frac_sigma;
  psf_spr_arr[4] = 0.416*frac_sigma;
  psf_spr_arr[5] = 0.510*frac_sigma;
  psf_spr_arr[6] = 0.610*frac_sigma;
  psf_spr_arr[7] = 0.700*frac_sigma;
  //
  //
  TGraph *gr_flt = new TGraph(n,theta_arr,psf_flt_arr);
  TGraph *gr_spr = new TGraph(n,theta_arr,psf_spr_arr);
  //
  save_data_file("psf_sigma_flt.dat", gr_flt);
  save_data_file("psf_sigma_spr.dat", gr_spr);
  //
  //
  gr_flt->SetMarkerStyle(20);
  gr_spr->SetMarkerStyle(20);
  //
  gr_flt->SetMarkerColor(kRed);
  gr_spr->SetMarkerColor(kBlack);
  //
  gr_flt->SetLineColor(kRed);
  gr_spr->SetLineColor(kBlack);
  //
  gr_flt->SetLineWidth(3);
  gr_spr->SetLineWidth(3);
  //
  TCanvas *c1 = new TCanvas("c4","c4",10,10,1200,800);
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
  TMultiGraph *mg = new TMultiGraph();
  //mg->Add(gr_flt);
  mg->Add(gr_spr);
  mg->Draw("APL");
  mg->SetMinimum(0.0);
  //mg->SetMaximum(4.0);
  //mg->SetMaximum(6.0);
  //mg->SetMaximum(5.0);
  mg->GetXaxis()->SetTitle("#theta, deg");
  //mg->GetYaxis()->SetTitle("2*RMS, mm");
  mg->GetYaxis()->SetTitle("RMS, mm");
  //  
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_flt, "Flat", "pl");
  leg->AddEntry(gr_spr, "Spherical", "pl");
  //leg->Draw();
  return 0;
}

void save_data_file(TString fileOutName, TGraph *gr){
  FILE *fp01;
  fp01 = fopen(fileOutName.Data(), "w+");
  Double_t x;
  Double_t y;
  for(int i=0; i<gr->GetN(); i++) {
    gr->GetPoint(i,x,y);
    fprintf(fp01, "%20.10f %20.10f \n",x,y);
  }  
  fclose(fp01);
}
