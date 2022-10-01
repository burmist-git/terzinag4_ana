//my
#include "mgrana.hh"

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
#include <iomanip>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

void mgrana::Loop(TString histOut){
  Int_t i = 0;
  //
  TH1D *h1_nphotons_per_m2 = new TH1D("h1_nphotons_per_m2","nphotons per m2",1000,0.0,10000);
  TH1D *h1_nPhot_mean = new TH1D("h1_nPhot_mean","nPhot mean",1000,0.0,1000);
  TH1D *h1_npe_mean = new TH1D("h1_npe_mean","h1_npe_mean",1000,0.0,200);
  TH1D *h1_npe_th = new TH1D("h1_npe_th","nPhot mean",12,-0.5,11.5);
  TH1D *h1_theta = new TH1D("h1_theta","thetanPhot",200,66.5,69.5); //deg
  TH1D *h1_distToEarth = new TH1D("h1_distToEarth","distToEarth",100,0.0,70.0);
  TH1D *h1_distToEarth_cut = new TH1D("h1_distToEarth_cut","distToEarth cut",100,0.0,50.0);
  TH1D *h1_distToTerzina = new TH1D("h1_distToTerzina","distToTerzina",80,0.0,40.0);
  TH1D *h1_distToTerzina_cut = new TH1D("h1_distToTerzina_cut","distToTerzina cut",80,0.0,40.0);
  //
  TH2D *h2_distToEarth_vs_theta = new TH2D("h2_distToEarth_vs_theta","distToEarth_vs_theta",50,66.5,69.5,50,0.0,50.0);
  TH2D *h2_distToEarth_vs_theta_norm = new TH2D("h2_distToEarth_vs_theta_norm","distToEarth_vs_theta_norm",50,66.5,69.5,50,0.0,50.0);
  //
  TGraph *gr_npe_th = new TGraph();
  gr_npe_th->SetName("gr_npe_th");
  gr_npe_th->SetTitle("gr_npe_th");
  //
  //
  Double_t theta_deg = 0.0;
  //
  Long64_t nentries = fChain->GetEntriesFast();
  cout<<"nentries = "<<nentries<<endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    //
    theta_deg = theta*180.0/TMath::Pi();
    //
    h1_nphotons_per_m2->Fill(nphotons_per_m2);
    h1_nPhot_mean->Fill(nPhot_mean);
    h1_npe_mean->Fill(npe_mean);
    h1_theta->Fill(theta_deg);
    h1_distToEarth->Fill(distToEarth);
    h1_distToEarth_cut->Fill(distToEarth,npe_th[6]/1000.0/108591.0);
    h1_distToTerzina->Fill(distToTerzina);
    h1_distToTerzina_cut->Fill(distToTerzina,npe_th[6]/1000.0/108591.0);
    for(i = 0;i<10;i++)
      h1_npe_th->Fill(i+1,npe_th[i]/1000.0/108591.0);
    if(npe_th[6]>100 && distToTerzina> 14.9 && distToTerzina<15.1)
      cout<<eventID<<endl;
    //
    h2_distToEarth_vs_theta->Fill(theta_deg,distToEarth,nphotons_per_m2);
    h2_distToEarth_vs_theta_norm->Fill(theta_deg,distToEarth);
    //
  }
  //
  hist2Dnorm(h2_distToEarth_vs_theta, h2_distToEarth_vs_theta_norm);
  //
  TFile* rootFile = new TFile(histOut.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<histOut.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<histOut.Data()<<endl;
  //
  for(i = 2;i<h1_npe_th->GetNbinsX();i++){
    gr_npe_th->SetPoint(gr_npe_th->GetN(),i-1,h1_npe_th->GetBinContent(i));
    //cout<<gr_npe_th->GetN()<<endl
    //	<<i-1<<endl
    //	<<h1_npe_th->GetBinContent(i)<<endl;
  }
  //
  h1_nphotons_per_m2->Write();
  h1_nPhot_mean->Write();
  h1_npe_mean->Write();
  h1_npe_th->Write();
  //
  h1_theta->Write();
  h1_distToEarth->Write();
  h1_distToEarth_cut->Write();
  //
  h1_distToTerzina->Write();
  h1_distToTerzina_cut->Write();
  //
  gr_npe_th->Write();
  //
  h2_distToEarth_vs_theta->Write();
  h2_distToEarth_vs_theta_norm->Write();
  //
  rootFile->Close();
}
