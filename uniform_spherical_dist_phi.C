void getPhiMInMax(Double_t dist, Double_t phi1, Double_t &phi1_min, Double_t &phi1_max, Bool_t buildplot);

Int_t uniform_spherical_dist_phi(){
  Double_t dist = 40.0;
  Double_t dist_min = 0.0;
  Double_t dist_max = 10.0;
  Double_t phi1 = 0.0;
  Double_t phi1_min;
  Double_t phi1_max;
  Bool_t buildplot = false;
  //
  const Int_t n = 1000; 

  TGraph *gr_dphi = new TGraph(); 
  gr_dphi->SetTitle("");
  gr_dphi->SetName("gr_dphi");
  
  for(Int_t i = 0;i<n;i++){
    dist = dist_min + (dist_max-dist_min)/(n-1)*i;
    getPhiMInMax(dist,phi1,phi1_min,phi1_max,buildplot);
    gr_dphi->SetPoint(i,dist,(phi1_max - phi1_min));
  }
  
  //
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,800);
  c1->SetRightMargin(0.01);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.01);
  c1->SetBottomMargin(0.1);

  gr_dphi->SetMarkerStyle(7);
  
  gr_dphi->Draw("APL");

  gr_dphi->GetXaxis()->SetTitle("Distance, km");
  gr_dphi->GetYaxis()->SetTitle("Phi_max - Phi_min, deg");

  
  //getPhiMInMax(dist,phi1,phi1_min,phi1_max,buildplot);
  //cout<<phi1_min<<endl
  //    <<phi1_max<<endl;
  //
  //getPhiMInMax(dist,phi1,phi1_min,phi1_max,buildplot);
  //cout<<phi1_min<<endl
  // <<phi1_max<<endl;
	    
  return 0;
}

//                         km             deg
void getPhiMInMax(Double_t dist, Double_t phi1, Double_t &phi1_min, Double_t &phi1_max, Bool_t buildplot){
  //
  Double_t theta;
  Double_t costheta;
  Double_t phi;
  TRandom3 *rnd = new TRandom3(21341);
  //
  Double_t delta_theta = TMath::ATan(0.396/(2650.0*1000.0));
  //  
  phi1_min =  1000;
  phi1_max = -1000;
  Double_t theta1 = TMath::ATan(dist*1000/(2650.0*1000.0));
  Double_t theta1deg = theta1*180/TMath::Pi();
  TString h1_theta1_title = "dist = ";
  h1_theta1_title += dist;
  h1_theta1_title += " km";
  cout<<"theta1 = "<<theta1<<endl;
  cout<<"theta1deg = "<<theta1deg<<endl;
  //
  TH1D *h1_theta1 = new TH1D("h1_theta1",h1_theta1_title.Data(),100, (theta1-delta_theta*3.0)*180/TMath::Pi(), (theta1+delta_theta*3.0)*180/TMath::Pi());
  //
  Double_t R = 1.0;
  //  
  const Int_t n = 10000;
  //
  Double_t x1[n];
  Double_t y1[n];
  Double_t z1[n];
  //
  Double_t phi1arr[n];
  //
  Double_t theta_min = 0.0;
  Double_t theta_max = delta_theta;
  //
  for(Int_t i = 0;i<n;i++){
    costheta = rnd->Uniform(TMath::Cos(theta_max),TMath::Cos(theta_min));
    theta = TMath::ACos(costheta);
    phi = (2.0*rnd->Uniform()-1.0)*TMath::Pi();
    TVector3 v1;
    v1.SetMagThetaPhi(R,theta,phi);
    //
    v1.RotateY(theta1);
    v1.RotateZ(phi1);
    //
    x1[i] = v1.x();
    y1[i] = v1.y();
    z1[i] = v1.z();
    //
    h1_theta1->Fill(v1.Theta()*180/TMath::Pi());
    //h1_phi1->Fill(v1.Phi()*180/TMath::Pi());
    //
    phi1arr[i] = v1.Phi()*180/TMath::Pi();
    if(phi1_min>(v1.Phi()*180/TMath::Pi()))
      phi1_min = v1.Phi()*180/TMath::Pi();
    if(phi1_max<(v1.Phi()*180/TMath::Pi()))
      phi1_max = v1.Phi()*180/TMath::Pi();
  }
  //
  TH1D *h1_phi1 = new TH1D("h1_phi1","h1_phi1",101, phi1_min - TMath::Abs((phi1_max - phi1_min)*0.1), phi1_max + TMath::Abs((phi1_max - phi1_min)*0.1));
  //
  for(Int_t i = 0;i<n;i++){
    h1_phi1->Fill(phi1arr[i]);
  }  
  //
  if(buildplot){
    TCanvas *c2 = new TCanvas("c2","c2",10,10,1200,800);
    c2->Divide(2,1);  
    c2->cd(1);
    h1_theta1->Draw();
    c2->cd(2);
    h1_phi1->Draw();
  }
  //
  //return 0;
}
