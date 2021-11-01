#ifndef terzinabase_hh
#define terzinabase_hh

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

class terzinabase {

public :
  terzinabase(TString fileList);
  terzinabase(TString inFileName, Int_t keyID);
  ~terzinabase();
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
  //Int_t           evt;
  //Int_t           run;
  //Float_t         pValue;
  //...
  //...
  //
  //---------------------------------------------------
  // ADD HERE :
  //Tree name
  //const TString treeName = "arich";
  const TString treeName = "T";
  static const Int_t nChannels = 1; //max namber of photons
  // Fixed size dimensions of array or collections stored in the TTree if any.
  // Declaration of leaf types
  Int_t           EventID;
  Int_t           BunchXID;
  Int_t           NTotPhot;
  Int_t           Nhits;
  Int_t           primType;
  Double_t        primMomX;
  Double_t        primMomY;
  Double_t        primMomZ;
  Double_t        primPosX;
  Double_t        primPosY;
  Double_t        primPosZ;
  Double_t        primTime;
  Double_t        trigTopL;
  Double_t        trigTopEdep;
  Double_t        trigBotL;
  Double_t        trigBotEdep;
  Int_t           nPhot;
  Int_t           TrackID[nChannels];   //[nPhot]
  Int_t           ParentID[nChannels];   //[nPhot]
  Double_t        Energy[nChannels];   //[nPhot]
  Double_t        Wavelength[nChannels];   //[nPhot]
  Double_t        Time[nChannels];   //[nPhot]
  Double_t        photPathLen[nChannels];   //[nPhot]
  Int_t           SecID[nChannels];   //[nPhot]
  Int_t           chID[nChannels];   //[nPhot]
  Double_t        PosX[nChannels];   //[nPhot]
  Double_t        PosY[nChannels];   //[nPhot]
  Double_t        PosZ[nChannels];   //[nPhot]
  Double_t        MomX[nChannels];   //[nPhot]
  Double_t        MomY[nChannels];   //[nPhot]
  Double_t        MomZ[nChannels];   //[nPhot]
  Double_t        trkMomX[nChannels];   //[nPhot]
  Double_t        trkMomY[nChannels];   //[nPhot]
  Double_t        trkMomZ[nChannels];   //[nPhot]
  Double_t        trkPosX[nChannels];   //[nPhot]
  Double_t        trkPosY[nChannels];   //[nPhot]
  Double_t        trkPosZ[nChannels];   //[nPhot]
  Double_t        trkT[nChannels];   //[nPhot]
  Double_t        trkLength[nChannels];   //[nPhot]
  //---------------------------------------------------
  
  // List of branches
  //TBranch        *b_evt;
  //TBranch        *b_run;
  //TBranch        *b_pValue;
  //...
  //...
  //
  //---------------------------------------------------
  // ADD HERE :
  TBranch        *b_Event;   //!
  TBranch        *b_BunchXID;   //!
  TBranch        *b_NTotPhot;   //!
  TBranch        *b_Nhits;   //!
  TBranch        *b_primType;   //!
  TBranch        *b_primMomX;   //!
  TBranch        *b_primMomY;   //!
  TBranch        *b_primMomZ;   //!
  TBranch        *b_primPosX;   //!
  TBranch        *b_primPosY;   //!
  TBranch        *b_primPosZ;   //!
  TBranch        *b_primTime;   //!
  TBranch        *b_trigTopL;   //!
  TBranch        *b_trigTopEdep;   //!
  TBranch        *b_trigBotL;   //!
  TBranch        *b_trigBotEdep;   //!
  TBranch        *b_nPhot;   //!
  TBranch        *b_TrackID;   //!
  TBranch        *b_ParentID;   //!
  TBranch        *b_Energy;   //!
  TBranch        *b_Wavelength;   //!
  TBranch        *b_Time;   //!
  TBranch        *b_photPathLen;   //!
  TBranch        *b_SecID;   //!
  TBranch        *b_chID;   //!
  TBranch        *b_PosX;   //!
  TBranch        *b_PosY;   //!
  TBranch        *b_PosZ;   //!
  TBranch        *b_MomX;   //!
  TBranch        *b_MomY;   //!
  TBranch        *b_MomZ;   //!
  TBranch        *b_trkMomX;   //!
  TBranch        *b_trkMomY;   //!
  TBranch        *b_trkMomZ;   //!
  TBranch        *b_trkPosX;   //!
  TBranch        *b_trkPosY;   //!
  TBranch        *b_trkPosZ;   //!
  TBranch        *b_trkT;   //!
  TBranch        *b_trkLength;   //!
  
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
  
};

#endif
