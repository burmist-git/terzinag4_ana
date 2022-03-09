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

Int_t plots_camera_plane(){

    
  Double_t sipm_array_L = 25.3;                 //mm  
  Double_t sipm_array_L_eff = 24.0;             //mm

  //
  //Pixel
  unsigned int nx_sipm_pixel = 8;
  unsigned int ny_sipm_pixel = nx_sipm_pixel;
  Double_t sipm_pixel_pitch = 3.1;              //mm
  Double_t pixel_size = sipm_array_L_eff/nx_sipm_pixel;
  Double_t d_pixel = sipm_pixel_pitch - pixel_size;
  Double_t dead_are_from_edge = (sipm_array_L - sipm_array_L_eff - d_pixel*(nx_sipm_pixel+1))/2.0;
  //
  //Array
  //
  double sipm_array_d = 0.2;                   //mm distance between two SiPM arrays
  unsigned int nx_sipm_array = 5;
  unsigned int ny_sipm_array = 2;
  Double_t x0_camera = 0.0;
  Double_t y0_camera = 0.0;
  Double_t camera_pitch = sipm_array_L + sipm_array_d;
  Double_t lx_camera = camera_pitch*nx_sipm_array + sipm_array_d;
  Double_t ly_camera = camera_pitch*ny_sipm_array + sipm_array_d;
  //
  //
  cout<<"nx_sipm_pixel      "<<nx_sipm_pixel<<endl
      <<"ny_sipm_pixel      "<<ny_sipm_pixel<<endl
      <<"sipm_pixel_pitch   "<<sipm_pixel_pitch<<endl
      <<"pixel_size         "<<pixel_size<<endl
      <<"d_pixel            "<<d_pixel<<endl
      <<"dead_are_from_edge "<<dead_are_from_edge<<endl;
  //
  
  TString fileName;
  //fileName = "./hist_GeomID11/hist_terzina_theta176.5deg_phi13deg_7.0km.root";
  //fileName = "./hist_GeomID11/hist_terzina_bifocal_theta177.0deg_phi5deg_7.0km.root";

  //fileName = "./hist_GeomID11/hist_terzina_bifocal_theta179.4deg_phi45deg_7.0km.root";
  //fileName = "./hist_GeomID11/hist_terzina_PSF_theta180.0deg_phi0.0deg.root";
  //fileName = "./hist_GeomID11/hist_terzina_PSF_theta179.0deg_phi10.0deg.root";
  //fileName = "./hist_GeomID11/hist_terzina_PSF_theta177.0deg_phi10.0deg.root";
  //fileName = "./hist_GeomID11/hist_terzina_PSF_theta176.5deg_phi10.0deg.root";
  //fileName = "./run_sim_camera.root";
  fileName = "./run_sim_camera_spr.root";

  TFile *f1 = new TFile(fileName.Data());
  //
  //TH2Poly *cp_hist = (TH2Poly*)f1->Get("cp_hist");
  TH2Poly *cp_hist = (TH2Poly*)f1->Get("cp_h2_towrite");
  //
  //TCanvas *c1 = new TCanvas("c1",fileName.Data(),10,10,1600,800);



  //  

  //TImage *img = TImage::Open("./merger.png");
  //img->SetConstRatio(kFALSE);
  TCanvas *c1 = new TCanvas("c1","c1",1000*1.7,470*1.5);
  //  gStyle->SetPalette(kRainBow);
  gStyle->SetPalette(kBlueRedYellow);
  //gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  
  //SetTitle("");
  //SetName("");
  //c1->SetTitle(title);
  //c1->SetName(name);
  c1->SetRightMargin(0.08);
  c1->SetLeftMargin(0.08);
  c1->SetTopMargin(0.02);
  c1->SetBottomMargin(0.1);

  Double_t d_frame = 5.0;
  TH2F *frame = new TH2F( "", "", 40, -lx_camera/2.0-d_frame,lx_camera/2.0+d_frame,40, -ly_camera/2.0-d_frame,ly_camera/2.0+d_frame);
  frame->SetTitle("");
  frame->GetXaxis()->SetTitle("x (mm)");
  frame->GetYaxis()->SetTitle("y (mm)");
  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->CenterTitle();
  frame->GetYaxis()->SetTitleOffset(1.5);
  frame->SetStats(kFALSE);
  //frame->SetTitle(title);
  frame->Draw();

  cp_hist->SetMinimum(0);
  cp_hist->SetMaximum(2000);
  cp_hist->SetTitle("");
  cp_hist->Draw("ZCOLOR");

  cp_hist->GetXaxis()->SetTitle("x (mm)");
  cp_hist->GetYaxis()->SetTitle("y (mm)");

  c1->SaveAs("plots_camera_plane.pdf");
  
  /*
  //
  c1->Divide(4,2);
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
  h1_4->Draw();
  c1->cd(5);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_5->Draw();
  //h1_5->GetXaxis()->SetRangeUser(x_PosX_RangeMin,x_PosX_RangeMax);
  c1->cd(6);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_6->Draw();
  //h1_6->GetXaxis()->SetRangeUser(x_PosY_RangeMin,x_PosY_RangeMax);
  c1->cd(7);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogz();
  h1_7->Draw();
  //
  c1->cd(8);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogz();
  h2_8->Draw("ZCOLOR");
  //h2_8->GetXaxis()->SetRangeUser(x_PosX_RangeMin,x_PosX_RangeMax);
  //h2_8->GetYaxis()->SetRangeUser(x_PosY_RangeMin,x_PosY_RangeMax);
  //
  */
  /*
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
  */
  //
  //
  
  return 0;
}
