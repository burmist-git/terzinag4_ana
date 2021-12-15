//my
#include "terzina.hh"

//root
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TGraph.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TRandom3.h>
#include <TMath.h>

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <vector>
#include <iomanip>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

void terzina::Loop(TString histOut){
  //
  Int_t i = 0;
  //
  Double_t primR = 0.0;
  Double_t posR  = 0.0;
  //Double_t posL  = 0.0;
  Double_t thetaPhotons = 0.0;
  Double_t thetaPhotons_deg = 0.0;
  Double_t phiPhotons = 0.0;
  Double_t phiPhotons_deg = 0.0;
  //
  Double_t z0_reco = 0.0;
  Double_t proj_sphere_R = 208.0;
  Double_t proj_sphere_R_delta_R_2 = 0.0;
  //
  TH1D *h1_primPosX = new TH1D("h1_primPosX","primPosX",1000,-400,400);
  TH1D *h1_primPosY = new TH1D("h1_primPosY","primPosY",100,-400,400);
  TH1D *h1_primPosZ = new TH1D("h1_primPosZ","primPosZ",100,-400,400);
  //
  TH1D *h1_primMomX = new TH1D("h1_primMomX","h1_primMomX",1000,-5.5*1.0e-6,5.5*1.0e-6);
  TH1D *h1_primMomY = new TH1D("h1_primMomY","h1_primMomY",1000,-5.5*1.0e-6,5.5*1.0e-6);
  TH1D *h1_primMomZ = new TH1D("h1_primMomZ","h1_primMomZ",1000,-5.5*1.0e-6,5.5*1.0e-6);
  //
  TH2D *h2_primPosY_vs_primPosX = new TH2D("h2_primPosY_vs_primPosX","primPosY vs primPosX",400,-400,400,400,-400,400);
  TH1D *h1_thetaPhotons = new TH1D("h1_thetaPhotons","thetaPhotons",1000,-2*TMath::Pi(),2*TMath::Pi());
  TH1D *h1_thetaPhotons_deg = new TH1D("h1_thetaPhotons_deg","thetaPhotons deg",400,-10,10);
  //
  TH1D *h1_thetaPhotons_cut = new TH1D("h1_thetaPhotons_cut","thetaPhotons cut",1000,-2*TMath::Pi(),2*TMath::Pi());
  TH1D *h1_thetaPhotons_deg_cut = new TH1D("h1_thetaPhotons_deg_cut","thetaPhotons deg cut",400,-10,10);
  //TH1D *h1_thetaPhotons_deg = new TH1D("h1_thetaPhotons_deg","thetaPhotons deg",4000,-360,360);
  TH1D *h1_phiPhotons = new TH1D("h1_phiPhotons","phiPhotons",1000,-2*TMath::Pi(),2*TMath::Pi());
  TH1D *h1_phiPhotons_deg = new TH1D("h1_phiPhotons_deg","phiPhotons deg",4000,-360,360);
  //
  TH1D *h1_primR = new TH1D("h1_primR","primR",1000,0,1000);
  TH1D *h1_posR = new TH1D("h1_posR","posR",1000,0,100);
  //
  TH1D *h1_Energy = new TH1D("h1_Energy","Energy",100,0.0,6*1.0e-6);
  TH1D *h1_Wavelength = new TH1D("h1_Wavelength","Wavelength",100,200,1100);
  TH1D *h1_Time = new TH1D("h1_Time","Time",10000,0,10);
  TH1D *h1_Time_nocut = new TH1D("h1_Time_nocut","Time nocut",10000,0,10);
  TH1D *h1_photPathLen = new TH1D("h1_photPathLen","photPathLen",10000,0,5000); 
  //
  TH1D *h1_PosX = new TH1D("h1_PosX","PosX",5000,-100,100);
  TH1D *h1_PosX_cut = new TH1D("h1_PosX_cut","PosX cut",5000,-100,100);
  TH1D *h1_PosY = new TH1D("h1_PosY","PosY",5000,-100,100);
  TH1D *h1_PosZ = new TH1D("h1_PosZ","PosZ",5000, -200,200);
  TH2D *h2_PosY_vs_PosX = new TH2D("h2_PosY_vs_PosX","PosY vs PosX",1000,-100,100,1000,-100,100);
  TH2D *h2_PosY_vs_PosX_forzoom = new TH2D("h2_PosY_vs_PosX_forzoom","PosY vs PosX forzoom",1000,-100,100,1000,-100,100);
  TH2D *h2_PosY_vs_PosX_single = new TH2D("h2_PosY_vs_PosX_single","PosY vs PosX single",400,-5,5,400,-5,5);
  //
  TH1D *h1_MomX = new TH1D("h1_MomX","MomX",1000,-6*1.0e-6,6*1.0e-6);
  TH1D *h1_MomY = new TH1D("h1_MomY","MomY",1000,-6*1.0e-6,6*1.0e-6);
  TH1D *h1_MomZ = new TH1D("h1_MomZ","MomZ",1000,-6*1.0e-6,6*1.0e-6);
  //
  TH2D *h2_PosX_vs_primPosX = new TH2D("h2_PosX_vs_primPosX","PosX vs primPosX",400,-400,400,4000,-120,120);
  TProfile *pr_PosX_vs_primPosX = new TProfile("pr_PosX_vs_primPosX","PosX vs primPosX",400,-400,400,"");
  TH2D *h2_thetaPhotons_deg_vs_primPosX = new TH2D("h2_thetaPhotons_deg_vs_primPosX","thetaPhotons deg vs primPosX",400,-400,400,400,-10,10);
  TProfile *pr_thetaPhotons_deg_vs_primPosX = new TProfile("pr_thetaPhotons_deg_vs_primPosX","thetaPhotons deg vs primPosX",400,-400,400,"");
  //
  TH2D *h2_thetaPhotons_deg_vs_primPosX_cut = new TH2D("h2_thetaPhotons_deg_vs_primPosX_cut","thetaPhotons deg vs primPosX cut",400,-400,400,400,-10,10);
  TProfile *pr_thetaPhotons_deg_vs_primPosX_cut = new TProfile("pr_thetaPhotons_deg_vs_primPosX_cut","thetaPhotons deg vs primPosX cut",400,-400,400,"");
  TProfile *pr_thetaPhotons_vs_primPosX_cut = new TProfile("pr_thetaPhotons_vs_primPosX_cut","thetaPhotons vs primPosX cut",700,-350,350,"");
  //TProfile *pr_thetaPhotons_vs_primPosX_cut_tmp = new TProfile("pr_thetaPhotons_vs_primPosX_cut_tmp","thetaPhotons vs primPosX cut tmp",700,-350,350,"");
  //
  TH1D *h1_proj_sphere_R_delta_R_2 = new TH1D("h1_proj_sphere_R_delta_R_2","proj_sphere_R_delta_R_2",1000,-100000,100000);
  TH1D *h1_z0_reco = new TH1D("h1_z0_reco","z0_reco",4000,-100,-50);
  //
  TH1D *h1_R_PSF = new TH1D("h1_R_PSF","R PSF",800,0.0,20.0);
  //
  Double_t xMaxCenter;
  Double_t yMaxCenter;	  
  //
  vector<Double_t> vecPosX;
  vector<Double_t> vecPosY;
  //
  Long64_t nentries = fChain->GetEntriesFast();
  cout<<"nentries = "<<nentries<<endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    //
    primR = TMath::Sqrt(primPosX*primPosX+primPosY*primPosY);
    posR  = TMath::Sqrt(PosX[i]*PosX[i]+PosY[i]*PosY[i]);
    //
    thetaPhotons = TMath::ACos(primMomZ/TMath::Sqrt(primMomX*primMomX + primMomY*primMomY + primMomZ*primMomZ));
    thetaPhotons = thetaPhotons - TMath::Pi();
    if(primMomX>0)
      thetaPhotons = -thetaPhotons;
    thetaPhotons_deg = (thetaPhotons*180.0/TMath::Pi());
    //
    //
    if(primMomX == 0.0 && thetaPhotons != 0.0)
      phiPhotons = TMath::Pi()/2.0;
    else if(primMomX == 0.0 && thetaPhotons == 0.0)
      phiPhotons = 0.0;
    else if(primMomX > 0)
      phiPhotons = TMath::ATan(primMomY/primMomX);
    else if(primMomX < 0)
      phiPhotons = TMath::ATan(primMomY/primMomX) + TMath::Pi();
    phiPhotons_deg = phiPhotons*180/TMath::Pi();
    //
    if(nPhot>0){
      h1_Time_nocut->Fill(Time[i]);
      proj_sphere_R_delta_R_2 = proj_sphere_R*proj_sphere_R - PosX[i]*PosX[i] - PosY[i]*PosY[i];
      if(proj_sphere_R_delta_R_2 > 0.0)
	z0_reco = PosZ[i] - TMath::Sqrt(proj_sphere_R*proj_sphere_R - PosX[i]*PosX[i] - PosY[i]*PosY[i]);
      else
	z0_reco = -999.0;
      h1_proj_sphere_R_delta_R_2->Fill(proj_sphere_R_delta_R_2);
      h1_z0_reco->Fill(z0_reco);
      //if(TMath::Abs(z0_reco + 63)<0.00001 && TMath::Abs(primPosX)>95.0){
      //if(TMath::Abs(z0_reco + 63)<1000000 && TMath::Abs(primPosX)>-10000000){
      if(Time[i]>=0 && Time[i]<=10000){
	//if(Time[i]>=2.7 && Time[i]<=3.2){
	//if(Wavelength[i]>=290.0 && Wavelength[i]<=310.0){
	//if(Wavelength[i]>=390.0 && Wavelength[i]<=410.0){
	//if(Wavelength[i]>=590.0 && Wavelength[i]<=610.0){
	if(Wavelength[i]>=0.0 && Wavelength[i]<=2000.0){
	  //if(Time[i]>=4.7 && Time[i]<=4.8){
	  //
      if((PosX[i]*PosX[i] + PosY[i]*PosY[i])>0.0*0.0 && (PosX[i]*PosX[i] + PosY[i]*PosY[i])<400.0*400.0){
	h1_primPosX->Fill(primPosX);
	h1_primPosY->Fill(primPosY);
	h1_primPosZ->Fill(primPosZ);
	  //
	  h1_primMomX->Fill(primMomX);
	  h1_primMomY->Fill(primMomY);
	  h1_primMomZ->Fill(primMomZ);
	  //
	  h2_primPosY_vs_primPosX->Fill(primPosX,primPosY);
	  h1_thetaPhotons->Fill(thetaPhotons);
	  h1_thetaPhotons_deg->Fill(thetaPhotons_deg);
	  h1_phiPhotons->Fill(phiPhotons);
	  h1_phiPhotons_deg->Fill(phiPhotons_deg);
	  //
	  h1_primR->Fill(primR);
	  h1_posR->Fill(posR);
	  //h2_PosR_vs_primR->Fill(primR,posR);
	  //pr_PosR_vs_primR->Fill(primR,posR);
	  //	
	  h1_Energy->Fill(Energy[i]);
	  h1_Wavelength->Fill(Wavelength[i]);
	  h1_Time->Fill(Time[i]);
	  h1_photPathLen->Fill(photPathLen[i]);
	  //
	  h1_PosX->Fill(PosX[i]);
	  h1_PosY->Fill(PosY[i]);
	  h1_PosZ->Fill(PosZ[i]);
	  h2_PosY_vs_PosX->Fill(PosX[i],PosY[i]);
	  h2_PosY_vs_PosX_forzoom->Fill(PosX[i],PosY[i]);
	  h2_PosY_vs_PosX_single->Fill(PosX[i],PosY[i]);
	  //
	  h1_MomX->Fill(MomX[i]);
	  h1_MomY->Fill(MomY[i]);
	  h1_MomZ->Fill(MomZ[i]);
	  //
	  h2_PosX_vs_primPosX->Fill(primPosX,PosX[i]);
	  pr_PosX_vs_primPosX->Fill(primPosX,PosX[i]);
	  h2_thetaPhotons_deg_vs_primPosX->Fill(primPosX,thetaPhotons_deg);
	  pr_thetaPhotons_deg_vs_primPosX->Fill(primPosX,thetaPhotons_deg);
	  //
	  vecPosX.push_back(PosX[i]);
	  vecPosY.push_back(PosY[i]);
	  //xMaxCenter = -0.1;
	  //yMaxCenter = -0.1;
	  //h1_R_PSF_0deg->Fill(TMath::Sqrt((PosX[i]-xMaxCenter)*(PosX[i]-xMaxCenter) + (PosY[i]-yMaxCenter)*(PosY[i]-yMaxCenter)));
	  //xMaxCenter = 16.7;
	  //yMaxCenter =  0.1;
	  //h1_R_PSF_1deg->Fill(TMath::Sqrt((PosX[i]-xMaxCenter)*(PosX[i]-xMaxCenter) + (PosY[i]-yMaxCenter)*(PosY[i]-yMaxCenter)));
	  //xMaxCenter = 33.3;
	  //yMaxCenter =  0.1;
	  //h1_R_PSF_2deg->Fill(TMath::Sqrt((PosX[i]-xMaxCenter)*(PosX[i]-xMaxCenter) + (PosY[i]-yMaxCenter)*(PosY[i]-yMaxCenter)));
	  //xMaxCenter = 49.5;
	  //yMaxCenter = -0.1;
	  //h1_R_PSF_3deg->Fill(TMath::Sqrt((PosX[i]-xMaxCenter)*(PosX[i]-xMaxCenter) + (PosY[i]-yMaxCenter)*(PosY[i]-yMaxCenter)));
	  //
	  if(TMath::Abs(PosX[i])<1){
	    h2_thetaPhotons_deg_vs_primPosX_cut->Fill(primPosX,thetaPhotons_deg);
	    if(TMath::Abs(primPosX)>94 && TMath::Abs(primPosX)<278){
	      pr_thetaPhotons_deg_vs_primPosX_cut->Fill(primPosX,thetaPhotons_deg);
	      pr_thetaPhotons_vs_primPosX_cut->Fill(primPosX,thetaPhotons);
	      //pr_thetaPhotons_vs_primPosX_cut_tmp->Fill(primPosX,thetaPhotons);
	    }
	    h1_PosX_cut->Fill(PosX[i]);
	    h1_thetaPhotons_cut->Fill(thetaPhotons);
	    h1_thetaPhotons_deg_cut->Fill(thetaPhotons_deg);
	  }
	  }
	  }
    }
    }
  }
  ///////////////////
  //xMaxCenter = 32.0;
  //yMaxCenter = 0.0;
  xMaxCenter = h1_PosX->GetBinCenter(h1_PosX->GetMaximumBin());
  yMaxCenter = h1_PosY->GetBinCenter(h1_PosY->GetMaximumBin());
  //xMaxCenter = h1_PosX->GetMean();
  //yMaxCenter = h1_PosY->GetMean();
  Double_t window_dl = 10;
  TH2D *h2_PosY_vs_PosX_recentrate = new TH2D("h2_PosY_vs_PosX_recentrate","PosY vs PosX recentrate",1000,xMaxCenter-window_dl,xMaxCenter+window_dl,1000,yMaxCenter-window_dl,yMaxCenter+window_dl);
  for(unsigned int ii = 0;ii<vecPosX.size();ii++){
    h1_R_PSF->Fill(TMath::Sqrt((vecPosX.at(ii)-xMaxCenter)*(vecPosX.at(ii)-xMaxCenter) + (vecPosY.at(ii)-yMaxCenter)*(vecPosY.at(ii)-yMaxCenter)));
    h2_PosY_vs_PosX_recentrate->Fill(vecPosX.at(ii),vecPosY.at(ii));
  }
  ///////////////////
  TFile* rootFile = new TFile(histOut.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<histOut.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<histOut.Data()<<endl;
  //
  h1_primPosX->Write();
  h1_primPosY->Write();
  h1_primPosZ->Write();
  //
  h1_primMomX->Write();
  h1_primMomY->Write();
  h1_primMomZ->Write();
  //
  h2_primPosY_vs_primPosX->Write();
  h1_thetaPhotons->Write();
  h1_thetaPhotons_deg->Write();
  h1_thetaPhotons_cut->Write();
  h1_thetaPhotons_deg_cut->Write();
  //
  h1_phiPhotons->Write();
  h1_phiPhotons_deg->Write();
  //      
  h1_primR->Write();
  h1_posR->Write();
  //	
  h1_Energy->Write();
  h1_Wavelength->Write();
  h1_Time->Write();
  h1_Time_nocut->Write();
  h1_photPathLen->Write();
  //
  h1_PosX->Write();
  h1_PosX_cut->Write();
  h1_PosY->Write();
  h1_PosZ->Write();
  h2_PosY_vs_PosX->Write();
  h2_PosY_vs_PosX_forzoom->Write();
  h2_PosY_vs_PosX_single->Write();
  h2_PosY_vs_PosX_recentrate->Write();
  //
  h1_MomX->Write();
  h1_MomY->Write();
  h1_MomZ->Write();
  //
  h2_PosX_vs_primPosX->Write();
  pr_PosX_vs_primPosX->Write();
  h2_thetaPhotons_deg_vs_primPosX->Write();
  pr_thetaPhotons_deg_vs_primPosX->Write();
  //
  h2_thetaPhotons_deg_vs_primPosX_cut->Write();
  pr_thetaPhotons_deg_vs_primPosX_cut->Write();
  pr_thetaPhotons_vs_primPosX_cut->Write();
  //pr_thetaPhotons_vs_primPosX_cut_tmp->Write();
  //
  h1_PosX_cut->Write();
  //
  h1_proj_sphere_R_delta_R_2->Write();
  h1_z0_reco->Write();
  //
  h1_R_PSF->Write();
  //
  rootFile->Close();
}
