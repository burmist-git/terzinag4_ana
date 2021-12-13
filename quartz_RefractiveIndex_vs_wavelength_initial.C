//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TGaxis.h>
#include <TLine.h>
#include <TMath.h>
#include <TF1.h>
#include <TLegend.h>
#include <TMultiGraph.h>

//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>

using namespace std;

// Please _note_ the lambda is in nm
Double_t getSellmeierQuartz(Double_t lam){
  lam = lam;
  Double_t B1 = 0.696166300;
  Double_t B2 = 0.407942600;
  Double_t B3 = 0.897479400;
  
  Double_t C1 = 4.67914826*1.0e-3; //um^2
  Double_t C2 = 1.35120631*1.0e-2; //um^2
  Double_t C3 = 97.9340025;        //um^2
  
  return TMath::Sqrt(1 + B1*lam*lam/(lam*lam-C1) + B2*lam*lam/(lam*lam-C2) + B3*lam*lam/(lam*lam-C3));
}

//
// If returnStrID == RI      --> return TGraph of QuartzRefractiveIndex vs wavelength
// If returnStrID == RIsell  --> return TGraph of QuartzRefractiveIndexSellm vs wavelength
// If returnStrID == RIgroup --> return TGraph of QuartzRefractiveIndexGroup vs wavelength
//
TGraph *quartz_RefractiveIndex_vs_wavelength_initial(TString returnStrID = "RI"){
  
  const int num = 36;
  const int numL = 100;
  double WaveLength[num];
  double WaveLengthL[numL];
  double lamL_min = 247.968386;
  //double lamL_max = 826.56;
  double lamL_max = 1033.2016083333335;
  double lamL;
  //double Absorption[num];
  //double AirAbsorption[num];
  //double AirRefractiveIndex[num];
  //double PhotonEnergy[num];
    
  /*
  // Absorption of quartz per 1m
  double QuartzAbsorption[num] =
  {0.999572036,0.999544661,0.999515062,0.999483019,0.999448285,
  0.999410586,0.999369611,0.999325013,0.999276402,0.999223336,
  0.999165317,0.999101778,0.999032079,0.998955488,0.998871172,
  0.998778177,0.99867541 ,0.998561611,0.998435332,0.998294892,
  0.998138345,0.997963425,0.997767484,0.997547418,0.99729958 ,
  0.99701966 ,0.99670255 ,0.996342167,0.995931242,0.995461041,
  0.994921022,0.994298396,0.993577567,0.992739402,0.991760297,
  0.990610945};
  */
  
  //double nanometer = 1.0E-9;
  int i;
  for (i=0; i<num; i++) {
    //PhotonEnergy[num - (i+1)] = 2*TMath::Pi()/((300 + i*10)/0.197*1.0e6);
    WaveLength[num - (i+1)] = (300 + i*10);//nm
    /* Absorption is given per length and G4 needs mean free path
       length, calculate it here
       mean free path length - taken as probablility equal 1/e
       that the photon will be absorbed */
    //QuartzAbsorption[i] = (-1)/log(QuartzAbsorption[i])/1000.0;
    //EpotekAbsorption[i] = (-1)/log(EpotekAbsorption[i])*
    //epotekBarJoint.thickness;
  }
  
  double QuartzRefractiveIndex[num] =
    {1.456535,1.456812,1.4571  ,1.457399,1.457712,1.458038,
     1.458378,1.458735,1.459108,1.4595  ,1.459911,1.460344,
     1.460799,1.46128 ,1.461789,1.462326,1.462897,1.463502,
     1.464146,1.464833,1.465566,1.46635 ,1.46719 ,1.468094,
     1.469066,1.470116,1.471252,1.472485,1.473826,1.475289,
     1.476891,1.478651,1.480592,1.482739,1.485127,1.487793};
  
  double QuartzRefractiveIndexGroup[num];
  double QuartzRefractiveIndexSellm[num];
  double QuartzRefractiveIndexSellmL[numL];
  
  for(i = 1;i<num;i++){
    QuartzRefractiveIndexGroup[i] = QuartzRefractiveIndex[i]-WaveLength[i]*(QuartzRefractiveIndex[i] - QuartzRefractiveIndex[i-1])/(WaveLength[i] - WaveLength[i-1]);
    //cout<<"WaveLength[i] = "<<WaveLength[i]<<"    QuartzRefractiveIndexGroup[i] "<<QuartzRefractiveIndexGroup[i]<<endl;
  }
  QuartzRefractiveIndexGroup[0] = QuartzRefractiveIndexGroup[1] - 0.0006;
  
  
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  
  
  TCanvas *c1 = new TCanvas("c1","canva", 10, 10, 800, 800);
  c1->SetFillColor(kWhite);
  
  for(i = 0;i<num;i++){
    cout<<"++++++++++++++++++++++++++"<<endl;
    cout<<"WaveLength[i] = "<<WaveLength[i]<<"  QuartzRefractiveIndex[i]      = "<<QuartzRefractiveIndex[i]<<endl;
    cout<<"WaveLength[i] = "<<WaveLength[i]<<"  QuartzRefractiveIndex[i]      = "<<getSellmeierQuartz(WaveLength[i])<<endl;
    cout<<"WaveLength[i] = "<<WaveLength[i]<<"  QuartzRefractiveIndexGroup[i] = "<<QuartzRefractiveIndexGroup[i]<<endl;
    cout<<"--------------------------"<<endl;
    QuartzRefractiveIndexSellm[i] = getSellmeierQuartz(WaveLength[i]/1000.0);
  }
  
  for(i = 0;i<numL;i++){
    lamL = lamL_min + (lamL_max - lamL_min)*i/(numL - 1);
    WaveLengthL[i] = lamL;
    QuartzRefractiveIndexSellmL[i] = getSellmeierQuartz(lamL/1000.0);
  }
  
  //TGraph *gr1_pr1 = new TGraph( num, PhotonEnergy, QuartzRefractiveIndex );
  TGraph *gr1_pr1   = new TGraph( num, WaveLength, QuartzRefractiveIndex );
  TGraph *gr1_Sellm = new TGraph( num, WaveLength, QuartzRefractiveIndexSellm );
  TGraph *gr1_SellmL = new TGraph( numL, WaveLengthL, QuartzRefractiveIndexSellmL );
  TGraph *gr1_grout = new TGraph( num, WaveLength, QuartzRefractiveIndexGroup );
  gr1_pr1->SetName("");
  gr1_pr1->SetTitle("");
  gr1_pr1->SetLineWidth(2.0);
  gr1_pr1->SetLineColor(kRed);
  gr1_pr1->SetMarkerStyle(20);
  gr1_pr1->SetMarkerColor(kRed);
  gr1_pr1->SetMarkerSize(1.2);
  //gr1_pr1->Draw("APL");
  gr1_grout->SetName("");
  gr1_grout->SetTitle("");
  gr1_grout->SetLineWidth(3.0);
  gr1_grout->SetLineColor(kRed);
  gr1_grout->SetMarkerColor(kRed);
  gr1_Sellm->SetName("");
  gr1_Sellm->SetTitle("");
  gr1_Sellm->SetLineWidth(3.0);
  gr1_Sellm->SetLineColor(kBlue);
  //gr1_Sellm->SetMarkerStyle(20);
  gr1_SellmL->SetName("");
  gr1_SellmL->SetTitle("");
  gr1_SellmL->SetLineWidth(3.0);
  gr1_SellmL->SetLineColor(kBlack);
  //gr1_SellmL->SetMarkerStyle(20);
  
  TMultiGraph *mg = new TMultiGraph("mg","");
  mg->Add(gr1_pr1);
  //mg->Add(gr1_grout);
  mg->Add(gr1_SellmL);
  mg->Draw("APL");
  mg->GetXaxis()->SetTitle("#lambda, nm");
  mg->GetYaxis()->SetTitle("Refractive Index");
  
  /*
    TF1 *f1 = new TF1("f1","1239.84/x",1.9,4);
    f1->GetName();
    TGaxis *axis = new TGaxis( 309.4, 1.45, 651.5, 1.45, "f1", 510, "L+", 1);
    //axis->SetLabelColor(kRed);
    axis->SetTitle("h#nu, eV");
    axis->Draw();
  */

  TF1 *f1 = new TF1("f1","1239.84/x", 1.2, 5.0);
  cout<<"f1->Eval(400.0) = "<<f1->Eval(400.0)<<endl;
  f1->GetName();
  TGaxis *axis = new TGaxis( lamL_min, 1.445, lamL_max, 1.445, "f1", 510, "L+", 1);
  axis->SetLabelSize(0.03);
  //axis->SetLabelColor(kRed);
  axis->SetTitle("h#nu, eV");
  axis->Draw();
  
  TLegend *leg = new TLegend(0.7,0.2,0.9,0.4,"","brNDC");
  //leg->AddEntry(gr1_grout, "group R.I.","l");
  leg->AddEntry(gr1_pr1,   "phase R.I.","p");
  leg->AddEntry(gr1_SellmL, "phase R.I. Sellmeier Eq.","l");
  leg->Draw();
  
  //cout<<"convert_TGraph_Lambda_vs_pe"<<endl;
  //print_TGraph_info(convert_TGraph_Lambda_vs_pe(gr1_pr1), "g4");
  
  if(returnStrID == "RI"){
    return gr1_pr1;
  }
  else if(returnStrID == "RIsell"){
    return gr1_Sellm;
  }
  else if(returnStrID == "RIgroup"){
    return gr1_grout;
  }
  
  return 0;
}
