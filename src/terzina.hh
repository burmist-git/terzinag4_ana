#ifndef terzina_hh
#define terzina_hh

//My
#include "terzinabase.hh"

//root
#include <TROOT.h>

class TChain;
class TH1D;
class TFile;
class TTree;
class TGraph;
class TString;
class TBranch;
class TRandom3;
struct sim_trk_info_str;

class terzina: public terzinabase {
public:

  terzina(TString fileList);
  terzina(TString file, Int_t key);
  ~terzina();


  void Loop(TString histOut);
  void showerSim(TString inRootFileWithShower, TString inDatFileShower, Double_t particleMomentum, TString outRootFileF);
  void readEventFormRootFile(TString inRootFileName_g4s, Double_t distanceFromTheAxisOfTheShower);
  void readEventFormRootFile_newFormat( TString inRootFileName_g4s, TString inTrkDataFile_g4s, Double_t particleMomentum);
  double generateDistFromHist(TH1D *h1, TRandom3 *rnd);  
  void copyHistogram(TH1D *h1, TH1D *h1_copy, TString h1_name_g, TString h1_title_g, bool ifBinsOnly, double norm);
  void read_Eff_vs_wl(TString datafileIn, TGraph *gr, TString nameTitle);
  Bool_t ifQE(Double_t wl, TString qe_ID, TRandom3 *rnd);
  double getMaximumHistCount(TH1D *h1);

  Bool_t if_mirror(Double_t wl, TString mirror_ID, TRandom3 *rnd);
  Bool_t if_lens(Double_t wl, TString lens_ID, TRandom3 *rnd);
  Bool_t if_package_fill_factor(TString package_ID, TRandom3 *rnd);
  Bool_t crosstalk(Double_t prob, TRandom3 *rnd);

private:
  
  TH1D *_h1_distance;
  TH1D *_h1_wavelength;
  TH1D *_h1_timeHist;
  TH1D *_h1_angleHist;
  TGraph *_gr_QE_NUVHD;
  TGraph *_gr_mirror_Reflectance_Unpolarized;
  sim_trk_info_str *_trk_info;
  TH1D *_h1_particle_per_year;

  Int_t _nPhotonsPerM2;
  Double_t _particleMomentum;
  Double_t _ThetaAngle_offset;
  Double_t _ThetaAngle_mean_without_offset;
  Double_t _ThetaAngle_RMS;
  Double_t _time_offset;
  Double_t _time_mean_without_offset;
  Double_t _time_RMS;
  Double_t _DistanceFromTheAxisOfTheShower;
  Double_t _nPhotonsPerM2_scaled_100PeV;

};

#endif
