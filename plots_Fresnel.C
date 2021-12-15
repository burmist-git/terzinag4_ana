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

void IntegrateInR_PSF(TH1D *h1_integral_PSF, TH1D *h1_r, Double_t norm);
Double_t getPSF_r(TH1D *h1, Double_t val);
void psf_culc(TString fileN, Double_t &psf_95percent, Double_t &psf_80percent, Double_t &psf_65percent, Double_t &psf_rms_radius, Double_t &posX_MaxVal, Double_t &posY_MaxVal, Bool_t toplot);
TString round_o(float var);

Int_t plots_Fresnel(){

  TString rootHistfileIn;
  //rootHistfileIn = "./hist_fresnel/hist_terzina_1e.7_n25_spectrum_full_0.0deg.root";
  //rootHistfileIn = "./hist_fresnel/hist_terzina_1e.7_n25_spectrum_full_1.0deg.root";

  //rootHistfileIn = "./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_0.0deg.root";
  //rootHistfileIn = "./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_1.0deg.root";
  //rootHistfileIn = "./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_2.0deg.root";
  //rootHistfileIn = "./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_3.0deg.root";
  //rootHistfileIn = "./hist_fresnel/hist_terzina_1e.7_n100_spectrum_400_4.0deg.root";
  rootHistfileIn = "./hist_fresnel/hist_terzina_1e.7_n25_spectrum_full_2.0deg.root";
    
  Double_t psf_95percent;
  Double_t psf_80percent;
  Double_t psf_65percent;
  Double_t psf_rms_radius;
  //
  Double_t posX_MaxVal;
  Double_t posY_MaxVal;
  //
  Bool_t toplot = true;
  psf_culc( rootHistfileIn, psf_95percent, psf_80percent, psf_65percent, psf_rms_radius, posX_MaxVal, posY_MaxVal, toplot);
  cout<<rootHistfileIn<<endl;
  cout<<"psf_95percent  = "<<psf_95percent<<endl
      <<"psf_80percent  = "<<psf_80percent<<endl
      <<"psf_65percent  = "<<psf_65percent<<endl
      <<"psf_rms_radius = "<<psf_rms_radius<<endl;
  return 0;
}

void psf_culc(TString fileN, Double_t &psf_95percent, Double_t &psf_80percent, Double_t &psf_65percent, Double_t &psf_rms_radius, Double_t &posX_MaxVal, Double_t &posY_MaxVal, Bool_t toplot){

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

  //fileN = "./hist_v02.00.00b/hist_terzina.root";
  //fileN = "./hist_v02.00.00b/hist_terzina_theta_0deg.root";
  //fileN = "./hist_v02.00.00b/hist_terzina_theta_1deg.root";
  //fileN = "./hist_v02.00.00b/hist_terzina_theta_2deg.root";
  //fileN = "./hist_v02.00.00b/hist_terzina_theta_3deg.root";

  //fileN = "./hist_v02.00.00/hist_terzina_theta_3.6deg.root";

  TFile *f1 = new TFile(fileN.Data());

  TH2D *h2_1 = (TH2D*)f1->Get("h2_primPosY_vs_primPosX");
  TH1D *h1_2 = (TH1D*)f1->Get("h1_thetaPhotons_deg");
  TH1D *h1_3 = (TH1D*)f1->Get("h1_phiPhotons_deg");
  TH1D *h1_41 = (TH1D*)f1->Get("h1_Time_nocut");
  TH1D *h1_42 = (TH1D*)f1->Get("h1_Time");
    
  TH1D *h1_5 = (TH1D*)f1->Get("h1_PosX");
  TH1D *h1_6 = (TH1D*)f1->Get("h1_PosY");
  TH2D *h2_7 = (TH2D*)f1->Get("h2_PosY_vs_PosX");
  //TH2D *h2_8 = (TH2D*)f1->Get("h2_PosY_vs_PosX_forzoom");
  TH2D *h2_8 = (TH2D*)f1->Get("h2_PosY_vs_PosX_recentrate");
  //TH2D *h2_6 = (TH2D*)f1->Get("h2_PosY_vs_PosX_single");
  //
  TH1D *h1_PSF = (TH1D*)f1->Get("h1_R_PSF");
  TH1D *h1_wl = (TH1D*)f1->Get("h1_Wavelength");
  //  
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_Time");
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_PosX");
  //TH1D *h1_1 = (TH1D*)f1->Get("h1_PosX_cut");
  
  //h1_1->Rebin(4);
  //h1_1->SetTitle("");

  Double_t window_dim = 10.0;
  //  
  //Double_t x_PosX_MaxVal = 32.0;
  Double_t x_PosX_MaxVal = h1_5->GetBinCenter(h1_5->GetMaximumBin());
  //Double_t x_PosX_MaxVal = h1_5->GetMean();
  Double_t x_PosX_RangeMin = x_PosX_MaxVal - window_dim;
  Double_t x_PosX_RangeMax = x_PosX_MaxVal + window_dim;
  posX_MaxVal = x_PosX_MaxVal;
  //  
  //Double_t x_PosY_MaxVal = 0.0;
  Double_t x_PosY_MaxVal = h1_6->GetBinCenter(h1_6->GetMaximumBin());
  //Double_t x_PosY_MaxVal = h1_6->GetMean();
  Double_t x_PosY_RangeMin = x_PosY_MaxVal - window_dim;
  Double_t x_PosY_RangeMax = x_PosY_MaxVal + window_dim;
  posY_MaxVal = x_PosY_MaxVal;

  cout<<"posX_MaxVal "<<posX_MaxVal<<endl
      <<"posY_MaxVal "<<posY_MaxVal<<endl;
  
  //////////////////////////////////////////////////////
  TH1D *h1_integral_PSF = new TH1D(*h1_PSF);
  Double_t norm = h1_5->Integral(1,(h1_5->GetNbinsX()-1));
  cout<<"norm = "<<norm<<endl;
  IntegrateInR_PSF(h1_integral_PSF, h1_PSF, norm);
  h1_integral_PSF->SetLineColor(kBlack);
  h1_integral_PSF->SetLineWidth(3.0);
  h1_integral_PSF->SetTitle("Number of photons vs circle radius.");
  h1_integral_PSF->GetXaxis()->SetTitle("r, mm");
  psf_95percent = getPSF_r(h1_integral_PSF,0.95);
  psf_80percent = getPSF_r(h1_integral_PSF,0.80);
  psf_65percent = getPSF_r(h1_integral_PSF,0.65);
  psf_rms_radius = h1_PSF->GetRMS();
  cout<<"psf_rms_radius = "<<psf_rms_radius<<endl;
  //////////////////////////////////////////////////////
  
  if(toplot){
    TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,1400,1050);
    //TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,600,600);
    gStyle->SetPalette(1);
    gStyle->SetFrameBorderMode(0);
    gROOT->ForceStyle();
    gStyle->SetStatColor(kWhite);
    gStyle->SetOptStat(kFALSE);
    //
    //h1_1->SetLineColor(kBlack);
    //h1_1->SetLineWidth(3.0);
    h1_2->SetLineColor(kBlack);
    h1_2->SetLineWidth(3.0);
    //
    h1_3->SetLineColor(kBlack);
    h1_3->SetLineWidth(3.0);
    //
    h1_41->SetLineColor(kBlack);
    h1_41->SetLineWidth(3.0);
    //
    h1_42->SetLineColor(kRed);
    h1_42->SetLineWidth(3.0);
    //
    h1_5->SetLineColor(kBlack);
    h1_5->SetLineWidth(3.0);
    //
    h1_6->SetLineColor(kBlack);
    h1_6->SetLineWidth(3.0);
    //
    h1_PSF->SetLineColor(kBlack);
    h1_PSF->SetLineWidth(3.0);
    //
    c1->Divide(4,3);
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
    gPad->SetLogy();
    h1_41->Draw();
    h1_42->Draw("same");
    c1->cd(5);
    gPad->SetGridx();
    gPad->SetGridy();
    h1_5->Draw();
    h1_5->GetXaxis()->SetRangeUser(x_PosX_RangeMin,x_PosX_RangeMax);
    c1->cd(6);
    gPad->SetGridx();
    gPad->SetGridy();
    h1_6->Draw();
    h1_6->GetXaxis()->SetRangeUser(x_PosY_RangeMin,x_PosY_RangeMax);
    c1->cd(7);
    gPad->SetGridx();
    gPad->SetGridy();
    gPad->SetLogz();
    h2_7->Draw("ZCOLOR");
    //
    c1->cd(8);
    gPad->SetGridx();
    gPad->SetGridy();
    gPad->SetLogz();
    h2_8->Draw("ZCOLOR");
    h2_8->GetXaxis()->SetRangeUser(x_PosX_RangeMin,x_PosX_RangeMax);
    h2_8->GetYaxis()->SetRangeUser(x_PosY_RangeMin,x_PosY_RangeMax);
    //
    h2_1->GetXaxis()->SetTitle("Primary position x, mm");
    h2_1->GetYaxis()->SetTitle("Primary position y, mm");
    h1_2->GetXaxis()->SetTitle("Primary #theta, deg");
    h1_3->GetXaxis()->SetTitle("Primary #phi, deg");
    h1_41->GetXaxis()->SetTitle("Time, ns");
    h1_42->GetXaxis()->SetTitle("Time, ns");
    h1_5->GetXaxis()->SetTitle("x in projection plane, mm");
    h1_6->GetXaxis()->SetTitle("y in projection plane, mm");
    h2_7->GetXaxis()->SetTitle("x in projection plane, mm");
    h2_7->GetYaxis()->SetTitle("y in projection plane, mm");
    h2_8->GetXaxis()->SetTitle("x in projection plane, mm");
    h2_8->GetYaxis()->SetTitle("y in projection plane, mm");
    //
    //h2_1->GetXaxis()->SetRangeUser(-0.13,-0.12);
    c1->cd(9);
    gPad->SetGridx();
    gPad->SetGridy();
    h1_wl->SetLineColor(kBlack);
    h1_wl->SetLineWidth(3.0);
    h1_wl->GetXaxis()->SetTitle("wavelength, nm");
    h1_wl->Draw();
    //
    c1->cd(10);
    gPad->SetGridx();
    gPad->SetGridy();
    //gPad->SetLogz();
    h2_8->Draw("ZCOLOR");
    Int_t nnjj = 100;
    for(Int_t jj = 0;jj<nnjj;jj++){
      TVector2 *v = new TVector2();
      Double_t phi = 2.0*TMath::Pi()/nnjj*jj;
      v->SetMagPhi(getPSF_r(h1_integral_PSF,0.80),phi);
      //v->SetMagPhi(getPSF_r(h1_integral_PSF,0.65),phi);
      TLine *l1 = new TLine(v->X()+x_PosX_MaxVal,
			    v->Y()+x_PosY_MaxVal,
			    v->Rotate(TMath::Pi()/nnjj*2.0).X()+x_PosX_MaxVal,
			    v->Rotate(TMath::Pi()/nnjj*2.0).Y()+x_PosY_MaxVal);
      l1->SetLineWidth(2.0);
      //l1->SetLineColor(kMagenta+2);
      l1->Draw("same");
    }
    //
    c1->cd(11);
    gPad->SetGridx();
    gPad->SetGridy();
    h1_PSF->SetTitle("Radius (center is taken from mean of the dis.)");
    h1_PSF->Draw();
    h1_PSF->GetXaxis()->SetTitle("r, mm");
    TString ttex_data_radious = "RMS : ";
    ttex_data_radious += round_o((float)h1_PSF->GetRMS());
    TText *t_radious = new TText(6,h1_PSF->GetMaximum() - h1_PSF->GetMaximum()/10.0, ttex_data_radious.Data());
    t_radious->SetTextSize(0.05);
    t_radious->Draw();
    TString ttex_data_entries = "Entries : ";
    ttex_data_entries += round_o((float)h1_PSF->GetEntries());
    TText *t_entries = new TText(6,h1_PSF->GetMaximum() - 2*h1_PSF->GetMaximum()/10.0, ttex_data_entries.Data());
    t_entries->SetTextSize(0.05);
    t_entries->Draw();
    //    
    c1->cd(12);
    gPad->SetGridx();
    gPad->SetGridy();
    h1_integral_PSF->SetMinimum(0.0);
    h1_integral_PSF->SetMaximum(1.1);
    h1_integral_PSF->Draw();
    TString ttex_data_psf_95 = "PSF @ 95 : ";
    TString ttex_data_psf_80 = "PSF @ 80 : ";
    TString ttex_data_psf_65 = "PSF @ 65 : ";
    ttex_data_psf_95 += round_o((float)psf_95percent);
    ttex_data_psf_80 += round_o((float)psf_80percent);
    ttex_data_psf_65 += round_o((float)psf_65percent);
    TText *t_psf_95 = new TText(5, 0.9, ttex_data_psf_95.Data());
    TText *t_psf_80 = new TText(5, 0.8, ttex_data_psf_80.Data());
    TText *t_psf_65 = new TText(5, 0.7, ttex_data_psf_65.Data());
    t_psf_95->SetTextSize(0.05);
    t_psf_80->SetTextSize(0.05);
    t_psf_65->SetTextSize(0.05);
    t_psf_95->Draw();
    t_psf_80->Draw();
    t_psf_65->Draw();
    TString filePdfN = fileN;
    filePdfN += ".pdf";
    c1->SaveAs(filePdfN.Data());
  }
    
  if(toplot){
  //if(false){
    TCanvas *c2 = new TCanvas("c2",fileN.Data(),10,10,1500,500);
    gStyle->SetPalette(1);
    gStyle->SetFrameBorderMode(0);
    gROOT->ForceStyle();
    gStyle->SetStatColor(kWhite);
    //gStyle->SetOptStat(kFALSE);
    c2->Divide(3,1);
    c2->cd(1);
    gPad->SetGridx();
    gPad->SetGridy();
    gPad->SetLogz();
    h2_8->Draw("ZCOLOR");
    c2->cd(2);
    gPad->SetGridx();
    gPad->SetGridy();
    h1_PSF->SetTitle("Radius (center is taken from maximum of the dis.)");
    h1_PSF->Draw();
    h1_PSF->GetXaxis()->SetTitle("r, mm");
    //
    c2->cd(3);
    gPad->SetGridx();
    gPad->SetGridy();
    h1_integral_PSF->Draw();
  }
  //--------------------------------------------------
  if(toplot){ 
  //if(false){
    TCanvas *c3 = new TCanvas("c3",fileN.Data(),10,10,1900,475);
    gStyle->SetPalette(1);
    gStyle->SetFrameBorderMode(0);
    gROOT->ForceStyle();
    gStyle->SetOptStat(kFALSE);
    c3->Divide(4,1);
    //
    c3->cd(1);
    gPad->SetGridx();
    gPad->SetGridy();
    h1_wl->SetLineColor(kBlack);
    h1_wl->SetLineWidth(3.0);
    h1_wl->GetXaxis()->SetTitle("wavelength, nm");
    h1_wl->Draw();
    //
    c3->cd(2);
    gPad->SetGridx();
    gPad->SetGridy();
    //gPad->SetLogz();
    h2_8->Draw("ZCOLOR");
    Int_t nnjj = 100;
    for(Int_t jj = 0;jj<nnjj;jj++){
      TVector2 *v = new TVector2();
      Double_t phi = 2.0*TMath::Pi()/nnjj*jj;
      v->SetMagPhi(getPSF_r(h1_integral_PSF,0.80),phi);
      TLine *l1 = new TLine(v->X()+x_PosX_MaxVal,
			    v->Y()+x_PosY_MaxVal,
			    v->Rotate(TMath::Pi()/nnjj*2.0).X()+x_PosX_MaxVal,
			    v->Rotate(TMath::Pi()/nnjj*2.0).Y()+x_PosY_MaxVal);
      l1->SetLineWidth(2.0);
      //l1->SetLineColor(kMagenta+2);
      l1->Draw("same");
    }
    //
    c3->cd(3);
    gPad->SetGridx();
    gPad->SetGridy();
    h1_PSF->SetTitle("Radius (center is taken from maximum of the dis.)");
    h1_PSF->Draw();
    h1_PSF->GetXaxis()->SetTitle("r, mm");
    //Double_t rms_psf_r = roundf(h1_PSF->GetRMS() * 1000) / 1000;
    //printf("%.2f", 37.777779);
    //Double_t rms_psf_r =  ceilf(h1_PSF->GetRMS() * 100) / 100;
    //Double_t rms_psf_r = h1_PSF->GetRMS();
    //Double_t rms_psf_r = ;
    TString ttex_data = "RMS : ";
    ttex_data += round_o((float)h1_PSF->GetRMS());
    TText *t21 = new TText(6,h1_PSF->GetMaximum() - h1_PSF->GetMaximum()/10.0, ttex_data.Data());
    t21->SetTextSize(0.05);
    t21->Draw();
    //    
    c3->cd(4);
    gPad->SetGridx();
    gPad->SetGridy();
    h1_integral_PSF->Draw();
  }
  //
  //cout<<"psf_95percent = "<<psf_95percent<<endl
  //  <<"psf_80percent = "<<psf_80percent<<endl
  //    <<"psf_65percent = "<<psf_65percent<<endl;
  //
  //TGraph *gr_PSF = new TGraph();
  //
  //cout<<"x_PosX_MaxVal "<<x_PosX_MaxVal<<endl
  //    <<"x_PosY_MaxVal "<<x_PosY_MaxVal<<endl;
  //
  //calculatePSF(gr_PSF, h2_6,x_PosX_MaxVal,x_PosY_MaxVal,1000,0.0,10.0);
  //gr_PSF->Draw("APL");
    
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
}

void IntegrateInR_PSF(TH1D *h1_integral_PSF, TH1D *h1_r, Double_t norm){
  for(Int_t i = 1;i<(h1_r->GetNbinsX()-1);i++)
    h1_integral_PSF->SetBinContent(i,h1_r->Integral(1,i)/norm);
}

Double_t getPSF_r(TH1D *h1, Double_t val){
  Int_t nn = h1->GetNbinsX();
  Double_t yl;
  Double_t yr;
  for (Int_t i=0;i<nn;i++){
    yl = h1->GetBinContent(i);
    yr = h1->GetBinContent(i+1);
    if(yl < val && yr>= val)
      return h1->GetBinCenter(i+1);
  }
  return 10.0;
}

TString round_o(float var){
  //float val = 37.777779;
  //float rounded_down = floorf(val * 100) / 100;   //Result: 37.77
  //float nearest      = roundf(val * 100) / 100;   //Result: 37.78
  //float rounded_up   = ceilf(val  * 100) / 100;   //Result: 37.78
  char str[40];
    sprintf(str, "%.3f", var);
    TString str_var = str;
    return str_var;
}
