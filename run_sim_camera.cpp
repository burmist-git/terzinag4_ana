//my
#include "src/CameraPlaneHist.hh"

//root
#include "TROOT.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TMath.h"

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

Double_t getSigma(Double_t x0, Double_t y0,TGraph *gr_PSF_sigma);
void load_Sigma_gr(TString fileInName, TGraph *gr);

int main(int argc, char *argv[]){
  if(argc == 6 && atoi(argv[1])==0){
    //
    Int_t nEvents = atoi(argv[2]);
    Double_t n_average_number_of_pe = atof(argv[3]);
    Double_t signal_threshold = atof(argv[4]);
    TString fileInName_with_PSF = argv[5];
    //
    cout<<"nEvents                "<<nEvents<<endl
	<<"n_average_number_of_pe "<<n_average_number_of_pe<<endl
      	<<"signal_threshold       "<<signal_threshold<<endl
	<<"fileInName_with_PSF    "<<fileInName_with_PSF<<endl;
    //
    Double_t x0 = 0.0;
    Double_t y0 = 0.0;
    Double_t sigma = 1.0;
    Int_t number_of_pe = 0;
    //
    Double_t xMin = -60.0;
    Double_t xMax =  60.0;
    Double_t yMin = -22.0;
    Double_t yMax =  22.0;
    //
    Int_t nch;
    Int_t npe;
    //
    Double_t r;
    //
    Double_t theta;
    //
    TH1D *h1_theta = new TH1D("h1_theta","theta",100,0.0,5.0);
    TH1D *h1_nchannels = new TH1D("h1_nchannels","theta",21,-0.5,20.5);
    TH1D *h1_npe = new TH1D("h1_npe","npe",201,-0.5,200.5);
    //
    TRandom3 *rnd = new TRandom3(123123);    
    //
    TGraph *gr_PSF_sigma = new TGraph();
    load_Sigma_gr( fileInName_with_PSF, gr_PSF_sigma);    
    //
    //cp_h2->test();
    //assert(0);
    ///////////////////
    CameraPlaneHist *cp_h2 = new CameraPlaneHist("cp_h2","cp_h2");
    CameraPlaneHist *cp_h2_towrite = new CameraPlaneHist("cp_h2_towrite","cp_h2_towrite");
    for(Int_t j = 0; j<nEvents;j++){
      x0 = rnd->Uniform( xMin, xMax);
      y0 = rnd->Uniform( yMin, yMax);
      r = TMath::Sqrt(x0*x0 + y0*y0);
      theta = r*3.5/57.1;
      h1_theta->Fill(theta);
      sigma = getSigma(x0,y0,gr_PSF_sigma);
      //cout<<"sigma "<<sigma<<endl;
      number_of_pe = rnd->Poisson(n_average_number_of_pe);
      cp_h2->Clean();
      //cout<<"number_of_pe "<<number_of_pe<<endl;
      for(Int_t i = 0; i<number_of_pe;i++){
	cp_h2->Fill(rnd->Gaus(x0,sigma),rnd->Gaus(y0,sigma));
	cp_h2_towrite->Fill(rnd->Gaus(x0,sigma),rnd->Gaus(y0,sigma));
      }
      //cp_h2->Clean();
      cp_h2->count_signal(signal_threshold,nch,npe);
      if(npe>0){
	h1_nchannels->Fill(nch);
	h1_npe->Fill(npe);
      }
    }
    ///////////////////
    //
    TString outRootFileF = "./run_sim_camera.root";
    TFile* rootFile = new TFile(outRootFileF.Data(), "RECREATE", " Histograms", 1);
    rootFile->cd();
    if (rootFile->IsZombie()){
      cout<<"  ERROR ---> file "<<outRootFileF.Data()<<" is zombi"<<endl;
      assert(0);
    }
    else
      cout<<"  Output Histos file ---> "<<outRootFileF.Data()<<endl;
    //
    h1_theta->Write();
    h1_nchannels->Write();
    h1_npe->Write();
    cp_h2_towrite->Write();
    //
    rootFile->Close();
  }
  else{
    //------------------------------------------------
    cout<<" --> ERROR in input arguments "<<endl
	<<" runID [1] = 0 (execution ID number)"<<endl
      	<<"       [2] - n events"<<endl
	<<"       [3] - average number of pe"<<endl
	<<"       [4] - file name with PSF"<<endl;
  }
  return 0;
}

Double_t getSigma(Double_t x0, Double_t y0,TGraph *gr_PSF_sigma){
  Double_t r = TMath::Sqrt(x0*x0 + y0*y0);
  return gr_PSF_sigma->Eval(r);
}

void load_Sigma_gr(TString fileInName, TGraph *gr){
  ifstream fileIn(fileInName.Data());
  Double_t x;
  Double_t y;
  if(fileIn.is_open()){
    while(fileIn>>x>>y){
      //cout<<x<<endl
      //  <<y<<endl;
      gr->SetPoint(gr->GetN(),x,y);
    }
    fileIn.close();
  }
  else{
    cout<<"Unable to open file \n";
  }
  //assert(0);
}
