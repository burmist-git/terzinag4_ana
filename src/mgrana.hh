#ifndef mgrana_hh
#define mgrana_hh

//My
#include "mgranabase.hh"

//root
#include <TROOT.h>

class TChain;
class TFile;
class TTree;
class TString;
class TBranch;


class mgrana: public mgranabase {
public:
  mgrana(TString fileList) : mgranabase(fileList)
  {
  }

  mgrana(TString file, Int_t key) : mgranabase(file, key)
  {
  }

  void Loop(TString histOut);

};

#endif
