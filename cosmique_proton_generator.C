//root
#include "TROOT.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TVector3.h"
#include "TGraph.h"
#include "TMath.h"
#include "TFree.h"
#include "TBranch.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <vector>

using namespace std;

////
const Double_t earthR = 6371;                           // km
const Double_t earthD = earthR*2;                       // km
const Double_t satelliteH = 525;                        // km
const Double_t satelliteH_from_c = earthR + satelliteH; // km
const Double_t track_speed = TMath::C()/1000;           // km/s
////
const TVector3 terzina_r0(0.0,0.0,satelliteH_from_c);
const TVector3 terzina_n0(0.0,earthR/satelliteH_from_c,-TMath::Cos(TMath::ASin(earthR/satelliteH_from_c)));
//TVector3 terzina_n0(0.0,1.0,0.0);
////
void genTrk(Double_t &x0, Double_t &y0, Double_t &z0, Double_t &vx, Double_t &vy, Double_t &vz, Double_t &theta, Double_t &phi, TRandom3 *rnd);
Bool_t getIntersection(Double_t &x_int, Double_t &y_int, Double_t &z_int, Double_t x0, Double_t y0, Double_t z0, Double_t vx, Double_t vy, Double_t vz);
Double_t getDistToEarth(Double_t x0, Double_t y0, Double_t z0, Double_t vx, Double_t vy, Double_t vz);
Double_t getDistToTerzinaOfIntersection(Double_t x_int, Double_t y_int, Double_t z_int);
Double_t getAngleBetweenTrzinaAndTrk(Double_t vx, Double_t vy, Double_t vz);

int main(int argc, char *argv[]){
  if(argc == 5 && atoi(argv[1])==0){
    //
    Int_t nEvents = atoi(argv[2]);
    TString outputRootFile = argv[3];
    Int_t randomSeed = atoi(argv[4]);
    //
    cout<<"nEvents        "<<nEvents<<endl
	<<"outputRootFile "<<outputRootFile<<endl
      	<<"randomSeed     "<<randomSeed<<endl;
    //
    TRandom3 *rnd = new TRandom3(randomSeed);
    //
    Double_t x0, y0, z0;
    Double_t vx, vy, vz;
    Double_t theta;
    Double_t phi;
    Double_t x_int, y_int, z_int;
    Double_t distToEarth;
    Double_t distToTerzina;
    Double_t angleTrzinaTrk;
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
    tree->Branch("x0",&x0, "x0/D");
    tree->Branch("y0",&y0, "y0/D");
    tree->Branch("z0",&z0, "z0/D");
    //
    tree->Branch("vx",&vx, "vx/D");
    tree->Branch("vy",&vy, "vy/D");
    tree->Branch("vz",&vz, "vz/D");
    //
    tree->Branch("theta",&theta, "theta/D");
    tree->Branch("phi",&phi, "phi/D");
    //
    tree->Branch("x_int",&x_int, "x_int/D");
    tree->Branch("y_int",&y_int, "y_int/D");
    tree->Branch("z_int",&z_int, "z_int/D");
    //
    tree->Branch("distToEarth",&distToEarth, "distToEarth/D");
    tree->Branch("distToTerzina",&distToTerzina, "distToTerzina/D");
    tree->Branch("angleTrzinaTrk",&angleTrzinaTrk, "angleTrzinaTrk/D");
    //
    for(Int_t i = 0;i<nEvents;i++){
      genTrk(x0, y0, z0, vx, vy, vz, theta, phi,rnd);
      if(getIntersection(x_int, y_int, z_int, x0, y0, z0, vx, vy, vz)){
	distToTerzina = getDistToTerzinaOfIntersection(x_int, y_int, z_int);
	if(distToTerzina<40.0){
	  distToEarth = getDistToEarth( x0, y0, z0, vx, vy, vz);
	  if(distToEarth>=0.0 && distToEarth<60.0){
	    angleTrzinaTrk = getAngleBetweenTrzinaAndTrk( vx, vy, vz);
	    tree->Fill();
	  }
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
      	<<"       [2] - n events"<<endl
	<<"       [3] - output root file"<<endl
	<<"       [4] - random seed"<<endl;
  }
  return 0;
}

Double_t getDistToTerzinaOfIntersection(Double_t x_int, Double_t y_int, Double_t z_int){
  TVector3 v_int(x_int,y_int,z_int);
  TVector3 v = terzina_r0 - v_int;
  return v.Mag();
}

void genTrk(Double_t &x0, Double_t &y0, Double_t &z0, Double_t &vx, Double_t &vy, Double_t &vz, Double_t &theta, Double_t &phi, TRandom3 *rnd){
  //
  Double_t theta_r0 = TMath::ACos(rnd->Uniform(-1.0,1.0));
  Double_t phi_r0   = rnd->Uniform(0.0,TMath::TwoPi());
  theta  = TMath::ACos(rnd->Uniform(-1.0,1.0));
  phi    = rnd->Uniform(0.0,TMath::TwoPi());
  TVector3 v_r0;
  TVector3 v_v;
  v_r0.SetMagThetaPhi(satelliteH_from_c,theta_r0,phi_r0);
  v_v.SetMagThetaPhi(track_speed,theta,phi);
  x0 = v_r0.x();
  y0 = v_r0.y();
  z0 = v_r0.z();
  vx = v_v.x();
  vy = v_v.y();
  vz = v_v.z();
}

Bool_t getIntersection(Double_t &x_int, Double_t &y_int, Double_t &z_int, Double_t x0, Double_t y0, Double_t z0, Double_t vx, Double_t vy, Double_t vz){
  //
  TVector3 v_r0(x0,y0,z0);
  TVector3 v_v(vx,vy,vz);
  //  
  Double_t div = terzina_n0.Dot(v_v);
  if(div == 0.0)
    return false;
  Double_t t = (terzina_n0.Dot(terzina_r0) - terzina_n0.Dot(v_r0))/div;
  if(t<=0.0)
    return false;
  //
  TVector3 v;
  v = v_r0 + v_v*t;
  x_int = v.x();
  y_int = v.y();
  z_int = v.z();
  if(TMath::Abs(x_int)>earthD)
    return false;
  if(TMath::Abs(y_int)>earthD)
    return false;
  if(TMath::Abs(z_int)>earthD)
    return false;
  return true;
}

Double_t getDistToEarth(Double_t x0, Double_t y0, Double_t z0, Double_t vx, Double_t vy, Double_t vz){
  //
  TVector3 v_r0(x0,y0,z0);
  TVector3 v_v(vx,vy,vz);
  //
  Double_t div = v_v.Dot(v_v);
  if(div == 0.0)
    assert(0);
  Double_t t = -v_r0.Dot(v_v)/div;
  TVector3 v;
  v = v_r0 + v_v*t;
  return (v.Mag()-earthR);
}

Double_t getAngleBetweenTrzinaAndTrk(Double_t vx, Double_t vy, Double_t vz){
  TVector3 v_v(vx,vy,vz);
  return TMath::ACos(v_v.Dot(terzina_n0)/v_v.Mag()/terzina_n0.Mag());
}
