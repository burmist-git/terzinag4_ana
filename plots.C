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

const Int_t nFiles = 42;
TString fileNarr[nFiles];

Int_t plots(){
  fileNarr[0]="./hist_v02.00.00/hist_terzina_theta_0.0deg.root";
  fileNarr[1]="./hist_v02.00.00/hist_terzina_theta_0.1deg.root";
  fileNarr[2]="./hist_v02.00.00/hist_terzina_theta_0.2deg.root";
  fileNarr[3]="./hist_v02.00.00/hist_terzina_theta_0.3deg.root";
  fileNarr[4]="./hist_v02.00.00/hist_terzina_theta_0.4deg.root";
  fileNarr[5]="./hist_v02.00.00/hist_terzina_theta_0.5deg.root";
  fileNarr[6]="./hist_v02.00.00/hist_terzina_theta_0.6deg.root";
  fileNarr[7]="./hist_v02.00.00/hist_terzina_theta_0.7deg.root";
  fileNarr[8]="./hist_v02.00.00/hist_terzina_theta_0.8deg.root";
  fileNarr[9]="./hist_v02.00.00/hist_terzina_theta_0.9deg.root";
  fileNarr[10]="./hist_v02.00.00/hist_terzina_theta_1.0deg.root";
  fileNarr[11]="./hist_v02.00.00/hist_terzina_theta_1.1deg.root";
  fileNarr[12]="./hist_v02.00.00/hist_terzina_theta_1.2deg.root";
  fileNarr[13]="./hist_v02.00.00/hist_terzina_theta_1.3deg.root";
  fileNarr[14]="./hist_v02.00.00/hist_terzina_theta_1.4deg.root";
  fileNarr[15]="./hist_v02.00.00/hist_terzina_theta_1.5deg.root";
  fileNarr[16]="./hist_v02.00.00/hist_terzina_theta_1.6deg.root";
  fileNarr[17]="./hist_v02.00.00/hist_terzina_theta_1.7deg.root";
  fileNarr[18]="./hist_v02.00.00/hist_terzina_theta_1.8deg.root";
  fileNarr[19]="./hist_v02.00.00/hist_terzina_theta_1.9deg.root";
  fileNarr[20]="./hist_v02.00.00/hist_terzina_theta_2.0deg.root";
  fileNarr[21]="./hist_v02.00.00/hist_terzina_theta_2.1deg.root";
  fileNarr[22]="./hist_v02.00.00/hist_terzina_theta_2.2deg.root";
  fileNarr[23]="./hist_v02.00.00/hist_terzina_theta_2.3deg.root";
  fileNarr[24]="./hist_v02.00.00/hist_terzina_theta_2.4deg.root";
  fileNarr[25]="./hist_v02.00.00/hist_terzina_theta_2.5deg.root";
  fileNarr[26]="./hist_v02.00.00/hist_terzina_theta_2.6deg.root";
  fileNarr[27]="./hist_v02.00.00/hist_terzina_theta_2.7deg.root";
  fileNarr[28]="./hist_v02.00.00/hist_terzina_theta_2.8deg.root";
  fileNarr[29]="./hist_v02.00.00/hist_terzina_theta_2.9deg.root";
  fileNarr[30]="./hist_v02.00.00/hist_terzina_theta_3.0deg.root";
  fileNarr[31]="./hist_v02.00.00/hist_terzina_theta_3.1deg.root";
  fileNarr[32]="./hist_v02.00.00/hist_terzina_theta_3.2deg.root";
  fileNarr[33]="./hist_v02.00.00/hist_terzina_theta_3.3deg.root";
  fileNarr[34]="./hist_v02.00.00/hist_terzina_theta_3.4deg.root";
  fileNarr[35]="./hist_v02.00.00/hist_terzina_theta_3.5deg.root";
  fileNarr[36]="./hist_v02.00.00/hist_terzina_theta_3.6deg.root";
  fileNarr[37]="./hist_v02.00.00/hist_terzina_theta_3.7deg.root";
  fileNarr[38]="./hist_v02.00.00/hist_terzina_theta_3.8deg.root";
  fileNarr[39]="./hist_v02.00.00/hist_terzina_theta_3.9deg.root";
  fileNarr[40]="./hist_v02.00.00/hist_terzina_theta_4.0deg.root";
  fileNarr[41]="./hist_v02.00.00/hist_terzina_theta_4.1deg.root";
  Double_t psf_95percent;
  Double_t psf_80percent;
  Double_t psf_65percent;
  Double_t psf_rms_radius;
  //
  Double_t posX_MaxVal;
  Double_t posY_MaxVal;
  //
  Double_t psf_95percent_arr[nFiles];
  Double_t psf_80percent_arr[nFiles];
  Double_t psf_65percent_arr[nFiles];
  Double_t psf_rms_radius_arr[nFiles];
  Double_t posX_MaxVal_arr[nFiles];
  Double_t posY_MaxVal_arr[nFiles];
  Double_t posX_MaxVal_arr_err[nFiles];
  Double_t posY_MaxVal_arr_err[nFiles];
  //
  Double_t theta_arr[nFiles];
  Double_t theta_arr_err[nFiles];
  //
  TString fileN;
  Bool_t toplot = false;
  for(Int_t i = 0;i<nFiles;i++){
  //for(Int_t i = 16;i<17;i++){
    theta_arr[i] = 0.1*i;
    theta_arr_err[i] = 0.0;
    fileN = fileNarr[i];
    //fileN = "./hist_v02.00.00/hist_terzina_theta_0.0deg.root";
    psf_culc(fileN, psf_95percent, psf_80percent, psf_65percent, psf_rms_radius, posX_MaxVal, posY_MaxVal, toplot);
    cout<<fileN<<endl;
    cout<<"psf_95percent  = "<<psf_95percent<<endl
	<<"psf_80percent  = "<<psf_80percent<<endl
	<<"psf_65percent  = "<<psf_65percent<<endl
    	<<"psf_rms_radius = "<<psf_rms_radius<<endl;
    psf_95percent_arr[i] = psf_95percent;
    psf_80percent_arr[i] = psf_80percent;
    psf_65percent_arr[i] = psf_65percent;
    psf_rms_radius_arr[i] = psf_rms_radius;
    posX_MaxVal_arr[i] = posX_MaxVal;
    posY_MaxVal_arr[i] = posY_MaxVal;
    posX_MaxVal_arr_err[i] = psf_80percent;
    posY_MaxVal_arr_err[i] = psf_80percent;
  }


  //TGraph *gr_95percent = new TGraph(nFiles,theta_arr,psf_95percent_arr);
  //TGraph *gr_80percent = new TGraph(nFiles,theta_arr,psf_80percent_arr);
  //TGraph *gr_65percent = new TGraph(nFiles,theta_arr,psf_65percent_arr);
  //
  TGraph *gr_95percent = new TGraph(nFiles-9,theta_arr,psf_95percent_arr);
  TGraph *gr_80percent = new TGraph(nFiles-9,theta_arr,psf_80percent_arr);
  TGraph *gr_65percent = new TGraph(nFiles-9,theta_arr,psf_65percent_arr);
  TGraph *gr_rms_radius = new TGraph(nFiles-9,theta_arr,psf_rms_radius_arr);

  //
  TGraphErrors *gr_xmax_pos = new TGraphErrors(nFiles-9,theta_arr,posX_MaxVal_arr,theta_arr_err,posX_MaxVal_arr_err);
  TGraphErrors *gr_ymax_pos = new TGraphErrors(nFiles-9,theta_arr,posY_MaxVal_arr,theta_arr_err,posY_MaxVal_arr_err);
  //
  gr_95percent->SetMarkerStyle(20);
  gr_80percent->SetMarkerStyle(20);
  gr_65percent->SetMarkerStyle(20);
  gr_rms_radius->SetMarkerStyle(21);
  //
  gr_95percent->SetMarkerColor(kRed);
  gr_80percent->SetMarkerColor(kBlack);
  gr_65percent->SetMarkerColor(kBlue+1);
  gr_rms_radius->SetMarkerColor(kGreen+2);
  //
  gr_95percent->SetLineColor(kRed);
  gr_80percent->SetLineColor(kBlack);
  gr_65percent->SetLineColor(kBlue+2);
  gr_rms_radius->SetLineColor(kGreen+2);
  //
  gr_95percent->SetLineWidth(3);
  gr_80percent->SetLineWidth(3);
  gr_65percent->SetLineWidth(3);
  gr_rms_radius->SetLineWidth(3);
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
  //
  gPad->SetGridx();
  gPad->SetGridy();
  //
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_95percent);
  mg->Add(gr_80percent);
  mg->Add(gr_65percent);
  mg->Add(gr_rms_radius);
  //mg->GetXaxis()->SetLimits(xMin,xMax);
  mg->Draw("APL");
  mg->SetMinimum(0.0);
  mg->SetMaximum(4.0);
  //mg->SetMaximum(6.0);
  //mg->SetMaximum(5.0);
  mg->GetXaxis()->SetTitle("#theta, deg");
  mg->GetYaxis()->SetTitle("PSF, mm");
  //  
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_95percent, "95 % of light", "pl");
  leg->AddEntry(gr_80percent, "80 % of light", "pl");
  leg->AddEntry(gr_65percent, "65 % of light", "pl");
  leg->AddEntry(gr_rms_radius, "rms of the light spot radius", "pl");
  leg->Draw();
  //
  TCanvas *c5 = new TCanvas("c5","c5",10,10,1000,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  //
  c5->SetRightMargin(0.02);
  c5->SetLeftMargin(0.08);
  c5->SetTopMargin(0.02);
  c5->SetBottomMargin(0.08);
  //
  gPad->SetGridx();
  gPad->SetGridy();
  //
  gr_xmax_pos->Fit("pol1","Q","",0.0,3.2);
  gr_xmax_pos->SetTitle("");
  gr_xmax_pos->GetXaxis()->SetLimits(-0.5,3.5);
  gr_xmax_pos->SetMarkerStyle(20);
  gr_xmax_pos->SetLineWidth(2);
  gr_xmax_pos->Draw("APL");
  gr_xmax_pos->GetXaxis()->SetTitle("#theta, deg");
  gr_xmax_pos->GetYaxis()->SetTitle("Centre of gravity, mm");
  //
  //POEMMA DATA
  //
  Double_t poemma_theta[18];
  Double_t poemma_rms_radius[18];
  poemma_theta[0]=0;                   poemma_rms_radius[0]=1;
  poemma_theta[1]=0.6219512195121961;  poemma_rms_radius[1]=1;
  poemma_theta[2]=1.9390243902439046;  poemma_rms_radius[2]=0.9554140127388533;
  poemma_theta[3]=2.926829268292682;   poemma_rms_radius[3]=0.8980891719745223;
  poemma_theta[4]=4.134146341463415;   poemma_rms_radius[4]=0.8726114649681525;
  poemma_theta[5]=5.487804878048783;   poemma_rms_radius[5]=0.9235668789808917;
  poemma_theta[6]=6.951219512195122;   poemma_rms_radius[6]=1.0700636942675161;
  poemma_theta[7]=7.79268292682927;    poemma_rms_radius[7]=1.1528662420382165;
  poemma_theta[8]=8.890243902439027;   poemma_rms_radius[8]=1.2611464968152868;
  poemma_theta[9]=10.207317073170733;  poemma_rms_radius[9]=1.3566878980891721;
  poemma_theta[10]=11.451219512195125; poemma_rms_radius[10]=1.4267515923566878;
  poemma_theta[11]=12.98780487804878;  poemma_rms_radius[11]=1.4904458598726116;
  poemma_theta[12]=14.597560975609758; poemma_rms_radius[12]=1.5286624203821655;
  poemma_theta[13]=16.317073170731703; poemma_rms_radius[13]=1.4968152866242037;
  poemma_theta[14]=17.890243902439025; poemma_rms_radius[14]=1.407643312101911;
  poemma_theta[15]=19.646341463414636; poemma_rms_radius[15]=1.4522292993630572;
  poemma_theta[16]=21.07317073170732;  poemma_rms_radius[16]=1.535031847133758;
  poemma_theta[17]=22.5;               poemma_rms_radius[17]=1.6433121019108279;
  //
  TGraph *gr_poemma_rms_radius = new TGraph(18,poemma_theta,poemma_rms_radius);
  gr_poemma_rms_radius->SetMarkerStyle(20);
  gr_poemma_rms_radius->SetMarkerColor(kBlack);
  gr_poemma_rms_radius->SetLineColor(kBlack);
  gr_poemma_rms_radius->SetLineWidth(3.0);
  //
  TCanvas *c6 = new TCanvas("c6","c6",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  //
  c6->SetRightMargin(0.01);
  c6->SetLeftMargin(0.08);
  c6->SetTopMargin(0.01);
  c6->SetBottomMargin(0.08);
  //
  gPad->SetGridx();
  gPad->SetGridy();
  //
  TMultiGraph *mg_po = new TMultiGraph();
  mg_po->Add(gr_poemma_rms_radius);
  mg_po->Add(gr_rms_radius);
  //mg->GetXaxis()->SetLimits(xMin,xMax);
  mg_po->Draw("APL");
  mg_po->SetMinimum(0.0);
  mg_po->SetMaximum(2.0);
  //mg->SetMaximum(6.0);
  //mg->SetMaximum(5.0);
  mg_po->GetXaxis()->SetTitle("#theta, deg");
  mg_po->GetYaxis()->SetTitle("RMS spot radius, mm");
  //  
  TLegend *leg_po = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg_po->AddEntry(gr_poemma_rms_radius, "POEMMA", "pl");
  leg_po->AddEntry(gr_rms_radius,        "Terzina", "pl");
  leg_po->Draw();
  //  
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

  Double_t window_dim = 1.5;
  //  
  //Double_t x_PosX_MaxVal = h1_5->GetBinCenter(h1_5->GetMaximumBin());
  Double_t x_PosX_MaxVal = h1_5->GetMean();
  Double_t x_PosX_RangeMin = x_PosX_MaxVal - window_dim;
  Double_t x_PosX_RangeMax = x_PosX_MaxVal + window_dim;
  posX_MaxVal = x_PosX_MaxVal;
  //  
  //Double_t x_PosY_MaxVal = h1_6->GetBinCenter(h1_6->GetMaximumBin());
  Double_t x_PosY_MaxVal = h1_6->GetMean();
  Double_t x_PosY_RangeMin = x_PosY_MaxVal - window_dim;
  Double_t x_PosY_RangeMax = x_PosY_MaxVal + window_dim;
  posY_MaxVal = x_PosY_MaxVal;

  cout<<"posX_MaxVal "<<posX_MaxVal<<endl
      <<"posY_MaxVal "<<posY_MaxVal<<endl;
  
  //////////////////////////////////////////////////////
  TH1D *h1_integral_PSF = new TH1D(*h1_PSF);
  Double_t norm = h1_5->Integral(0,h1_5->GetNbinsX());
  IntegrateInR_PSF(h1_integral_PSF, h1_PSF, norm);
  h1_integral_PSF->SetLineColor(kBlack);
  h1_integral_PSF->SetLineWidth(3.0);
  h1_integral_PSF->SetTitle("Number of photons vs circle radius.");
  h1_integral_PSF->GetXaxis()->SetTitle("r, mm");
  psf_95percent = getPSF_r(h1_integral_PSF,0.95);
  psf_80percent = getPSF_r(h1_integral_PSF,0.80);
  psf_65percent = getPSF_r(h1_integral_PSF,0.65);
  psf_rms_radius = h1_PSF->GetRMS();
  //cout<<"psf_rms_radius == "<<psf_rms_radius<<endl;
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
  for(Int_t i = 0;i<h1_r->GetNbinsX();i++)
    h1_integral_PSF->SetBinContent(i,h1_r->Integral(0,i)/norm);
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
