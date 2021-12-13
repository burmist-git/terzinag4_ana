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

void load_data_file(TString fileInName, TGraph *gr_nm, TGraph *gr_ev);
void save_data_file(TString fileOutName, TGraph *gr_nm);

TGraph *al_mirror_reflectance_vs_wavelength(){
  //
  TGraph *gr_al_mirror_refl_Unpolarized_nm = new TGraph();
  TGraph *gr_al_mirror_refl_Spolarized_nm = new TGraph();
  TGraph *gr_al_mirror_refl_Ppolarized_nm = new TGraph();
  //
  TGraph *gr_al_mirror_refl_Unpolarized_ev = new TGraph();
  TGraph *gr_al_mirror_refl_Spolarized_ev = new TGraph();
  TGraph *gr_al_mirror_refl_Ppolarized_ev = new TGraph();
  //
  load_data_file("./al_mirror_Reflectance_Unpolarized.dat", gr_al_mirror_refl_Unpolarized_nm, gr_al_mirror_refl_Unpolarized_ev);
  load_data_file("./al_mirror_Reflectance_P-polarized.dat", gr_al_mirror_refl_Ppolarized_nm,  gr_al_mirror_refl_Ppolarized_ev);
  load_data_file("./al_mirror_Reflectance_S-polarized.dat", gr_al_mirror_refl_Spolarized_nm,  gr_al_mirror_refl_Spolarized_ev);
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
  //
  c1->Divide(2,1);
  //
  c1->cd(1);  
  gPad->SetGridx();
  gPad->SetGridy();
  //gPad->SetLogy();
  gr_al_mirror_refl_Unpolarized_nm->SetLineColor(kBlack);
  gr_al_mirror_refl_Unpolarized_nm->SetLineWidth(2.0);
  gr_al_mirror_refl_Spolarized_nm->SetLineColor(kRed);
  gr_al_mirror_refl_Spolarized_nm->SetLineWidth(2.0);
  gr_al_mirror_refl_Ppolarized_nm->SetLineColor(kBlue);
  gr_al_mirror_refl_Ppolarized_nm->SetLineWidth(2.0);
  //
  TMultiGraph *mg_nm = new TMultiGraph();
  mg_nm->Add(gr_al_mirror_refl_Unpolarized_nm);
  mg_nm->Add(gr_al_mirror_refl_Ppolarized_nm);
  mg_nm->Add(gr_al_mirror_refl_Spolarized_nm);
  mg_nm->SetMinimum(50.0);
  mg_nm->SetMaximum(100.0);
  mg_nm->Draw("AL");
  mg_nm->GetXaxis()->SetTitle("#lambda, nm");
  mg_nm->GetYaxis()->SetTitle("Reflectance, %");
  //
  TLegend *leg = new TLegend(0.7,0.2,0.9,0.4,"","brNDC");
  leg->AddEntry(gr_al_mirror_refl_Unpolarized_nm, "Unpolarized","l");
  leg->AddEntry(gr_al_mirror_refl_Spolarized_nm, "S-Polarized","l");
  leg->AddEntry(gr_al_mirror_refl_Ppolarized_nm, "P-Polarized","l");
  leg->Draw();
  //
  c1->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  //gPad->SetLogy();
  //
  gr_al_mirror_refl_Unpolarized_ev->SetLineColor(kBlack);
  gr_al_mirror_refl_Unpolarized_ev->SetLineWidth(2.0);
  gr_al_mirror_refl_Spolarized_ev->SetLineColor(kRed);
  gr_al_mirror_refl_Spolarized_ev->SetLineWidth(2.0);
  gr_al_mirror_refl_Ppolarized_ev->SetLineColor(kBlue);
  gr_al_mirror_refl_Ppolarized_ev->SetLineWidth(2.0);
  //
  TMultiGraph *mg_ev = new TMultiGraph();
  mg_ev->Add(gr_al_mirror_refl_Unpolarized_ev);
  mg_ev->Add(gr_al_mirror_refl_Ppolarized_ev);
  mg_ev->Add(gr_al_mirror_refl_Spolarized_ev);
  mg_ev->SetMinimum(50.0);
  mg_ev->SetMaximum(100.0);
  mg_ev->Draw("AL");
  mg_ev->GetXaxis()->SetTitle("Photon energy, eV");
  mg_ev->GetYaxis()->SetTitle("Reflectance, %");
  //
  leg->Draw();
  //
  save_data_file("al_mirror_Reflectance_Unpolarized_ev.dat", gr_al_mirror_refl_Unpolarized_ev);
  save_data_file("al_mirror_Reflectance_P-polarized_ev.dat", gr_al_mirror_refl_Ppolarized_ev);
  save_data_file("al_mirror_Reflectance_S-polarized_ev.dat", gr_al_mirror_refl_Spolarized_ev);
  //FILE *fp01;
  //fp01 = fopen(outData_ABSORB_vs_eV.Data(), "w+");
  //fprintf(fp01, " ev        m \n");
  //for(int i=0; i<71; i++) {
  //Double_t x_nm,x,y;
  //x_nm = 1000 - 10*i;
  //x = f_nm_to_eV->Eval(x_nm);
  //y = gr_abs_ev->Eval(x);
  //fprintf(fp01, "%10.7f %10.7f \n",x,y);
  //}
  //fclose(fp01);
  //
  return gr_al_mirror_refl_Unpolarized_ev;
}

void load_data_file(TString fileInName, TGraph *gr_nm, TGraph *gr_ev){
  ifstream fileIn(fileInName.Data());
  Double_t lam;
  Double_t refl;
  Double_t eV;
  if(fileIn.is_open()){
    while(fileIn>>lam>>refl){
      eV = 1239.84/lam;
      gr_nm->SetPoint(gr_nm->GetN(),lam,refl);
      gr_ev->SetPoint(gr_ev->GetN(),eV,refl);
    }
    fileIn.close();
  }
  else{
    cout<<"Unable to open file \n";
  }
}

void save_data_file(TString fileOutName, TGraph *gr_ev){
  FILE *fp01;
  fp01 = fopen(fileOutName.Data(), "w+");
  fprintf(fp01, "        ev                   refl    \n");
  Double_t lam_min = 300;
  Double_t lam_max = 1000;
  Double_t ev_min = 1239.84/lam_max;
  Double_t ev_max = 1239.84/lam_min;
  Double_t ev;
  for(int i=0; i<100; i++) {
    ev = ev_min + (ev_max - ev_min)/99*i;
    fprintf(fp01, "%20.10f %20.10f \n",ev,gr_ev->Eval(ev)/100.0);
  }  
  fclose(fp01);
}
