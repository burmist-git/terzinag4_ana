#ifndef mgranabase_hh
#define mgranabase_hh

#include <TROOT.h>

class TChain;
class TFile;
class TTree;
class TString;
class TBranch;
class TGraph;
class TH1D;
class TH2D;
class TProfile;

class mgranabase {

public :
  mgranabase(TString fileList);
  mgranabase(TString inFileName, Int_t keyID);
  ~mgranabase();
  Int_t GetEntry(Long64_t entry);
  Long64_t LoadTree(Long64_t entry);
  void Init(TTree *tree);
  void Loop(TString histOut);
  Bool_t Notify();
  void Show(Long64_t entry = -1);
  Int_t Cut(Long64_t entry);

protected :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  //
  // Declaration of leaf types
  Int_t           eventID;
  Double_t        theta;
  Double_t        phi;
  Double_t        x_int;
  Double_t        y_int;
  Double_t        z_int;
  Double_t        xe0;
  Double_t        ye0;
  Double_t        ze0;
  Double_t        distToEarth;
  Double_t        distToTerzina;
  Double_t        angleTrzinaTrk;
  Double_t        nphotons_per_m2;
  Double_t        nPhot_mean;
  Double_t        npe_mean;
  Int_t           npe_th[10];
  //---------------------------------------------------
  // ADD HERE :
  //Tree name
  //const TString treeName = "arich";
  const TString treeName = "T";
  static const Int_t nChannels = 10;
  //---------------------------------------------------
  
  // List of branches
  //
  //---------------------------------------------------
  // ADD HERE :
  TBranch        *b_eventID;   //!
  TBranch        *b_theta;   //!
  TBranch        *b_phi;   //!
  TBranch        *b_x_int;   //!
  TBranch        *b_y_int;   //!
  TBranch        *b_z_int;   //!
  TBranch        *b_xe0;   //!
  TBranch        *b_ye0;   //!
  TBranch        *b_ze0;   //!
  TBranch        *b_distToEarth;   //!
  TBranch        *b_distToTerzina;   //!
  TBranch        *b_angleTrzinaTrk;   //!
  TBranch        *b_nphotons_per_m2;   //!
  TBranch        *b_nPhot_mean;   //!
  TBranch        *b_npe_mean;   //!
  TBranch        *b_npe_th;   //!
  //---------------------------------------------------
  void tGraphInit(TGraph *gr[nChannels], TString grName, TString grTitle);
  void h1D1Init(TH1D *h1D1[nChannels],TString h1name, TString h1Title,
		Int_t Nbin, Float_t Vmin, Float_t Vmax);
  void h2D2Init(TH2D *h2D1[nChannels],TString h2name, TString h2Title,
                Int_t Nbin1, Float_t Vmin1, Float_t Vmax1,
                Int_t Nbin2, Float_t Vmin2, Float_t Vmax2);
  void tProfInit(TProfile *tprof[nChannels],TString prname, TString prTitle,
                 Int_t Nbin, Float_t Vmin, Float_t Vmax);
  double getUnixTimeFromTime(double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec);  
  //
  void hist2Dnorm(TH2D *h2, TH2D *h2norm);  
  //  
};

#endif
