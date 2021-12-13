//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TGaxis.h>
#include <TLine.h>
#include <TMath.h>
#include <TF1.h>
#include <TLegend.h>
#include <TMultiGraph.h>

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

// Please _note_ the lambda is in nm
Double_t getSellmeierQuartz(Double_t lam){
  lam = lam/1000.0;
  Double_t B1 = 0.696166300;
  Double_t B2 = 0.407942600;
  Double_t B3 = 0.897479400;
  //  
  Double_t C1 = 4.67914826*1.0e-3; //um^2
  Double_t C2 = 1.35120631*1.0e-2; //um^2
  Double_t C3 = 97.9340025;        //um^2
  //  
  return TMath::Sqrt(1 + B1*lam*lam/(lam*lam-C1) + B2*lam*lam/(lam*lam-C2) + B3*lam*lam/(lam*lam-C3));
}

TGraph *quartz_RefractiveIndex_vs_wavelength(){
  //  
  TF1 *f_nm_to_eV = new TF1("f_nm_to_eV","1239.84/x");
  //double lam_min =  247.9683860000000;
  //double lam_max = 1033.2016083333335;
  double lam_min =  300.0;
  double lam_max = 1000.0;
  double lam;
  double E_min = f_nm_to_eV->Eval(lam_max);
  double E_max = f_nm_to_eV->Eval(lam_min);
  double E;
  TString outData_RI_vs_eV = "./fused_silica_refractive_index_eV.dat";
  //
  const int num = 100;
  double WaveLength[num];
  double PhotonEnergy[num];
  double QuartzRefractiveIndex_nm[num];
  double QuartzRefractiveIndex_eV[num];
  //
  for(int i=0; i<num; i++) {
    lam = lam_min + (lam_max - lam_min)/(num - 1)*i;
    WaveLength[i] = lam;
    QuartzRefractiveIndex_nm[i] = getSellmeierQuartz(lam);
  }
  for(int i=0; i<num; i++) {
    E = E_min + (E_max - E_min)/(num - 1)*i;
    PhotonEnergy[i] = E;
    lam = f_nm_to_eV->Eval(E);
    QuartzRefractiveIndex_eV[i] = getSellmeierQuartz(lam);
  }  
  //
  TGraph *gr_RI_vs_nm = new TGraph( num, WaveLength, QuartzRefractiveIndex_nm);
  gr_RI_vs_nm->SetTitle("");
  gr_RI_vs_nm->SetLineColor(kRed);
  gr_RI_vs_nm->SetMarkerColor(kRed);
  gr_RI_vs_nm->SetLineWidth(2.0);
  gr_RI_vs_nm->GetXaxis()->SetTitle("#lambda, nm");
  gr_RI_vs_nm->GetYaxis()->SetTitle("Refractive Index");
  //
  TGraph *gr_RI_vs_eV = new TGraph( num, PhotonEnergy, QuartzRefractiveIndex_eV);
  gr_RI_vs_eV->SetTitle("");
  gr_RI_vs_eV->SetLineColor(kRed);
  gr_RI_vs_eV->SetMarkerColor(kRed);
  gr_RI_vs_eV->SetLineWidth(2.0);
  gr_RI_vs_eV->GetXaxis()->SetTitle("Photon energy, eV");
  gr_RI_vs_eV->GetYaxis()->SetTitle("Refractive Index");
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  c1->SetRightMargin(0.01);
  c1->SetLeftMargin(0.08);
  c1->SetTopMargin(0.01);
  c1->SetBottomMargin(0.08);
  c1->Divide(2,1);
  //
  c1->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  gr_RI_vs_nm->Draw("APL");
  c1->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  gr_RI_vs_eV->Draw("APL");
  //
  FILE *fp01;
  fp01 = fopen(outData_RI_vs_eV.Data(), "w+");
  for(int i=0; i<num; i++) {
    PhotonEnergy[i];
    QuartzRefractiveIndex_eV[i];
    fprintf(fp01, "%10.7f %10.7f \n",PhotonEnergy[i],QuartzRefractiveIndex_eV[i]);
  }  
  fclose(fp01);
  //
  return gr_RI_vs_nm;
}
