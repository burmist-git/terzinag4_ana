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

Double_t getSigma(Double_t x0, Double_t y0,TGraph *gr_PSF_sigma);
void load_Sigma_gr(TString fileInName, TGraph *gr);
void readEventFormRootFile(TString inRootFileName_g4s, Double_t distanceFromTheAxisOfTheShower, TH1D *_h1_distance, TH1D *_h1_wavelength, TH1D *_h1_timeHist, TH1D *_h1_angleHist,
			   Double_t &_ThetaAngle_offset, Double_t &_ThetaAngle_mean_without_offset, Double_t &_ThetaAngle_RMS,
			   Double_t &_time_offset, Double_t &_time_mean_without_offset, Double_t &_time_RMS,
			   Double_t &_nPhotonsPerM2);
void copyHistogram(TH1D *h1, TH1D *h1_copy, TString h1_name_g, TString h1_title_g, bool ifBinsOnly, double norm);
double generateDistFromHist(TH1D *h1, TRandom3 *rnd);

int main(int argc, char *argv[]){
  if(argc == 8 && atoi(argv[1])==0){
    //
    Int_t nEvents = atoi(argv[2]);
    Double_t n_average_number_of_pe = atof(argv[3]);
    Double_t signal_threshold = atof(argv[4]);
    TString fileInName_with_PSF = argv[5];
    TString inRootFileName_g4s = argv[6];
    Double_t distanceFromTheAxisOfTheShower = atof(argv[7]);
    //
    cout<<"nEvents                        "<<nEvents<<endl
	<<"n_average_number_of_pe         "<<n_average_number_of_pe<<endl
      	<<"signal_threshold               "<<signal_threshold<<endl
	<<"fileInName_with_PSF            "<<fileInName_with_PSF<<endl
    	<<"inRootFileName_g4s             "<<inRootFileName_g4s<<endl
    	<<"distanceFromTheAxisOfTheShower "<<distanceFromTheAxisOfTheShower<<endl;
    //
    // Read Sim Event
    TH1D *_h1_distance = new TH1D();
    _h1_distance->SetName("_h1_distance");
    _h1_distance->SetTitle("_h1_distance");
    TH1D *_h1_wavelength = new TH1D();
    _h1_wavelength->SetName("_h1_wavelength");
    _h1_wavelength->SetTitle("_h1_wavelength");
    TH1D *_h1_timeHist = new TH1D();
    _h1_timeHist->SetName("_h1_timeHist");
    _h1_timeHist->SetTitle("_h1_timeHist");
    TH1D *_h1_angleHist = new TH1D();
    _h1_angleHist->SetName("_h1_angleHist");
    _h1_angleHist->SetTitle("_h1_angleHist");
    //
    Double_t _ThetaAngle_offset;
    Double_t _ThetaAngle_mean_without_offset;
    Double_t _ThetaAngle_RMS;
    Double_t _time_offset;
    Double_t _time_mean_without_offset;
    Double_t _time_RMS;
    Double_t _nPhotonsPerM2;
    //
    TRandom3 *rnd = new TRandom3(123123);
    //
    readEventFormRootFile(inRootFileName_g4s, distanceFromTheAxisOfTheShower,
			  _h1_distance, _h1_wavelength, _h1_timeHist, _h1_angleHist,
			  _ThetaAngle_offset, _ThetaAngle_mean_without_offset, _ThetaAngle_RMS,
			  _time_offset, _time_mean_without_offset, _time_RMS,
			  _nPhotonsPerM2);
    //
    cout<<"_ThetaAngle_offset              "<<_ThetaAngle_offset<<endl
	<<"_ThetaAngle_mean_without_offset "<<_ThetaAngle_mean_without_offset<<endl
	<<"_ThetaAngle_RMS                 "<<_ThetaAngle_RMS<<endl
	<<"_time_offset                    "<<_time_offset<<endl
	<<"_time_mean_without_offset       "<<_time_mean_without_offset<<endl
	<<"_time_RMS                       "<<_time_RMS<<endl
	<<"_nPhotonsPerM2                  "<<_nPhotonsPerM2<<endl;
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
    TH1D *h1_time_all = new TH1D("h1_time_all","h1_time_all",1000,0.0,1000.0);
    //
    TGraph *gr_PSF_sigma = new TGraph();
    load_Sigma_gr( fileInName_with_PSF, gr_PSF_sigma);    
    //
    //cp_h2->test();
    //assert(0);
    ///////////////////
    Int_t n_time_samples = 20;
    Double_t time_bin    = 5.0; //ns
    TH1D *h1_time_bin_all = new TH1D("h1_time_bin_all","h1_time_bin_all",n_time_samples,0.0,n_time_samples*time_bin);
    TH2D *h2_nchannels_vs_time = new TH2D("h2_nchannels_vs_time","h2_nchannels_vs_time",21,-0.5,20.5,n_time_samples,0.0,n_time_samples*time_bin);
    TH2D *h2_npe_vs_time = new TH2D("h2_npe_vs_time","h2_npe_vs_time",201,-0.5,200.5,n_time_samples,0.0,n_time_samples*time_bin);
    vector<CameraPlaneHist*> cp_h2_arr;
    //
    for(Int_t ii = 0; ii<n_time_samples;ii++){
      TString cp_h2_title = "cp_h2_time_bin_"; cp_h2_title += ii;
      TString cp_h2_name = "cp_h2_time_bin_"; cp_h2_name += ii;
      CameraPlaneHist *cp_h2 = new CameraPlaneHist(cp_h2_title.Data(), cp_h2_name.Data());
      cp_h2_arr.push_back(cp_h2);
    }
    CameraPlaneHist *cp_h2_towrite = new CameraPlaneHist("cp_h2_towrite","cp_h2_towrite");
    Double_t photon_time;
    Int_t nBinDist;
    //std::cout<<"nBinDist "<<nBinDist<<std::endl;
    //nBinDist = h1_time_bin_all->FindBin(2.5);
    //std::cout<<"nBinDist "<<nBinDist<<std::endl;
    //nBinDist = h1_time_bin_all->FindBin(5);
    //std::cout<<"nBinDist "<<nBinDist<<std::endl;
    //nBinDist = h1_time_bin_all->FindBin(5.1);
    //std::cout<<"nBinDist "<<nBinDist<<std::endl;
    //

    for(Int_t j = 0; j<nEvents;j++){
      x0 = rnd->Uniform( xMin, xMax);
      y0 = rnd->Uniform( yMin, yMax);
      r = TMath::Sqrt(x0*x0 + y0*y0);
      theta = r*3.5/57.1;
      h1_theta->Fill(theta);
      sigma = getSigma(x0,y0,gr_PSF_sigma);
      //cout<<"sigma "<<sigma<<endl;
      number_of_pe = rnd->Poisson(n_average_number_of_pe);
      for(Int_t ii = 0; ii<n_time_samples;ii++)
	cp_h2_arr.at(ii)->Clean();
      //cout<<"number_of_pe "<<number_of_pe<<endl;
      for(Int_t i = 0; i<number_of_pe;i++){
	photon_time = generateDistFromHist(_h1_timeHist,rnd);
	nBinDist = h1_time_bin_all->FindBin(photon_time);
	if(nBinDist>=0 && nBinDist<n_time_samples)
	  cp_h2_arr.at((nBinDist-1))->Fill(rnd->Gaus(x0,sigma),rnd->Gaus(y0,sigma));
	cp_h2_towrite->Fill(rnd->Gaus(x0,sigma),rnd->Gaus(y0,sigma));
	h1_time_all->Fill(photon_time);
	h1_time_bin_all->Fill(photon_time);
	//auto nBinDist = distance->FindBin(dist);
	//std::cout<<"nBinDist "<<nBinDist<<std::endl;
      }
      nch = 0;
      npe = 0;
      for(Int_t ii = 0; ii<n_time_samples;ii++){
	Int_t nch_bin_t = 0;
	Int_t npe_bin_t = 0;
	cp_h2_arr.at(ii)->count_signal(signal_threshold,nch_bin_t,npe_bin_t);
	if(nch_bin_t>0)
	 h2_nchannels_vs_time->Fill(nch_bin_t,(ii*time_bin + time_bin/2.0));
	if(npe_bin_t>0)
	  h2_npe_vs_time->Fill(npe_bin_t,(ii*time_bin + time_bin/2.0));
	nch = nch + nch_bin_t;
	npe = npe + npe_bin_t;
      }
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
    h1_time_all->Write();
    h1_time_bin_all->Write();
    //
    h2_nchannels_vs_time->Write();
    h2_npe_vs_time->Write();
    //
    _h1_distance->Write();
    _h1_wavelength->Write();
    _h1_timeHist->Write();
    _h1_angleHist->Write();
    //
    rootFile->Close();
  }
  else{
    //------------------------------------------------
    cout<<" --> ERROR in input arguments "<<endl
	<<" runID [1] = 0 (execution ID number)"<<endl
      	<<"       [2] - n events"<<endl
	<<"       [3] - average number of pe"<<endl
	<<"       [4] - threshold"<<endl
	<<"       [5] - file name with PSF"<<endl
      	<<"       [6] - name of the root file with simulated shower"<<endl
      	<<"       [7] - distance from the axis of the shower"<<endl;
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

void readEventFormRootFile(TString inRootFileName_g4s, Double_t distanceFromTheAxisOfTheShower, TH1D *_h1_distance, TH1D *_h1_wavelength, TH1D *_h1_timeHist, TH1D *_h1_angleHist,
			   Double_t &_ThetaAngle_offset, Double_t &_ThetaAngle_mean_without_offset, Double_t &_ThetaAngle_RMS,
			   Double_t &_time_offset, Double_t &_time_mean_without_offset, Double_t &_time_RMS,
			   Double_t &_nPhotonsPerM2){
  
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

  _ThetaAngle_offset = angle_offset->GetBinContent(nBinDist);
  
  //----------------------------------------------------------------------------------------
  // Angle distribution
  TTreeReader fReaderCherPh_angle;
  TTreeReaderValue<std::vector<TH1D>> fDistAngleVec = {fReaderCherPh_angle, "angle_dist"};
  fReaderCherPh_angle.SetTree("cherPhProp");
  fReaderCherPh_angle.SetEntry(0);
  TH1D *angleHist = NULL;
  angleHist = (TH1D*)((*fDistAngleVec)[nBinDist-1]).Clone();

  _ThetaAngle_mean_without_offset = angleHist->GetMean();
  _ThetaAngle_RMS = angleHist->GetRMS();

  _time_offset = time_offset->GetBinContent(nBinDist);
  _time_mean_without_offset = timeHist->GetMean();
  _time_RMS = timeHist->GetRMS();
  
  //----------------------------------------------------------------------------------------
  copyHistogram(distance, _h1_distance, "h1_distance", "h1_distance", false, 1.0);
  copyHistogram(wavelength, _h1_wavelength, "h1_wavelength", "h1_wavelength", false, wavelength->Integral(1,wavelength->GetNbinsX()));  
  //
  double nphotons_per_m2 = _h1_distance->GetBinContent((int)nBinDist);    
  _nPhotonsPerM2 = nphotons_per_m2;
  copyHistogram(timeHist,_h1_timeHist,"h1_timeHist","h1_timeHist",false,nphotons_per_m2);
  copyHistogram(angleHist,_h1_angleHist,"h1_angleHist","h1_angleHist",false,nphotons_per_m2);
  //
  std::cout<<"nBinDist               "<<nBinDist<<std::endl
	   <<"nphotons_per_m2        "<<nphotons_per_m2<<std::endl
    	   <<"_ThetaAngle_offset_deg "<<_ThetaAngle_offset<<std::endl
	   <<"_ThetaAngle_mean_without_offset_deg "<<_ThetaAngle_mean_without_offset<<std::endl
	   <<"_ThetaAngle_RMS_deg    "<<_ThetaAngle_RMS<<std::endl
	   <<"timeHist int.          "<<timeHist->Integral(1,timeHist->GetNbinsX())<<std::endl
	   <<"angleHist int.         "<<angleHist->Integral(1,angleHist->GetNbinsX())<<std::endl
    	   <<"_h1_wavelength int.    "<<_h1_wavelength->Integral(1,_h1_wavelength->GetNbinsX())<<std::endl
	   <<"_h1_timeHist int.      "<<_h1_timeHist->Integral(1,_h1_timeHist->GetNbinsX())<<std::endl
	   <<"_h1_angleHist int.     "<<_h1_angleHist->Integral(1,_h1_angleHist->GetNbinsX())<<std::endl;
  
  fIn->Close();
}

void copyHistogram(TH1D *h1, TH1D *h1_copy, TString h1_name_g, TString h1_title_g, bool ifBinsOnly, double norm){
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

double generateDistFromHist(TH1D *h1, TRandom3 *rnd){
  int nn = h1->GetNbinsX()+1;
  int binI;
  double val;
  bool go = false;
  double binL;
  double binR;
  while( go == false ){
    binI = (int)rnd->Uniform(1,nn);
    val = h1->GetBinContent(binI);
    if(val>=rnd->Uniform(0.0,1.0)){
      binL = h1->GetBinLowEdge(binI);
      binR = binL + h1->GetBinWidth(binI);
      go = true;
      return rnd->Uniform(binL,binR);
    }
  }
  return -999.0;
}
