#ifndef terzina_hh
#define terzina_hh

//My
#include "terzinabase.hh"

//root
#include <TROOT.h>

class TChain;
class TFile;
class TTree;
class TString;
class TBranch;


class terzina: public terzinabase {
public:
  terzina(TString fileList) : terzinabase(fileList)
  {
  }

  terzina(TString file, Int_t key) : terzinabase(file, key)
  {
  }

  void Loop(TString histOut);

};

#endif
