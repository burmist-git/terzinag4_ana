//my
#include "terzina.hh"
#include "CameraPlaneHist.hh"
#include "sim_trk_info_str.hh"

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
#include <TTreeReader.h>

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

terzina::terzina(TString fileList) : terzinabase(fileList)
{
  _nPhotonsPerM2 = 0;
  _particleMomentum = 0.0;
  _ThetaAngle_offset = 0.0;
  _ThetaAngle_mean_without_offset = 0.0;
  _ThetaAngle_RMS = 0.0;
  _time_offset = 0.0;
  _time_mean_without_offset = 0.0;
  _time_RMS = 0.0;
  _DistanceFromTheAxisOfTheShower = 0.0;
  _nPhotonsPerM2_scaled_100PeV = 0.0;
}

terzina::terzina(TString file, Int_t key) : terzinabase(file, key)
{
  _nPhotonsPerM2 = 0;
  _particleMomentum = 0.0;
  _ThetaAngle_offset = 0.0;
  _ThetaAngle_mean_without_offset = 0.0;
  _ThetaAngle_RMS = 0.0;
  _time_offset = 0.0;
  _time_mean_without_offset = 0.0;
  _time_RMS = 0.0;
  _DistanceFromTheAxisOfTheShower = 0.0;
  _nPhotonsPerM2_scaled_100PeV = 0.0;
}

terzina::~terzina(){
}

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
      //if(Time[i]>=3.01 && Time[i]<=3.02){
      //if(Time[i]>=2.95 && Time[i]<=3.1){
      //2.0deg
      //if(Time[i]>=2.98 && Time[i]<=3.06){
      //3.0deg
      //if(Time[i]>=2.98 && Time[i]<=3.06){
      //if(Time[i]>=2.7 && Time[i]<=3.2){
      //if(Time[i]>=2.7 && Time[i]<=3.0){
	//if(Wavelength[i]>=290.0 && Wavelength[i]<=310.0){
	//if(Wavelength[i]>=390.0 && Wavelength[i]<=410.0){
	//if(Wavelength[i]>=590.0 && Wavelength[i]<=610.0){
	if(Wavelength[i]>=0.0 && Wavelength[i]<=2000.0){
	  //if(Time[i]>=4.7 && Time[i]<=4.8){
	  //
      if((PosX[i]*PosX[i] + PosY[i]*PosY[i])>=0.0*0.0 &&
	 (PosX[i]*PosX[i] + PosY[i]*PosY[i])<400.0*400.0){
      //if(((PosX[i] - 57.1)*(PosX[i] - 57.1) + PosY[i]*PosY[i])>=0.0*0.0 &&
	  // ((PosX[i] - 57.1)*(PosX[i] - 57.1) + PosY[i]*PosY[i])<5.0*5.0){
       //if((PosX[i]*PosX[i] + PosY[i]*PosY[i])>=0.0*0.0 &&
       //(PosX[i]*PosX[i] + PosY[i]*PosY[i])<2.0*2.0){
	//if((PosX[i]*PosX[i] + PosY[i]*PosY[i])>10.5*10.5 &&
	  // (PosX[i]*PosX[i] + PosY[i]*PosY[i])<12.0*12.0){
	//if((PosX[i]*PosX[i] + PosY[i]*PosY[i])>56.0*56.0 &&
	//(PosX[i]*PosX[i] + PosY[i]*PosY[i])<60.0*60.0){

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

void terzina::read_Eff_vs_wl(TString datafileIn, TGraph *gr,TString nameTitle){
  ifstream fileIn(datafileIn.Data());
  double xval;
  double yval;
  gr->SetName(nameTitle.Data());
  gr->SetTitle(nameTitle.Data());
  if (fileIn.is_open()){
    while(fileIn>>xval>>yval){
      gr->SetPoint(gr->GetN(),xval,yval);
    }
    fileIn.close();
  }
  else cout<<"Unable to open file"<<endl;
}

Bool_t terzina::ifQE(Double_t wl, TString qe_ID, TRandom3 *rnd){
  Double_t prob_val;
  if(qe_ID == "NUVHD"){
    prob_val = _gr_QE_NUVHD->Eval(wl);
    if(rnd->Uniform()<=prob_val)
      return true;
    return false;
  }
  else
    assert(0);
  return false;
}

Bool_t terzina::if_mirror(Double_t wl, TString mirror_ID, TRandom3 *rnd){
  Double_t prob_val;
  if(mirror_ID == "mirror_Reflectance_Unpolarized"){
    prob_val = _gr_mirror_Reflectance_Unpolarized->Eval(wl);
    //prob_val = 1.0;
    if(rnd->Uniform()<=prob_val)
      return true;
    return false;
  }
  else
    assert(0);
  return false;
}

Bool_t terzina::if_lens(Double_t wl, TString lens_ID, TRandom3 *rnd){
  Double_t prob_val;
  if(lens_ID == "DEFAULT"){
    //prob_val = 0.95*0.95;
    prob_val = 1.0;
    if(rnd->Uniform()<=prob_val)
      return true;
    return false;
  }
  else
    assert(0);
  return false;
}

Bool_t terzina::if_package_fill_factor(TString package_ID, TRandom3 *rnd){
  Double_t prob_val;
  if(package_ID == "DEFAULT"){
    prob_val = 1.0;
    if(rnd->Uniform()<=prob_val)
      return true;
    return false;
  }
  else
    assert(0);
  return false;
}

Bool_t terzina::crosstalk(Double_t prob, TRandom3 *rnd){
  if(rnd->Uniform()<=prob)
      return true;
  return false;
}

void terzina::showerSim(TString inRootFileWithShower, TString inDatFileShower, Double_t particleMomentum, TString outRootFileF){
  //
  _trk_info = new sim_trk_info_str();
  _h1_particle_per_year = new TH1D();
  //
  readEventFormRootFile_newFormat(inRootFileWithShower, inDatFileShower, particleMomentum);
  //std::cout<<"_nPhotonsPerM2      "<<_nPhotonsPerM2<<std::endl
  //	   <<"_h1_wavelength int. "<<_h1_wavelength->Integral(1,_h1_wavelength->GetNbinsX())<<std::endl
  //	   <<"_h1_timeHist int.   "<<_h1_timeHist->Integral(1,_h1_timeHist->GetNbinsX())<<std::endl
  //	   <<"_h1_angleHist int.  "<<_h1_angleHist->Integral(1,_h1_angleHist->GetNbinsX())<<std::endl;  
  _gr_QE_NUVHD = new TGraph();
  _gr_mirror_Reflectance_Unpolarized = new TGraph();
  read_Eff_vs_wl("PDE_NUVHD_3.90V_Pxt_15.dat",_gr_QE_NUVHD,"_gr_QE_NUVHD");
  read_Eff_vs_wl("al_mirror_Reflectance_Unpolarized_nm.dat",_gr_mirror_Reflectance_Unpolarized,"_gr_mirror_Reflectance_Unpolarized");
  //Double_t xVal, yVal;
  //_gr_mirror_Reflectance_Unpolarized->GetPoint(0,xVal,yVal);
  //_gr_QE_NUVHD->GetPoint(3,xVal,yVal);
  //cout<<_gr_QE_NUVHD->Eval(421.3)<<endl;
  //cout<<_gr_mirror_Reflectance_Unpolarized->Eval(421.3)<<endl;
  //cout<<xVal<<" "<<yVal<<endl;
  //assert(0);
  //
  TRandom3 *rnd = new TRandom3(2342342);
  //
  Int_t i = 0;
  //
  TH1D *h1_nPhot = new TH1D("h1_nPhot","nPhot",400,0,400);
  TH1D *h1_npe = new TH1D("h1_npe","n p.e.",400,0,400);
  //
  TH1D *h1_primPosX = new TH1D("h1_primPosX","primPosX",1000,-400,400);
  TH1D *h1_primPosY = new TH1D("h1_primPosY","primPosY",1000,-400,400);
  TH1D *h1_primPosZ = new TH1D("h1_primPosZ","primPosZ",1000,-400,400);
  //
  TH1D *h1_PosX = new TH1D("h1_PosX","PosX",5000,-100,100);
  TH1D *h1_PosY = new TH1D("h1_PosY","PosY",5000,-100,100);
  TH1D *h1_PosZ = new TH1D("h1_PosZ","PosZ",5000,-100,100);
  //
  TH1D *h1_Time = new TH1D("h1_Time","Time",10000,0,10);
  //
  TH1D *h1_Wavelength = new TH1D("h1_Wavelength","Wavelength",1000,200,1100);
  //
  TH2D *h2_primPosY_vs_primPosX = new TH2D("h2_primPosY_vs_primPosX","primPosY vs primPosX",400,-400,400,400,-400,400);
  TH2D *h2_PosY_vs_PosX = new TH2D("h2_PosY_vs_PosX","PosY vs PosX",1000,-100,100,1000,-100,100);
  //
  TH1D *h1_proj_plane_z0 = new TH1D("h1_proj_plane_z0","h1_proj_plane_z0",1000,165,175);
  //
  Int_t npe = 0;
  Long64_t nentries = fChain->GetEntriesFast();
  cout<<"nentries = "<<nentries<<endl;
  Double_t weight = 1.0/nentries;
  Long64_t nbytes = 0, nb = 0;
  //
  Double_t proj_plane_R  = 300.0;
  Double_t proj_plane_x0 = 0.0;
  Double_t proj_plane_y0 = 0.0;
  Double_t proj_plane_z0 = 0.0;
  //
  CameraPlaneHist *cp_hist = new CameraPlaneHist("cp_hist", "cp_hist");
  //cp_hist->test();
  //assert(0);
  //
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //for (Long64_t jentry=0; jentry<1000;jentry++) {
    //Long64_t jentry_in=100;
    //for (Long64_t jentry=jentry_in; jentry<(jentry_in+1);jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    //
    //thetaPhotons = TMath::ACos(primMomZ/TMath::Sqrt(primMomX*primMomX + primMomY*primMomY + primMomZ*primMomZ));
    //thetaPhotons = thetaPhotons - TMath::Pi();
    //if(primMomX>0)
    //thetaPhotons = -thetaPhotons;
    //thetaPhotons_deg = (thetaPhotons*180.0/TMath::Pi());
    //
    h1_nPhot->Fill(nPhot);
    h1_primPosX->Fill(primPosX);
    h1_primPosY->Fill(primPosY);
    h1_primPosZ->Fill(primPosZ);
    h2_primPosY_vs_primPosX->Fill(primPosX,primPosY);
    if(nPhot>0){
      npe = 0;
      for(i = 0;i<nPhot;i++){
	if(ifQE(Wavelength[i],"NUVHD",rnd)){
	  if(if_mirror(Wavelength[i],"mirror_Reflectance_Unpolarized",rnd)){
	    if(if_mirror(Wavelength[i],"mirror_Reflectance_Unpolarized",rnd)){
	      if(if_lens(Wavelength[i],"DEFAULT",rnd)){
		if(if_package_fill_factor("DEFAULT",rnd)){
		  //if(Time[i]>3.01 && Time[i]<3.03){
		  //if(Time[i]>2.95 && Time[i]<3.1){
		  if(Time[i]>0.0 && Time[i]<100000){
		    proj_plane_z0 = PosZ[i] + TMath::Sqrt(proj_plane_R*proj_plane_R -
							  (PosX[i]*PosX[i] - proj_plane_x0*proj_plane_x0) -
							  (PosY[i]*PosY[i] - proj_plane_y0*proj_plane_y0));
		    h1_proj_plane_z0->Fill(proj_plane_z0);
		    //if(proj_plane_z0>=170 && proj_plane_z0<=172){
		    if(proj_plane_z0>=-10000 && proj_plane_z0<=10000){
		      do{
			//
			//
			h1_PosX->Fill(PosX[i]);
			h1_PosY->Fill(PosY[i]);
			h1_PosZ->Fill(PosZ[i]);
			//
			h1_Time->Fill(Time[i]);
			h1_Wavelength->Fill(Wavelength[i]);
			//
			h2_PosY_vs_PosX->Fill(PosX[i],PosY[i]);
			//
			cp_hist->Fill(PosX[i],PosY[i],weight);
			npe++;
		      }
		      while(crosstalk(0.0,rnd));
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
      h1_npe->Fill(npe);
    }
  }
  ///////////////////
  TFile* rootFile = new TFile(outRootFileF.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<outRootFileF.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<outRootFileF.Data()<<endl;
  //
  h1_nPhot->Write();
  h1_Time->Write();
  //
  h1_primPosX->Write();
  h1_primPosY->Write();
  h1_primPosZ->Write();
  //
  h1_PosX->Write();
  h1_PosY->Write();
  h1_PosZ->Write();
  //
  h1_proj_plane_z0->Write();
  //
  h2_primPosY_vs_primPosX->Write();
  h2_PosY_vs_PosX->Write();
  //
  h1_Wavelength->Write();
  //
  cp_hist->Write();
  //
  h1_npe->Write();
  //
  _h1_distance->Write();
  _h1_wavelength->Write();
  _h1_timeHist->Write();
  _h1_angleHist->Write();
  _gr_QE_NUVHD->Write();
  _gr_mirror_Reflectance_Unpolarized->Write();
  //
  rootFile->Close();
}

void terzina::bkgSim(TString outRootFileF){
  _gr_QE_NUVHD = new TGraph();
  cout<<"_gr_QE_NUVHD"<<endl;
  read_Eff_vs_wl("PDE_NUVHD_3.90V_Pxt_15.dat",_gr_QE_NUVHD,"_gr_QE_NUVHD");
  //
  TRandom3 *rnd = new TRandom3(2342342);
  //
  Int_t i = 0;
  //
  TH1D *h1_nPhot = new TH1D("h1_nPhot","nPhot",400,0,400);
  TH1D *h1_npe = new TH1D("h1_npe","n p.e.",400,0,400);
  //
  TH1D *h1_PosX = new TH1D("h1_PosX","PosX",5000,-100,100);
  TH1D *h1_PosY = new TH1D("h1_PosY","PosY",5000,-100,100);
  TH1D *h1_PosZ = new TH1D("h1_PosZ","PosZ",5000,-100,100);
  //
  TH1D *h1_Time = new TH1D("h1_Time","Time",10000,0,10);
  //
  TH1D *h1_Wavelength = new TH1D("h1_Wavelength","Wavelength",1000,200,1100);
  //
  TH2D *h2_PosY_vs_PosX = new TH2D("h2_PosY_vs_PosX","PosY vs PosX",1000,-100,100,1000,-100,100);
  //
  TH1D *h1_dedx_sipm = new TH1D("h1_dedx_sipm","dedx sipm",10000,0,400);
  TH1D *h1_trackL_sipm = new TH1D("h1_trackL_sipm","trackL sipm",10000,0,400);
  //
  TH1D *h1_dedx_sipm_zoom = new TH1D("h1_dedx_sipm_zoom","dedx sipm zoom",10000,0,40);
  TH1D *h1_trackL_sipm_zoom = new TH1D("h1_trackL_sipm_zoom","trackL sipm zoom",10000,0,40);
  //
  TH1D *h1_dedx_sipm_zoom_zoom = new TH1D("h1_dedx_sipm_zoom_zoom","dedx sipm zoom zoom",10000,0,4);
  TH1D *h1_trackL_sipm_zoom_zoom = new TH1D("h1_trackL_sipm_zoom_zoom","trackL sipm zoom zoom",10000,0,4);
  //
  Int_t npe = 0;
  Long64_t nentries = fChain->GetEntriesFast();
  cout<<"nentries = "<<nentries<<endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //for (Long64_t jentry=0; jentry<1000;jentry++) {
    //Long64_t jentry_in=100;
    //for (Long64_t jentry=jentry_in; jentry<(jentry_in+1);jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    //
    //if(nPhot>0.0)
    h1_nPhot->Fill(nPhot);
    //if(dedx_sipm>0.0){
    h1_dedx_sipm->Fill(dedx_sipm);
    h1_dedx_sipm_zoom->Fill(dedx_sipm);
    h1_dedx_sipm_zoom_zoom->Fill(dedx_sipm);
    //}
    //if(trackL_sipm>0.0){
    h1_trackL_sipm->Fill(trackL_sipm);
    h1_trackL_sipm_zoom->Fill(trackL_sipm);
    h1_trackL_sipm_zoom_zoom->Fill(trackL_sipm);
    //}
    //
    if(nPhot>0){
      npe = 0;
      for(i = 0;i<nPhot;i++){
	if(ifQE(Wavelength[i],"NUVHD",rnd)){
	  if(Time[i]>0.0 && Time[i]<100000){
	      do{
		//
		//
		h1_PosX->Fill(PosX[i]);
		h1_PosY->Fill(PosY[i]);
		h1_PosZ->Fill(PosZ[i]);
		//
		h1_Time->Fill(Time[i]);
		h1_Wavelength->Fill(Wavelength[i]);
		//
		h2_PosY_vs_PosX->Fill(PosX[i],PosY[i]);
		//
		npe++;
	      }
	      while(crosstalk(0.0,rnd));
	    }
	}
      }
      h1_npe->Fill(npe);
    }
  }
  ///////////////////
  TFile* rootFile = new TFile(outRootFileF.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<outRootFileF.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<outRootFileF.Data()<<endl;
  //
  h1_nPhot->Write();
  h1_Time->Write();
  //
  h1_PosX->Write();
  h1_PosY->Write();
  h1_PosZ->Write();
  //
  h2_PosY_vs_PosX->Write();
  //
  h1_Wavelength->Write();
  //
  h1_npe->Write();
  //
  h1_dedx_sipm->Write();
  h1_trackL_sipm->Write();
  //
  h1_dedx_sipm_zoom->Write();
  h1_trackL_sipm_zoom->Write();
  //
  h1_dedx_sipm_zoom_zoom->Write();
  h1_trackL_sipm_zoom_zoom->Write();
  //
  rootFile->Close();
}

void terzina::readEventFormRootFile(TString inRootFileName_g4s, Double_t distanceFromTheAxisOfTheShower){
  //
  _h1_distance = new TH1D();
  _h1_wavelength = new TH1D();
  _h1_timeHist = new TH1D();
  _h1_angleHist = new TH1D();
  //
  _h1_distance->SetName("_h1_distance");
  _h1_wavelength->SetName("_h1_wavelength");
  _h1_timeHist->SetName("_h1_timeHist");
  _h1_angleHist->SetName("_h1_angleHist");
  //
  _h1_distance->SetTitle("_h1_distance");
  _h1_wavelength->SetTitle("_h1_wavelength");
  _h1_timeHist->SetTitle("_h1_timeHist");
  _h1_angleHist->SetTitle("_h1_angleHist");
  
  TString inRootFileName = inRootFileName_g4s;
  
  //TString inRootFileName = "/home/dpncguest/home2/work/POEMMA/geant4/shower_sim/data/30km_Impact_Parameter.root";
  //TString outHistRootFileName = "./hist/hist_Proton_100PeV_525km_67_7.root";
  
  //void Read( TString inRootFileName = "./data/Proton_100PeV_525km_67_7.root", TString outHistRootFileName = "./hist/hist_Proton_100PeV_525km_67_7.root"){
  //TFile *fIn = new TFile("./data/Proton_100PeV_525km_67_7.root");
  //TFile *fIn = new TFile("./data/Proton_100PeV_33km_85.root");

  TFile *fIn = new TFile(inRootFileName.Data());

  fIn->ls();
  fIn->Print();

  // -----------------------------------------------------------------------------
  // Shower parameter
  // -----------------------------------------------------------------------------
  std::cout << std::endl;
  std::cout << std::endl;
  TTree *showerProp = (TTree*)fIn->Get("showerProp");
  showerProp->ls();
  showerProp->Print();
  //
  Double_t zenith, energy, startalt;
  TBranch *energyBr = showerProp->GetBranch("energy");
  energyBr->SetAddress(&energy);
  //
  TBranch *zenithBr = showerProp->GetBranch("zenith");
  zenithBr->SetAddress(&zenith);
  TBranch *startaltBr = showerProp->GetBranch("startalt");
  startaltBr->SetAddress(&startalt);
  Int_t nEntries = showerProp->GetEntries();
  std::cout<<"nEntries:"<<" "<<nEntries<<std::endl;
  showerProp->GetEntry(0);
  std::cout<< "Zenith angle = " << zenith <<std::endl;
  std::cout<< "E = " << energy << " PeV" << std::endl;
  std::cout<< "Starting altitude = " << startalt << " km" << std::endl;
  // -----------------------------------------------------------------------------
  
  // -----------------------------------------------------------------------------
  // Cherenkov light parameter
  // -----------------------------------------------------------------------------
  std::cout <<std::endl;
  std::cout <<std::endl;
  TTree *cherPhProp = (TTree*)fIn->Get("cherPhProp");
  cherPhProp->ls();
  cherPhProp->Print();
  TH1D *wavelength = NULL;
  TH1D *distance = NULL;
  TH1D *time_offset = NULL;
  TH1D *angle_offset = NULL;
  // wavelength
  TBranch *wavelengthBr = cherPhProp->GetBranch("wavelength");
  wavelengthBr->SetAddress(&wavelength);
  cherPhProp->GetEntry(0);
  TCanvas *cwl = new TCanvas("cwl", "cwl", 800, 600);
  cwl->cd();
  wavelength->SetDirectory(0);
  wavelength->GetXaxis()->SetTitle("wavelength [nm]");
  //wavelength->Draw();
  // distance
  TBranch *distanceBr = cherPhProp->GetBranch("distance");
  distanceBr->SetAddress(&distance);
  cherPhProp->GetEntry(0);
  TCanvas *cdst = new TCanvas("cdst", "cdst", 800, 600);
  cdst->cd();
  distance->SetDirectory(0);
  TH1D *hdistance = (TH1D *)(distance)->Clone();
  //hdistance->SetTitle("distance");
  //hdistance->GetYaxis()->SetTitle("photon density [pht/m^{2}]");
  //hdistance->GetXaxis()->SetTitle("distance [km]");
  //hdistance->Draw();
  //time_offset
  TBranch *time_offsetBr = cherPhProp->GetBranch("time_offset");
  time_offsetBr->SetAddress(&time_offset);
  cherPhProp->GetEntry(0);
  TCanvas *ctoff = new TCanvas("ctoff", "ctoff", 800, 600);
  ctoff->cd();
  time_offset->SetDirectory(0);
  //time_offset->GetXaxis()->SetTitle("ns");
  //time_offset->Draw("histo");
  // angle_offset
  TBranch *angle_offsetBr = cherPhProp->GetBranch("angle_offset");
  angle_offsetBr->SetAddress(&angle_offset);
  cherPhProp->GetEntry(0);
  TCanvas *cangoff = new TCanvas("cangoff", "cangoff", 800, 600);
  cangoff->cd();
  angle_offset->SetDirectory(0);
  //angle_offset->GetXaxis()->SetTitle("deg");
  //angle_offset->Draw("histo");
  //----------------------------------------------------------------------------------------

  //----------------------------------------------------------------------------------------
  // time distribution
  double dist = distanceFromTheAxisOfTheShower;
  TTreeReader fReaderCherPh_time;
  TTreeReaderValue<std::vector<TH1D>> fDistTimeVec = {fReaderCherPh_time, "time_dist"};
  fReaderCherPh_time.SetTree("cherPhProp");
  fReaderCherPh_time.SetEntry(0);
  // get number of photons at aperture
  auto nBinDist = distance->FindBin(dist);
  //std::cout<<"nBinDist "<<nBinDist<<std::endl;
  TH1D *timeHist = NULL;
  timeHist = (TH1D*)((*fDistTimeVec)[nBinDist-1]).Clone();

  //----------------------------------------------------------------------------------------
  // Angle distribution
  TTreeReader fReaderCherPh_angle;
  TTreeReaderValue<std::vector<TH1D>> fDistAngleVec = {fReaderCherPh_angle, "angle_dist"};
  fReaderCherPh_angle.SetTree("cherPhProp");
  fReaderCherPh_angle.SetEntry(0);
  TH1D *angleHist = NULL;
  angleHist = (TH1D*)((*fDistAngleVec)[nBinDist-1]).Clone();

  //----------------------------------------------------------------------------------------
  copyHistogram(distance, _h1_distance, "_h1_distance", "_h1_distance", false, 1.0);
  copyHistogram(wavelength, _h1_wavelength, "_h1_wavelength", "_h1_wavelength", false, wavelength->Integral(1,wavelength->GetNbinsX()));  
  //
  double nphotons_per_m2 = _h1_distance->GetBinContent((int)nBinDist);    
  _nPhotonsPerM2 = nphotons_per_m2;
  copyHistogram(timeHist,_h1_timeHist,"_h1_timeHist","_h1_timeHist",false,nphotons_per_m2);
  copyHistogram(angleHist,_h1_angleHist,"_h1_angleHist","_h1_angleHist",false,nphotons_per_m2);
  //
  std::cout<<"nBinDist            "<<nBinDist<<std::endl
	   <<"nphotons_per_m2     "<<nphotons_per_m2<<std::endl
	   <<"timeHist int.       "<<timeHist->Integral(1,timeHist->GetNbinsX())<<std::endl
	   <<"angleHist int.      "<<angleHist->Integral(1,angleHist->GetNbinsX())<<std::endl
    	   <<"_h1_wavelength int. "<<_h1_wavelength->Integral(1,_h1_wavelength->GetNbinsX())<<std::endl
	   <<"_h1_timeHist int.   "<<_h1_timeHist->Integral(1,_h1_timeHist->GetNbinsX())<<std::endl
	   <<"_h1_angleHist int.  "<<_h1_angleHist->Integral(1,_h1_angleHist->GetNbinsX())<<std::endl;
  
  fIn->Close();
}

double terzina::generateDistFromHist(TH1D *h1, TRandom3 *rnd){
  int nn = h1->GetNbinsX()+1;
  int binI;
  double val;
  bool go = false;
  double binL;
  double binR;
  while( go == false ){
    binI = (int)rnd->Uniform(1,nn);
    val = h1->GetBinContent(binI);
    if(val>=rnd->Uniform()){
      binL = h1->GetBinLowEdge(binI);
      binR = binL + h1->GetBinWidth(binI);
      go = true;
      return rnd->Uniform(binL,binR);
    }
  }
  return -999.0;
}

void terzina::copyHistogram(TH1D *h1, TH1D *h1_copy, TString h1_name_g, TString h1_title_g, bool ifBinsOnly, double norm){
  TString h1_name = h1_name_g;
  TString h1_title = h1_title_g;
  h1_copy->SetName(h1_name.Data());
  h1_copy->SetTitle(h1_title.Data());
  const int n_bins_max = 1000;
  double bins_low_edge[n_bins_max];
  int nBins = h1->GetNbinsX();
  if((nBins+1)>n_bins_max)
    cout<<"ERROR --> (nBins+1)  > n_bins_max"<<endl
	  <<"          nBins      = "<<nBins<<endl
	  <<"          n_bins_max = "<<n_bins_max<<endl;
  for(int i = 0;i<nBins;i++)
    bins_low_edge[i] = h1->GetBinLowEdge(i+1);
  bins_low_edge[nBins] = h1->GetBinLowEdge(nBins) + h1->GetBinWidth(nBins);
  h1_copy->SetBins(nBins,bins_low_edge);
  if(!ifBinsOnly && norm>0.0)
    for(int i = 1;i<=nBins;i++)
      h1_copy->SetBinContent(i,h1->GetBinContent(i)/norm);
}

void terzina::readEventFormRootFile_newFormat( TString inRootFileName_g4s, TString inTrkDataFile_g4s, Double_t particleMomentum){
  //
  _h1_distance = new TH1D();
  _h1_wavelength = new TH1D();
  _h1_timeHist = new TH1D();
  _h1_angleHist = new TH1D();
  //
  _h1_distance->SetName("_h1_distance");
  _h1_wavelength->SetName("_h1_wavelength");
  _h1_timeHist->SetName("_h1_timeHist");
  _h1_angleHist->SetName("_h1_angleHist");
  //
  _h1_distance->SetTitle("_h1_distance");
  _h1_wavelength->SetTitle("_h1_wavelength");
  _h1_timeHist->SetTitle("_h1_timeHist");
  _h1_angleHist->SetTitle("_h1_angleHist");
  //
  _particleMomentum = particleMomentum;
  //
  TString inTrkDataFile = inTrkDataFile_g4s;
  TString mot;
  //
  cout<<"inRootFileName_g4s "<<inRootFileName_g4s<<endl
      <<"inTrkDataFile      "<<inTrkDataFile<<endl;
  //
  //trk info
  std::ifstream trkDataFile(inTrkDataFile.Data());
  if (trkDataFile.is_open()) {
    trkDataFile>>mot
	       >>mot
	       >>mot
	       >>mot
	       >>mot
	       >>mot
	       >>mot
	       >>mot
	       >>mot
	       >>mot
	       >>mot
    	       >>mot;
    trkDataFile>>_trk_info->theta
	       >>_trk_info->phi
	       >>_trk_info->x_int
	       >>_trk_info->y_int
	       >>_trk_info->z_int
	       >>_trk_info->xe0
	       >>_trk_info->ye0
	       >>_trk_info->ze0
	       >>_trk_info->distToEarth
	       >>_trk_info->distToTerzina
	       >>_trk_info->angleTrzinaTrk
	       >>_trk_info->nphotons_per_m2;
    trkDataFile.close();
  }
  else {
    cout << "Unable to open file"<<endl; 
    assert(0);
  }
  //_trk_info->printInfo();
  //assert(0);

  TString inRootFileName = inRootFileName_g4s;
  TFile *f1 = new TFile(inRootFileName.Data());

  TH1D *h1_wavelength = (TH1D*)f1->Get("wl");
  TH1D *h1_distance = (TH1D*)f1->Get("r");
  TH1D *h1_angle_offset = (TH1D*)f1->Get("ang_off");
  TH1D *h1_time_offset = (TH1D*)f1->Get("t_off");
  //double _ThetaAngle_mean_without_offset;
  //double _ThetaAngle_RMS;
  //double _time_mean_without_offset;
  //double _time_RMS;

  copyHistogram(h1_wavelength, _h1_wavelength, "h1_wavelength", "h1_wavelength", false, 1.0);
  copyHistogram(h1_distance, _h1_distance, "h1_distance", "h1_distance", false, 1.0);

  //assert(0);

  auto nBinDist = h1_distance->FindBin(_trk_info->distToTerzina);
  //auto nBinDist = h1_distance->FindBin(5);
  
  //
  TString angle_dist_name = "ang_dist_";
  angle_dist_name += nBinDist;
  //
  TString time_dist_name = "t_dist_";
  time_dist_name += nBinDist;

  //
  //G4cout<<"nBinDist        "<<nBinDist<<G4endl
  //	<<"time_dist_name  "<<time_dist_name<<G4endl
  //	<<"angle_dist_name "<<angle_dist_name<<G4endl;
  //
  
  if(!f1->GetListOfKeys()->Contains(angle_dist_name.Data())){ 
    cout<<"Distance bin does not exist "<<endl;
    assert(0);
  }
  //  
  TH1D *h1_angle_dist = (TH1D*)f1->Get(angle_dist_name.Data());
  TH1D *h1_time_dist = (TH1D*)f1->Get(time_dist_name.Data());
  //
  //h1_angle_dist->SaveAs("h1_angle_dist.C");
  //
  copyHistogram(h1_angle_dist, _h1_angleHist, "h1_angleHist", "h1_angleHist", false, getMaximumHistCount(h1_angle_dist));
  //copyHistogram(h1_angle_dist, _h1_angleHist, "h1_angleHist", "h1_angleHist", false, 1.0);
  copyHistogram(h1_time_dist, _h1_timeHist, "h1_timeHist", "h1_timeHist", false, getMaximumHistCount(h1_time_dist));
  //
  //h1_angle_dist->SaveAs("_h1_angleHist.C");
  //
  _nPhotonsPerM2_scaled_100PeV = _h1_distance->GetBinContent(nBinDist)*_particleMomentum/100.0;
  _nPhotonsPerM2 = _nPhotonsPerM2_scaled_100PeV;
  _ThetaAngle_offset = h1_angle_offset->GetBinContent(nBinDist);
  _time_offset = h1_time_offset->GetBinContent(nBinDist);
  //
  _ThetaAngle_mean_without_offset = _h1_angleHist->GetMean();
  _ThetaAngle_RMS = _h1_angleHist->GetRMS();
  _time_mean_without_offset = _h1_angleHist->GetMean();
  _time_RMS = _h1_timeHist->GetRMS();
  //  
  f1->Close();
  //
  //_trk_info->printInfo();
  //
  //cout<<"_particleName     "<<_particleName<<endl
  // 	<<"_particleMomentum "<<_particleMomentum<<endl
  // 	<<"_PhiAngle         "<<_PhiAngle<<endl
  // 	<<"_ThetaAngle       "<<_ThetaAngle<<endl;
  //
  //cout<<"_ThetaAngle_offset               "<<_ThetaAngle_offset<<endl
  //	<<"_ThetaAngle_mean_without_offset  "<<_ThetaAngle_mean_without_offset<<endl
  //	<<"_ThetaAngle_RMS                  "<<_ThetaAngle_RMS<<endl
  //	<<"_time_offset                     "<<_time_offset<<endl
  //	<<"_time_mean_without_offset        "<<_time_mean_without_offset<<endl
  //	<<"_time_RMS                        "<<_time_RMS<<endl
  //	<<"_DistanceFromTheAxisOfTheShower  "<<_DistanceFromTheAxisOfTheShower<<endl
  //	<<"_nPhotonsPerM2                   "<<_nPhotonsPerM2<<endl
  //	<<"_nPhotonsPerM2_scaled_100PeV     "<<_nPhotonsPerM2_scaled_100PeV<<endl;
  //
  //assert(0);
  //  
  //TFile* rootFile = new TFile("test.root", "RECREATE", " Histograms", 1);
  //rootFile->cd();
  //_h1_wavelength->Write();
  //_h1_distance->Write();
  //_h1_angleHist->Write();
  //_h1_timeHist->Write();
  //rootFile->Close();  
  //
  if(_nPhotonsPerM2<=0){
    cout<<"photon density is low ~ 0 per m^2"<<endl;
    assert(0);
  }
  ////////////////////////
  TFile *f1_cosmique_particle_spectrum = new TFile("../terzinag4/cosmique_particle_spectrum.root");
  f1_cosmique_particle_spectrum->cd();
  cout<<"f1_cosmique_particle_spectrum"<<endl;
  TH1D *h1_particle_per_year = (TH1D*)f1_cosmique_particle_spectrum->Get("h1_particle_per_year");
  copyHistogram(h1_particle_per_year, _h1_particle_per_year, "h1_particle_per_year", "h1_particle_per_year", false, 1.0);
  f1_cosmique_particle_spectrum->Close();
  ////////////////////////
}

double terzina::getMaximumHistCount(TH1D *h1){
  int nn = h1->GetNbinsX()+1;
  double maxVal = -999.0;
  for(Int_t iiii = 1;iiii<=nn;iiii++){
    if(maxVal<h1->GetBinContent(iiii))
      maxVal = h1->GetBinContent(iiii);
  }
  return maxVal;
}
