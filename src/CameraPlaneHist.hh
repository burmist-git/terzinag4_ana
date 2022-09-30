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
  void Clean();
  void count_signal(Double_t th_val, Int_t &nch, Int_t &npe);
  
 private:

  Double_t _d_frame;
  Double_t _lx_camera;
  Double_t _ly_camera;
  
};
