#undef NDEBUG

//my
#include "src/terzina.hh"

//root
#include "TROOT.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TGraph.h"

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]){
  if(argc == 4 && atoi(argv[1])==0){
    TString rootFilesList = argv[2];
    TString outRootFileF = argv[3];
    cout<<"--> Parameter calculation from the WF <--"<<endl
	<<"rootFilesList : "<<rootFilesList<<endl
	<<"outRootFileF  : "<<outRootFileF<<endl;
    terzina a(rootFilesList);
    a.Loop(outRootFileF);
  }
  else if(argc == 4 && atoi(argv[1])==1){
    TString inRootFiles = argv[2];
    TString outRootFileF = argv[3];
    cout<<"--> Parameter calculation from the WF <--"<<endl
	<<"inRootFiles : "<<inRootFiles<<endl
	<<"outRootFileF  : "<<outRootFileF<<endl;
    terzina a( inRootFiles, atoi(argv[1]));
    a.Loop(outRootFileF);
    //a.bkgSim(outRootFileF);
  }
  else if(argc == 8 && atoi(argv[1])==2){
    TString inRootFileWithShower = argv[2];
    TString inDatFileShower = argv[3];
    TString inRootFileWithG4sim = argv[4];
    Double_t particleMomentum = atof(argv[5]);
    TString outRootFileF = argv[6];
    TString wfSim_Terzina_conf = argv[7];
    cout<<"--> Parameter calculation from the WF <--"<<endl
	<<"inRootFileWithShower  "<<inRootFileWithShower<<endl
      	<<"inDatFileShower       "<<inDatFileShower<<endl
	<<"inRootFileWithG4sim   "<<inRootFileWithG4sim<<endl
	<<"particleMomentum      "<<particleMomentum<<endl
	<<"outRootFileF          "<<outRootFileF<<endl
	<<"wfSim_Terzina_conf    "<<wfSim_Terzina_conf<<endl;
    terzina a( inRootFileWithG4sim, atoi(argv[1]));
    a.showerSim(inRootFileWithShower, inDatFileShower, particleMomentum, outRootFileF, wfSim_Terzina_conf);
  }
  else if(argc == 4 && atoi(argv[1])==3){
    TString rootFilesList = argv[2];
    TString outRootFileF = argv[3];
    cout<<"--> Parameter calculation from the WF <--"<<endl
	<<"rootFilesList : "<<rootFilesList<<endl
	<<"outRootFileF  : "<<outRootFileF<<endl;
    terzina a(rootFilesList);
    a.bkgSim(outRootFileF);
  }
  else if(argc == 2 && atoi(argv[1])==4){
    cout<<"--> test <--"<<endl;
    terzina a = terzina();
    a.testlocal();
  }
  else{
    //------------------------------------------------
    cout<<" --> ERROR in input arguments "<<endl
	<<" runID [1] = 0 (execution ID number)"<<endl
      	<<"       [2] - file with list of the root files"<<endl
	<<"       [3] - name of root file with histograms"<<endl;
    //------------------------------------------------
    cout<<" runID [1] = 1 (execution ID number)"<<endl
      	<<"       [2] - in root files"<<endl
	<<"       [3] - name of root file with histograms"<<endl;
    //------------------------------------------------
    cout<<" runID [1] = 2 (execution ID number)"<<endl
      	<<"       [2] - in root file with shower simulation"<<endl
	<<"       [3] - in dat file with trk parameters"<<endl
      	<<"       [4] - in root file with Geant4 terzina simulation"<<endl
      	<<"       [5] - proton track Ekin (PeV)"<<endl
	<<"       [6] - name of root file with histograms"<<endl;
    //------------------------------------------------
    cout<<" runID [1] = 3 (background analysis)"<<endl
      	<<"       [2] - file with list of the root files"<<endl
	<<"       [3] - name of root file with histograms"<<endl;
    cout<<" runID [1] = 4 (simple test)"<<endl;
  }
  return 0;
}
