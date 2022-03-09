#pragma once

//root
#include <TObject.h>
#include <TH2Poly.h>
#include <TGraph.h>
#include <TVector2.h>
#include <TCanvas.h>

//c, c++
#include <string>
#include <vector>
#include <map>

class CameraPlaneHist: public TH2Poly {
 public:
  
  CameraPlaneHist(const char* name, const char* title);
  ~CameraPlaneHist();
  void test();
  //void DrawHisto( TString opt, TString pdfOutFileName, TString frameTitle, TString lineDrawOpt, Double_t ztMin, Double_t ztMax);
  //void DrawHistoC1( TString opt, TString pdfOutFileName, TString frameTitle, TString lineDrawOpt, Double_t ztMin, Double_t ztMax, TCanvas *c1);  
  void Clean();
  void count_signal(Double_t th_val, Int_t &nch, Int_t &npe);
  
 private:

  Double_t _d_frame;
  Double_t _lx_camera;
  Double_t _ly_camera;
  
  /*
  void setUpARICHMergerHist();
  
  void SetInitialParametersByDefault();

  void SetUpVerticesMap();

  void dumpVerticesMap();

  void makeRotation( Double_t xold, Double_t yold, Double_t &xnew, Double_t &ynew, Double_t r, Double_t phi);

  std::vector<mergerStruct> read_merger_positions( TString fnameInfo, float &size_l, float &size_w, int &nMerger);
  
  //Vector of tructures which contains merger positions.
  std::vector<mergerStruct> m_merStrV;
  //Vector mergerSlotNumber m_mergerSlotNumber[binID] = mergerSlotNumber.
  std::vector<int> m_mergerSlotNumber;
  //Length of the merger board
  float m_Board_size_l;
  //Width of the merger board
  float m_Board_size_w;
  //Verbose level
  Int_t m_verboseLevel;
  //Meger vertices map
  std::vector<TVector2> m_verticesMap;
  //Meger vertices map
  std::vector<TGraph> m_verticesGraphV;
  */
};
