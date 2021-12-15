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

struct lens_tangent_info_str {
  //
  Double_t R;
  Double_t f;
  Double_t Theta;
  Double_t Beta;
  Double_t Alpha;
  //
  Bool_t tang_is_ok;
  lens_tangent_info_str(){
    R = -999.0;
    f = -999.0;
    Theta = -999.0;
    Beta = -999.0;
    Alpha = -999.0;
    //
    tang_is_ok = false;
  }
  void print_info(){
    cout<<"R       "<<R<<endl
	<<"f       "<<f<<endl
        <<"Theta   "<<Theta<<endl;
    cout<<"Beta    "<<Beta<<endl
        <<"Alpha   "<<Alpha<<endl;
  }   
};

TString file_info_fresnel_lens_shape;

void get_lens_shape(TGraph *gr_lens_shape, Double_t lens_R, Double_t lens_n, Double_t lens_f, Int_t n);
void get_fresnel_lens_shape(TGraph *gr_lens_shape, Double_t lens_R, Double_t lens_n, Double_t lens_f, Int_t n);
Bool_t get_lens_tangent(Double_t R, Double_t f, Double_t n, lens_tangent_info_str *lens_tangent_info);

Int_t normal_lens_fresnel_lens(){
  //
  ////////////////////////////////////////////////
  Double_t lens_n = 1.47;
  Double_t lens_f = 400.0; // mm
  Double_t lens_R = 270.0; // mm
  Int_t nn = 25;
  ///////////////////////////////////////////////
  Double_t R;
  //
  Double_t l = 700;
  Double_t xC = 0;
  Double_t yC = 100;
  Double_t xMin = xC - l/2.0;
  Double_t xMax = xC + l/2.0;
  //
  Double_t yMin = yC - l/2.0;
  Double_t yMax = yC + l/2.0;
  //
  ///////////////////////////////////////////////
  //
  TGraph *gr_lens_shape = new TGraph();
  //get_lens_shape(gr_lens_shape, lens_R, lens_n, lens_f, nn);
  file_info_fresnel_lens_shape = "./fresnel_lens_shape_R270_f400_n25.dat";
  get_fresnel_lens_shape(gr_lens_shape, lens_R, lens_n, lens_f, nn);
  //
  TCanvas *c1 = new TCanvas("c1","c2",10,10,800,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  c1->SetRightMargin(0.02);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.02);
  c1->SetBottomMargin(0.1);
  //
  gPad->SetGridx();
  gPad->SetGridy();
  //
  //gr_lens_shape->GetXaxis()->SetLimits(xMin,xMax);
  //gr_lens_shape->Draw("AP");
  //gr_lens_shape->GetYaxis()->SetRangeUser(yMin,yMax);  
  //
  gr_lens_shape->SetMarkerColor(kBlack);
  //gr_lens_shape->SetMarkerStyle(20);
  gr_lens_shape->SetMarkerStyle(7);
  //
  //gr_lens_shape->GetXaxis()->SetTitle("lens r, mm");
  //gr_lens_shape->GetYaxis()->SetTitle("thickness, mm");
  //
  TGraph *gr_support = new TGraph();
  gr_support->SetPoint(gr_support->GetN(),0.0,lens_f);
  gr_support->SetMarkerStyle(20);
  gr_support->SetLineColor(kRed);
  gr_support->SetMarkerColor(kRed);
  //
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_lens_shape);
  mg->Add(gr_support);
  //
  mg->GetXaxis()->SetLimits(xMin,xMax);
  mg->Draw("AP");
  mg->GetYaxis()->SetRangeUser(yMin,yMax);  
  mg->GetXaxis()->SetTitle("lens r, mm");
  mg->GetYaxis()->SetTitle("thickness, mm");
  //  
  return 0;
}

void get_lens_shape(TGraph *gr_lens_shape, Double_t lens_R, Double_t lens_n, Double_t lens_f, Int_t n){
  //
  Double_t Rmax = lens_R;           // mm
  Double_t Rmin = 1.0;              // mm
  Double_t dR   = (Rmax - Rmin)/n;  // mm
  Double_t R;
  Double_t f;
  Double_t df = 0.0;
  //
  vector<lens_tangent_info_str*> v_lens_tangent_info_str;
  //
  lens_tangent_info_str *lens_tangent_info_zero = new lens_tangent_info_str();
  if(get_lens_tangent( lens_R, lens_f, lens_n, lens_tangent_info_zero))
    v_lens_tangent_info_str.push_back(lens_tangent_info_zero);
  gr_lens_shape->SetPoint(gr_lens_shape->GetN(), lens_R, lens_f-lens_f);
  gr_lens_shape->SetPoint(gr_lens_shape->GetN(),-lens_R, lens_f-lens_f);
  //
  gr_lens_shape->SetPoint(gr_lens_shape->GetN(), lens_R, -lens_f-lens_f);
  gr_lens_shape->SetPoint(gr_lens_shape->GetN(),-lens_R, -lens_f-lens_f);
  //
  for(Int_t i = 1; i<n; i++){
    lens_tangent_info_str *lens_tangent_info = new lens_tangent_info_str();
    R = Rmax - dR*i;
    if(TMath::Tan(v_lens_tangent_info_str.at(i-1)->Alpha) != 0.0){
      df = df + dR/TMath::Tan(v_lens_tangent_info_str.at(i-1)->Alpha);
      f = lens_f - df;
      if(get_lens_tangent( R, f, lens_n, lens_tangent_info)){
	v_lens_tangent_info_str.push_back(lens_tangent_info);
	gr_lens_shape->SetPoint(gr_lens_shape->GetN(),R,df);
	gr_lens_shape->SetPoint(gr_lens_shape->GetN(),-R,df);
	//
	gr_lens_shape->SetPoint(gr_lens_shape->GetN(), R,-df);
	gr_lens_shape->SetPoint(gr_lens_shape->GetN(),-R,-df);
      }
    }
    else
      lens_tangent_info->tang_is_ok = false;
  }
  for(unsigned int i = 0;i<v_lens_tangent_info_str.size();i++){
    v_lens_tangent_info_str.at(i)->print_info();
  }
}

void get_fresnel_lens_shape(TGraph *gr_lens_shape, Double_t lens_R, Double_t lens_n, Double_t lens_f, Int_t n){
  //
  Double_t Rmax = lens_R;           // mm
  Double_t Rmin = 0.0;              // mm
  Double_t dR   = (Rmax - Rmin)/n;  // mm
  Double_t R;
  Double_t dl = 0.0;
  Double_t lens_substrate_thickness = 5.0; //mm
  Double_t x1,x2,y1,y2,x,y;
  Double_t k,b;
  Int_t nii = 100;
  //
  vector<lens_tangent_info_str*> v_lens_tangent_info_str;
  cout<<"file_info_fresnel_lens_shape = "<<file_info_fresnel_lens_shape<<endl;
  FILE *fp01;
  fp01 = fopen(file_info_fresnel_lens_shape.Data(), "w+");
  fprintf(fp01, "lens_R = %10.5f \n",lens_R);
  fprintf(fp01, "lens_n = %10.5f \n",lens_n);
  fprintf(fp01, "lens_f = %10.5f \n",lens_f);
  fprintf(fp01, "n      = %10d \n",n);
  fprintf(fp01, "substr = %10.5f \n",lens_substrate_thickness);
  //
  for(Int_t i = 0; i<n; i++){
    R = Rmax - dR*i;
    lens_tangent_info_str *lens_tangent_info = new lens_tangent_info_str();
    if(get_lens_tangent( R, lens_f, lens_n, lens_tangent_info)){
      v_lens_tangent_info_str.push_back(lens_tangent_info);
      if(TMath::Tan(lens_tangent_info->Alpha) != 0.0){
	dl = dR/TMath::Tan(v_lens_tangent_info_str.at(i)->Alpha);
	x1 = lens_substrate_thickness;
	x2 = x1 + dl;
	y1 = R;
	y2 = R-dR;
	k = (y2 - y1)/(x2-x1);
	b = y1 - k*x1;
	fprintf(fp01, "%10d %10.5f %10.5f %10.5f %10.5f \n",i,x1,y1,x2,y2);
	//
	for(Int_t ii = 0;ii<nii;ii++){
	  x = (x2 - x1)/(nii-1)*ii+x1;
	  y = k*x+b;
	  gr_lens_shape->SetPoint(gr_lens_shape->GetN(),y,x);
	}
	for(Int_t ii = 0;ii<100;ii++){
	  x = (x2 - x1)/(100-1)*ii+x1;
	  gr_lens_shape->SetPoint(gr_lens_shape->GetN(),y2,x);
	}	
	//
	y1 = -y1;
	y2 =  y1 + dR;
	k = (y2 - y1)/(x2-x1);
	b = y1 - k*x1;
	for(Int_t ii = 0;ii<nii;ii++){
	  x = (x2 - x1)/(nii-1)*ii+x1;
	  y = k*x+b;
	  gr_lens_shape->SetPoint(gr_lens_shape->GetN(),y,x);
	}
	for(Int_t ii = 0;ii<100;ii++){
	  x = (x2 - x1)/(100-1)*ii+x1;
	  gr_lens_shape->SetPoint(gr_lens_shape->GetN(),y2,x);
	}
      }
      //
      for(Int_t ii = 0;ii<100;ii++){
	y = (lens_substrate_thickness - 0)/(100-1)*ii+0;
	gr_lens_shape->SetPoint(gr_lens_shape->GetN(),lens_R,y);
	gr_lens_shape->SetPoint(gr_lens_shape->GetN(),-lens_R,y);
      }	
      //
      for(Int_t ii = 0;ii<1000;ii++){
	x = (lens_R + lens_R)/(1000-1)*ii-lens_R;
	gr_lens_shape->SetPoint(gr_lens_shape->GetN(),x,0);
      }	
    }
    else
      lens_tangent_info->tang_is_ok = false;
  }
  fclose(fp01);
  //for(unsigned int i = 0;i<v_lens_tangent_info_str.size();i++){
  //v_lens_tangent_info_str.at(i)->print_info();
  //}
}

Bool_t get_lens_tangent(Double_t R, Double_t f, Double_t n, lens_tangent_info_str *lens_tangent_info){
  if(R <= 0.0)
    return false;
  if(n <= 1.0)
    return false;
  //
  Double_t theta   = TMath::Pi()/2.0 - TMath::ATan(f/R);
  Double_t tg_beta = TMath::Sin(theta)/(n - TMath::Cos(theta));
  Double_t beta    = TMath::ATan(tg_beta);
  Double_t alpha   = TMath::Pi()/2.0 - beta;
  //
  lens_tangent_info->R = R;
  lens_tangent_info->f = f;
  lens_tangent_info->Theta = theta;
  lens_tangent_info->Beta = beta;
  lens_tangent_info->Alpha = alpha;
  //
  lens_tangent_info->tang_is_ok = true;
  //
  return true;
}
