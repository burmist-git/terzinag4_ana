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

TGraph *quartz_QuartzAbsorption_vs_wavelength(){
  TGraph *gr_abs_nm = new TGraph();
  TGraph *gr_abs_ev = new TGraph();
  TGraph *gr_copy_nm = new TGraph();
  ifstream fileQAbs("QuartzAbsorption.data");
  TString outData_ABSORB_vs_eV = "./fused_silica_absorption_eV.dat";
  Double_t lam;
  Double_t eV;
  Double_t absl;
  TF1 *f_nm_to_eV = new TF1("f_nm_to_eV","1239.84/x");
  if(fileQAbs.is_open()){
    while(fileQAbs>>eV>>lam>>absl){
      eV = eV*1000000.0;
      lam = lam/1000000.0;
      gr_abs_nm->SetPoint(gr_abs_nm->GetN(),lam,absl/1000.0);
      gr_abs_ev->SetPoint(gr_abs_ev->GetN(),eV,absl/1000.0);
      gr_copy_nm->SetPoint(gr_copy_nm->GetN(),lam,absl/1000.0);
    }
    fileQAbs.close();
  }
  else{
    cout<<"Unable to open file \n";
  }
  gr_copy_nm->Fit("expo","Q","",600,650);
  TF1 *f_fit = (TF1*)gr_copy_nm->GetListOfFunctions()->FindObject("expo");
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  //
  c1->SetRightMargin(0.01);
  c1->SetLeftMargin(0.08);
  c1->SetTopMargin(0.01);
  c1->SetBottomMargin(0.08);
  //gr_copy_nm->Draw();
  //
  for(Int_t i = 0;i<35;i++){
    lam = 660 + i*10;
    eV = f_nm_to_eV->Eval(lam);
    gr_abs_nm->SetPoint(gr_abs_nm->GetN(),lam,f_fit->Eval(lam));
    gr_abs_ev->SetPoint(gr_abs_ev->GetN(),eV,f_fit->Eval(lam));
  }
  c1->Divide(2,1);
  //
  c1->cd(1);  
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  gr_abs_nm->SetMarkerStyle(20);
  gr_abs_nm->SetLineWidth(2.0);
  gr_abs_nm->Draw("AP");
  gr_abs_nm->GetXaxis()->SetTitle("#lambda, nm");
  gr_abs_nm->GetYaxis()->SetTitle("Photon free path length in fused silica, m");
  gr_abs_nm->SetMinimum(80);
  c1->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  gr_abs_ev->SetMarkerStyle(20);
  gr_abs_ev->SetLineWidth(2.0);
  gr_abs_ev->Draw("AP");
  gr_abs_ev->GetXaxis()->SetTitle("Photon energy, eV");
  gr_abs_ev->GetYaxis()->SetTitle("Photon free path length in fused silica, m");
  gr_abs_ev->SetMinimum(80);
  //
  FILE *fp01;
  fp01 = fopen(outData_ABSORB_vs_eV.Data(), "w+");
  fprintf(fp01, " ev        m \n");
  for(int i=0; i<71; i++) {
    Double_t x_nm,x,y;
    x_nm = 1000 - 10*i;
    x = f_nm_to_eV->Eval(x_nm);    
    y = gr_abs_ev->Eval(x);
    fprintf(fp01, "%10.7f %10.7f \n",x,y);
  }  
  fclose(fp01);
  //
  return gr_abs_nm;
}
