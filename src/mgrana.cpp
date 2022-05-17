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
  TGraph *gr_npe_th = new TGraph();
  gr_npe_th->SetName("gr_npe_th");
  gr_npe_th->SetTitle("gr_npe_th");
  //
  //
  Long64_t nentries = fChain->GetEntriesFast();
  cout<<"nentries = "<<nentries<<endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    h1_nphotons_per_m2->Fill(nphotons_per_m2);
    h1_nPhot_mean->Fill(nPhot_mean);
    h1_npe_mean->Fill(npe_mean);
    for(i = 0;i<10;i++)
      h1_npe_th->Fill(i+1,npe_th[i]/1000.0/108591.0);
  }
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
  gr_npe_th->Write();
  //
  rootFile->Close();
}
