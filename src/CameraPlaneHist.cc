//my
#include "CameraPlaneHist.hh"

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <math.h>
#include <vector>

//root
#include <TVector2.h>
#include <TPolyLine.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TText.h>
#include <TMath.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TCrown.h>
#include <TArc.h>
#include <TROOT.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <TPad.h>
#include <TString.h>
#include <TFile.h>
#include <TAxis.h>
#include <TVector2.h>
#include <TImage.h>

using namespace std;

CameraPlaneHist::CameraPlaneHist(const char* name, const char* title) : TH2Poly()
{
  //
  SetName(name);
  SetTitle(title);
  //SetName("");
  //SetTitle("");

  Int_t nSide = 4;
  Int_t nAdditionalePoints = 5;
  Int_t n = nAdditionalePoints*nSide + nSide + 1;

  Double_t* x;
  Double_t* y;
  x = new Double_t [n];
  y = new Double_t [n];

  //Double_t focus_eff = 0.93/1000.0;   //km
  //Double_t dist_eff = 2640.0;         //km
  //
  //Double_t sipm_array_L = 25.3;                    //mm
  //Double_t sipm_array_L_eff = 24.0;                //mm
  //Double_t sipm_pixel_pitch = 3.1;              //mm
  //double sipm_array_d = 0.2;                   //mm distance between two SiPM arrays
  //  
  //sipm_array_L = sipm_array_L/focus_eff*dist_eff/1000000.0;         //km
  //sipm_array_L_eff = sipm_array_L_eff/focus_eff*dist_eff/1000000.0; //km
  //sipm_pixel_pitch = sipm_pixel_pitch/focus_eff*dist_eff/1000000.0; //km
  //sipm_array_d = sipm_array_d/focus_eff*dist_eff/1000000.0; //km

  Double_t focus_eff = 1.0;
  Double_t dist_eff = 1.0;
  //
  Double_t sipm_array_L = 25.3;                 //mm  
  Double_t sipm_array_L_eff = 24.0;             //mm
  Double_t sipm_pixel_pitch = 3.1;              //mm
  double sipm_array_d = 0.2;                   //mm distance between two SiPM arrays
  
  
  //
  //Pixel
  unsigned int nx_sipm_pixel = 8;
  unsigned int ny_sipm_pixel = nx_sipm_pixel;
  Double_t pixel_size = sipm_array_L_eff/nx_sipm_pixel;
  Double_t d_pixel = sipm_pixel_pitch - pixel_size;
  Double_t dead_are_from_edge = (sipm_array_L - sipm_array_L_eff - d_pixel*(nx_sipm_pixel+1))/2.0;
  //
  //Array
  //
  unsigned int nx_sipm_array = 5;
  unsigned int ny_sipm_array = 2;
  Double_t x0_camera = 0.0;
  Double_t y0_camera = 0.0;
  Double_t camera_pitch = sipm_array_L + sipm_array_d;
  _lx_camera = camera_pitch*nx_sipm_array + sipm_array_d;
  _ly_camera = camera_pitch*ny_sipm_array + sipm_array_d;
  //
  //
  /*
  cout<<"nx_sipm_pixel      "<<nx_sipm_pixel<<endl
      <<"ny_sipm_pixel      "<<ny_sipm_pixel<<endl
      <<"sipm_pixel_pitch   "<<sipm_pixel_pitch<<endl
      <<"pixel_size         "<<pixel_size<<endl
      <<"d_pixel            "<<d_pixel<<endl
      <<"dead_are_from_edge "<<dead_are_from_edge<<endl;
  */
  //
  Double_t x0_sipm_array = 0;
  Double_t y0_sipm_array = 0;
  Double_t x0_sipm_pixel = 0;
  Double_t y0_sipm_pixel = 0;
  //
  //
  //TRandom3 *rnd = new TRandom3(1123123);
  for(Int_t j = 0;j<ny_sipm_array;j++){
  for(Int_t i = 0;i<nx_sipm_array;i++){
  //for(Int_t j = 0;j<1;j++){
  //for(Int_t i = 0;i<1;i++){
      x0_sipm_array = -camera_pitch*2   + camera_pitch*i;
      y0_sipm_array = -camera_pitch/2.0 + camera_pitch*j;
      for(Int_t jp = 0;jp<ny_sipm_pixel;jp++){
      for(Int_t ip = 0;ip<nx_sipm_pixel;ip++){
      //for(Int_t jp = 0;jp<1;jp++){
      //for(Int_t ip = 0;ip<1;ip++){
	  y0_sipm_pixel = y0_sipm_array - (sipm_pixel_pitch*3.0 + sipm_pixel_pitch/2.0) + sipm_pixel_pitch*jp;
	  x0_sipm_pixel = x0_sipm_array - (sipm_pixel_pitch*3.0 + sipm_pixel_pitch/2.0) + sipm_pixel_pitch*ip;
	  //
	  //we go clockwise
	  int kk_count = 0;
	  for(Int_t kk = 0;kk<=nAdditionalePoints;kk++){
	    x[kk_count] = x0_sipm_pixel - pixel_size/2.0;
	    y[kk_count] = y0_sipm_pixel - pixel_size/2.0 + pixel_size/(nAdditionalePoints + 1.0)*kk;
	    kk_count++;
	  }
	  //
	  for(Int_t kk = 0;kk<=nAdditionalePoints;kk++){
	    x[kk_count] = x0_sipm_pixel - pixel_size/2.0 + pixel_size/(nAdditionalePoints + 1.0)*kk;
	    y[kk_count] = y0_sipm_pixel + pixel_size/2.0;
	    kk_count++;
	  }
	  //
	  for(Int_t kk = 0;kk<=nAdditionalePoints;kk++){
	    x[kk_count] = x0_sipm_pixel + pixel_size/2.0;
	    y[kk_count] = y0_sipm_pixel + pixel_size/2.0 - pixel_size/(nAdditionalePoints + 1.0)*kk;
	    kk_count++;
	  }
	  //
	  for(Int_t kk = 0;kk<=nAdditionalePoints;kk++){
	    x[kk_count] = x0_sipm_pixel + pixel_size/2.0 - pixel_size/(nAdditionalePoints + 1.0)*kk;
	    y[kk_count] = y0_sipm_pixel - pixel_size/2.0;
	    kk_count++;
	  }	 
	  //
	  x[kk_count] = x0_sipm_pixel - pixel_size/2.0;
	  y[kk_count] = y0_sipm_pixel - pixel_size/2.0;
	  //
	  AddBin(n,x,y);
	}
      }
    }
  }
  
  //  
  gStyle->SetPalette(kRainBow);
  //TImage *img = TImage::Open("./merger.png");
  //img->SetConstRatio(kFALSE);
  TCanvas *c1 = new TCanvas("c1","c1",1000,470);
  //SetTitle("");
  //SetName("");
  c1->SetTitle(title);
  c1->SetName(name);
  c1->SetRightMargin(0.12);
  c1->SetLeftMargin(0.12);
  c1->SetTopMargin(0.1);
  c1->SetBottomMargin(0.15);

  _d_frame = 5.0;
  TH2F *frame = new TH2F( "h2", "h2", 40, -_lx_camera/2.0-_d_frame,_lx_camera/2.0+_d_frame,40, -_ly_camera/2.0-_d_frame,_ly_camera/2.0+_d_frame);
  frame->SetTitle("");
  //frame->GetXaxis()->SetTitle("x (km)");
  //frame->GetYaxis()->SetTitle("y (km)");
  frame->GetXaxis()->SetTitle("x (mm)");
  frame->GetYaxis()->SetTitle("y (mm)");
  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->CenterTitle();
  frame->GetYaxis()->SetTitleOffset(1.5);
  frame->SetStats(kFALSE);
  frame->SetTitle(title);
  frame->Draw();

  //Draw("ZCOLOR text same");
  //Draw("same");
  //c1->SaveAs("test.pdf");
  
  /*
  Double_t l = 3  
  Double_t x0 = 0.0;
  Double_t y0 = 0.0;
  for (unsigned j=0; j < n; j++){
  //cout<<'  '<<m_verticesMap[j].X()<<'  '<<m_verticesMap[j].Y()<<endl;
  xold = ;
  yold = ;
  makeRotation( xold, yold, xnew, ynew, r, phi);
  makeRotation( xold, yold, xnew, ynew, r, phi);
  x[j] = xnew;
  y[j] = ynew;
  }

  */
}

CameraPlaneHist::~CameraPlaneHist(){
}

void CameraPlaneHist::count_signal(Double_t th_val, Int_t &nch, Int_t &npe){
  nch = 0;
  npe = 0;
  for(Int_t i = 0;i<GetNcells();i++){
    //cout<<GetNcells()<<endl;
    if(GetBinContent(i)>=th_val){
      npe = npe + GetBinContent(i);
      nch++;
    }
  }
}

void CameraPlaneHist::Clean(){
  for(Int_t i = 0;i<GetNcells();i++){
    SetBinContent(i,0);
  }
}

void CameraPlaneHist::test(){
  CameraPlaneHist  *test_cp = new CameraPlaneHist("", "");
  cout<<"test_cp->GetNcells() "<<test_cp->GetNcells()<<endl
      <<"test_cp->GetNbinsX() "<<test_cp->GetNbinsX()<<endl
      <<"test_cp->GetNbinsY() "<<test_cp->GetNbinsY()<<endl;

  TCanvas *c1 = new TCanvas("c1","c1",1000,470);
  c1->SetRightMargin(0.12);
  c1->SetLeftMargin(0.12);
  c1->SetTopMargin(0.1);
  c1->SetBottomMargin(0.15);

  TH2F *frame = new TH2F( "h2", "h2", 40, -_lx_camera/2.0-_d_frame,_lx_camera/2.0+_d_frame,40, -_ly_camera/2.0-_d_frame,_ly_camera/2.0+_d_frame);
  frame->SetTitle("");
  //frame->GetXaxis()->SetTitle("x (km)");
  //frame->GetYaxis()->SetTitle("y (km)");
  frame->GetXaxis()->SetTitle("x (mm)");
  frame->GetYaxis()->SetTitle("y (mm)");
  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->CenterTitle();
  frame->GetYaxis()->SetTitleOffset(1.5);
  frame->SetStats(kFALSE);
  frame->Draw();

  //for(Int_t i = 0;i<test_cp->GetNcells();i++){
  //test_cp->SetBinContent(i,i);
  //}
  test_cp->SetMarkerSize(1.0);
  //test_cp->Draw("text same");
  test_cp->Draw("same");
  c1->SaveAs("test.pdf");

}

/*
void ARICHMergerHist::setUpARICHMergerHist(){
  /*
  unsigned int n;
  Double_t* x; 
  Double_t* y;

  Double_t xold;
  Double_t yold;
  Double_t xnew;
  Double_t ynew;
  Double_t r;
  Double_t phi;

  for (unsigned i=0; i<m_merStrV.size(); i++){
    //cout <<i<< ' ' <<m_merStrV[i].center_radius_mm<<endl;
    r = m_merStrV[i].center_radius_mm;
    phi = m_merStrV[i].center_rotation_deg;
    n = m_verticesMap.size();  
    x = new Double_t [n];
    y = new Double_t [n];
    TGraph gr;
    for (unsigned j=0; j < n; j++){
      //cout<<'  '<<m_verticesMap[j].X()<<'  '<<m_verticesMap[j].Y()<<endl;
      xold = m_verticesMap[j].X();
      yold = m_verticesMap[j].Y();
      makeRotation( xold, yold, xnew, ynew, r, phi);
      makeRotation( xold, yold, xnew, ynew, r, phi);
      x[j] = xnew;
      y[j] = ynew;
      gr.SetPoint(gr.GetN(),xnew,ynew);
    }
    AddBin(n,x,y);
    m_verticesGraphV.push_back(gr);
    int mergerSlotNumber = m_merStrV[i].MergerSN + (m_merStrV[i].Sector - 1)*12.0;
    m_mergerSlotNumber.push_back(mergerSlotNumber);
    //cout<<"GetNcells() "<<GetNcells()<<endl;
    //SetBinContent(GetNcells(),m_merStrV[i].Sector);
    //SetBinContent(GetNcells(),mergerSlotNumber);
    //SetBinContent(GetNcells(),GetNcells());
    delete x;
    delete y;
  }

}
*/
