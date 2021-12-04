#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Int_t terzina_data_rate_estimate(){
  //
  TString dataFileIn = "POEMMA_Event_Rate.dat";
  Double_t terzina_R = 0.3;//m
  Double_t POEMMA_aperture = 2.5;//m^2
  Double_t terzina_aperture = TMath::Pi()*terzina_R*terzina_R; //m^2
  //
  ifstream fileIn(dataFileIn.Data());
  const Int_t nn = 11;
  Double_t x[nn];
  Double_t y[nn];
  Double_t xerr[nn];
  Double_t yerr[nn];
  Double_t xval;
  Double_t yval;
  if (fileIn.is_open()){
    for(int i = 0 ;i<nn;i++){
      fileIn >> xval>>yval;
      x[i] = xval;
      y[i] = yval;
      xerr[i] = 0.01;
      yerr[i] = 0.2;
    }
    fileIn.close();
  }
  else cout<<"Unable to open file"<<endl;
  TGraphErrors *gr = new TGraphErrors(nn,x,y,xerr,yerr);
  gr->Draw("APL");  
  gr->Fit("expo");
  TF1 *f_fit = (TF1*)gr->GetListOfFunctions()->FindObject("expo");
  //
  //POEMMA_aperture = 2.5;//m^2
  //cout<<"terzina_aperture                 "<<terzina_aperture<<endl
  //<<"terzina_aperture/POEMMA_aperture "<<terzina_aperture/POEMMA_aperture<<endl;
  //cout<<f_fit->Eval(17)<<endl;
  //
  //
  //cout<<f_fit->Eval(16)<<endl;
  //
  Int_t numberOf_SiPM_ch = 1024;
  Int_t n_ADC_bit = 10;
  Double_t event_rate_per_hour = 100;
  Double_t number_of_acquisitions_per_trigger = 100;
  Double_t nite_time_per_day = 12.0;
  Double_t data_per_day;
  data_per_day = numberOf_SiPM_ch*TMath::Power(2.0,n_ADC_bit)*event_rate_per_hour*number_of_acquisitions_per_trigger*nite_time_per_day/8.0/1024.0/1024.0/1024.0;

  cout<<"numberOf_SiPM_ch                   "<<numberOf_SiPM_ch<<endl
      <<"n_ADC_bit                          "<<n_ADC_bit<<endl
      <<"event_rate_per_hour                "<<event_rate_per_hour<<endl
      <<"number_of_acquisitions_per_trigger "<<number_of_acquisitions_per_trigger<<endl
      <<"nite_time_per_day                  "<<nite_time_per_day<<endl;
  cout<<"data_per_day                       "<<data_per_day<<" Gbyte per day"<<endl;

  return 0;
}
