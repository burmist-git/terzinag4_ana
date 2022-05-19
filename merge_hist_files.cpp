//root
#include "TROOT.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TVector3.h"
#include "TGraph.h"
#include "TMath.h"
#include "TFree.h"
#include "TBranch.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

//C, C++
#include <sys/stat.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <vector>
#include <string>

using namespace std;

TString getTrkInfoFileName(Int_t eventIDmy);
TString get_hist_root_FileName(Int_t eventIDmy, TString ekin_str);
bool file_exists_test(TString inFileName);
void readDatTrkFile(TString fileName, Double_t &theta, Double_t &phi,
		    Double_t &x_int, Double_t &y_int, Double_t &z_int,
		    Double_t &xe0, Double_t &ye0, Double_t &ze0,
		    Double_t &distToEarth, Double_t &distToTerzina, Double_t &angleTrzinaTrk, Double_t &nphotons_per_m2);
void readHistG4File(TString hist_fileName, Double_t &nPhot_mean, Double_t &npe_mean, Int_t npe_th[]);

int main(int argc, char *argv[]){
  if(argc == 4 && atoi(argv[1])==0){
    //theta       phi         x_int         y_int          z_int           xe0           ye0           ze0   distToEarth distToTerzina angleTrzinaTrk nphotons_per_m2
    //1.17783 4.71672 -3.75600184791 4.75931915385 6907.4891108 -14.3110148761 2444.12518573 5896.30158632 11.8148277637 12.9907018941 3.13758826212 6.80357827031
    //
    TString outputRootFile = argv[2];
    Int_t Ekin_in_PeV = atoi(argv[3]);
    cout<<"Ekin_in_PeV "<<Ekin_in_PeV<<endl;
    TString Ekin_in_PeV_str = "";
    Ekin_in_PeV_str += Ekin_in_PeV;
    Ekin_in_PeV_str += "PeV";
    cout<<"Ekin_in_PeV_str "<<Ekin_in_PeV_str<<endl;
    //
    Int_t eventID;
    Double_t theta;
    Double_t phi;
    Double_t x_int, y_int, z_int;
    Double_t xe0, ye0, ze0;
    Double_t distToEarth;
    Double_t distToTerzina;
    Double_t angleTrzinaTrk;
    Double_t nphotons_per_m2;
    //
    Double_t nPhot_mean;
    Double_t npe_mean;
    Int_t npe_th[10];
    //
    TFile *hfile = new TFile(outputRootFile.Data(), "RECREATE", "cosmique proton generator", 1);
    if (hfile->IsZombie()) {
      cout << "PROBLEM with the initialization of the output ROOT ntuple " 
	   << outputRootFile << ": check that the path is correct!!!"
	   << endl;
      assert(0);
    }
    TTree *tree = new TTree("T", "cosmique proton generator");
    hfile->SetCompressionLevel(2);
    tree->SetAutoSave(1000000);
    // Create new event
    TTree::SetBranchStyle(0);
    //
    //
    tree->Branch("eventID",&eventID, "eventID/I");
    //
    tree->Branch("theta",&theta, "theta/D");
    tree->Branch("phi",&phi, "phi/D");
    //
    tree->Branch("x_int",&x_int, "x_int/D");
    tree->Branch("y_int",&y_int, "y_int/D");
    tree->Branch("z_int",&z_int, "z_int/D");
    //
    tree->Branch("xe0",&xe0, "xe0/D");
    tree->Branch("ye0",&ye0, "ye0/D");
    tree->Branch("ze0",&ze0, "ze0/D");
    //
    tree->Branch("distToEarth",&distToEarth, "distToEarth/D");
    tree->Branch("distToTerzina",&distToTerzina, "distToTerzina/D");
    tree->Branch("angleTrzinaTrk",&angleTrzinaTrk, "angleTrzinaTrk/D");
    //
    tree->Branch("nphotons_per_m2",&nphotons_per_m2, "nphotons_per_m2/D");
    //
    tree->Branch("nPhot_mean",&nPhot_mean, "nPhot_mean/D");
    tree->Branch("npe_mean",&npe_mean, "npe_mean/D");
    tree->Branch("npe_th", npe_th, "npe_th[10]/I");
    //  
    TString  fileName;
    TString  hist_fileName;
    for(Int_t i = 0;i<110000;i++){
      //for(Int_t i = 0;i<100;i++){
      eventID = i;
      fileName = getTrkInfoFileName(eventID);
      hist_fileName = get_hist_root_FileName(eventID, Ekin_in_PeV_str);
      if(i%1000==0){
	cout<<i<<endl;
	cout<<fileName<<endl
	    <<hist_fileName<<endl;
      }
      if(file_exists_test(fileName)){
	readDatTrkFile(fileName.Data(), theta, phi, x_int, y_int, z_int, xe0, ye0, ze0, distToEarth, distToTerzina, angleTrzinaTrk, nphotons_per_m2);
	if(file_exists_test(hist_fileName)){
	  readHistG4File(hist_fileName.Data(), nPhot_mean, npe_mean, npe_th);
	  //cout<<fileName<<endl
	  //  <<hist_fileName<<endl
	  //   <<nphotons_per_m2<<endl;
	  //cout<<"nPhot_mean "<<nPhot_mean<<endl
	  //  <<"npe_mean   "<<npe_mean<<endl
	  //  <<"npe_th[9]  "<<npe_th[9]<<endl;
	  tree->Fill();
	}
      }
    }
    //
    hfile = tree->GetCurrentFile();
    hfile->Write();
    hfile->Close();
  }
  else{
    //------------------------------------------------
    cout<<" --> ERROR in input arguments "<<endl
	<<" runID [1] = 0 (execution ID number)"<<endl
	<<"       [2] - output root file"<<endl
	<<"       [3] - Ekin of the trk in PeV (integer)"<<endl;

  }
  return 0;
}

TString getTrkInfoFileName(Int_t eventIDmy){
  // 
  //../../easchersim/root/00000/trkInfo_0000021.dat
  //
  char buffer [8];
  sprintf(buffer ,"%07d", eventIDmy);
  TString rootDir = "../../easchersim/root/";
  Int_t nFilesPerDir = 200;
  Int_t dirNameID = eventIDmy/nFilesPerDir;
  char buffer2 [6];
  sprintf(buffer2 ,"%05d", dirNameID);
  TString fileNameIDstr =  buffer2;
  rootDir += fileNameIDstr;
  rootDir += "/";
  //
  TString fileNameID =  buffer;
  //
  TString fileName = rootDir;
  fileName += "trkInfo_";
  //
  fileName += fileNameID;
  fileName += ".dat";
  //cout<<fileName<<endl;
  return fileName;
}

TString get_hist_root_FileName(Int_t eventIDmy, TString ekin_str){
  // 
  //../hist_root/100PeV/00000/hist_0000000_g4.root
  //
  char buffer [8];
  sprintf(buffer ,"%07d", eventIDmy);
  TString hist_root_Dir = "../hist_root/";
  hist_root_Dir += ekin_str;
  hist_root_Dir += "/";
  Int_t nFilesPerDir = 200;
  Int_t dirNameID = eventIDmy/nFilesPerDir;
  char buffer2 [6];
  sprintf(buffer2 ,"%05d", dirNameID);
  TString fileNameIDstr =  buffer2;
  hist_root_Dir += fileNameIDstr;
  hist_root_Dir += "/";
  //
  TString fileNameID =  buffer;
  //
  TString fileName = hist_root_Dir;
  fileName += "hist_";
  //
  fileName += fileNameID;
  fileName += "_g4.root";
  //cout<<fileName<<endl;
  return fileName;
}

bool file_exists_test (TString inFileName) {
  struct stat buffer;   
  return (stat (inFileName.Data(), &buffer) == 0); 
}

/*
bool file_exists_test(TString inFileName){
  if (FILE *file = fopen(inFileName.Data(), "r")) {
    fclose(file);
    return true;
  }else {
    return false;
  }  
  return false;
}
*/

void readDatTrkFile(TString fileName, Double_t &theta, Double_t &phi, 
		    Double_t &x_int, Double_t &y_int, Double_t &z_int, 
		    Double_t &xe0, Double_t &ye0, Double_t &ze0, 
		    Double_t &distToEarth, Double_t &distToTerzina, Double_t &angleTrzinaTrk, Double_t &nphotons_per_m2){
  x_int = -999.0;
  y_int = -999.0;
  z_int = -999.0;
  xe0 = -999.0;
  ye0 = -999.0;
  ze0 = -999.0;
  distToEarth = -999.0;
  distToTerzina = -999.0;
  angleTrzinaTrk = -999.0;
  nphotons_per_m2 = -999.0;
  //
  ifstream myfile(fileName.Data());
  string mot;
  if(myfile.is_open()){
    for(Int_t i = 0;i<12;i++)
      myfile>>mot;
    myfile>>theta>>phi>>x_int>>y_int>>z_int>>xe0>>ye0>>ze0>>distToEarth>>distToTerzina>>angleTrzinaTrk>>nphotons_per_m2;
    myfile.close();
  }
}

void readHistG4File(TString hist_fileName, Double_t &nPhot_mean, Double_t &npe_mean, Int_t npe_th[]){
  //
  nPhot_mean = 0.0;
  npe_mean = 0.0;
  for(Int_t i = 0;i<=10;i++)
    npe_th[i] = 0;
  TFile *f1 = new TFile(hist_fileName.Data());
  //
  TH1D *h1_1 = (TH1D*)f1->Get("h1_nPhot");
  TH1D *h1_2 = (TH1D*)f1->Get("h1_npe");
  //
  nPhot_mean = h1_1->GetMean();
  npe_mean = h1_2->GetMean();
  //
  for(Int_t i = 0;i<=10;i++)
    npe_th[i] = h1_2->Integral(h1_2->FindBin(i+1),h1_2->GetEntries());
  f1->Close();
}

