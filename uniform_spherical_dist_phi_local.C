void getPhiMInMax(Double_t dist, Double_t phi1, Double_t &phi1_min, Double_t &phi1_max, Bool_t buildplot);

Int_t uniform_spherical_dist_phi_local(){
  //
  Double_t dist = 10.0;
  Double_t phi1 = 90.0*TMath::Pi()/180.0;
  Double_t phi1_min;
  Double_t phi1_max;
  Bool_t buildplot = true;
  
  getPhiMInMax(dist,phi1,phi1_min,phi1_max,buildplot);
  cout<<phi1_min<<endl
      <<phi1_max<<endl;
  //
  //getPhiMInMax(dist,phi1,phi1_min,phi1_max,buildplot);
  //cout<<phi1_min<<endl
  // <<phi1_max<<endl;
	    
  return 0;
}

//                         km             deg
void getPhiMInMax(Double_t dist, Double_t phi1, Double_t &phi1_min, Double_t &phi1_max, Bool_t buildplot){
  Double_t R = 2650.0;//km
  //
  Double_t theta;
  Double_t costheta;
  Double_t phi;
  TRandom3 *rnd = new TRandom3(21341);
  //
  Double_t delta_theta = TMath::ATan(0.396/(R*1000.0));
  //
  phi1_min =  1000;
  phi1_max = -1000;
  Double_t theta1 = TMath::ATan(dist*1000/(R*1000.0));
  Double_t theta1deg = theta1*180/TMath::Pi();
  TString h1_theta1_title = "dist = ";
  h1_theta1_title += dist;
  h1_theta1_title += " km";
  cout<<"theta1 = "<<theta1<<endl;
  cout<<"theta1deg = "<<theta1deg<<endl;
  //
  TH1D *h1_theta1 = new TH1D("h1_theta1",h1_theta1_title.Data(),100, (theta1-delta_theta*3.0)*180/TMath::Pi(), (theta1+delta_theta*3.0)*180/TMath::Pi());
  TH1D *h1_theta1local = new TH1D("h1_theta1local",h1_theta1_title.Data(),100, (theta1-delta_theta*3.0)*180/TMath::Pi(), (theta1+delta_theta*3.0)*180/TMath::Pi());
  //
  //  
  const Int_t n = 100000;
  //
  Double_t x1[n];
  Double_t y1[n];
  Double_t z1[n];
  //
  Double_t x1local[n];
  Double_t y1local[n];
  Double_t z1local[n];
  //
  Double_t x1_min = 2*R*1000;
  Double_t y1_min = 2*R*1000;
  Double_t z1_min = 2*R*1000;
  //
  Double_t x1_max = -2*R*1000;
  Double_t y1_max = -2*R*1000;
  Double_t z1_max = -2*R*1000;
  //
  Double_t phi1arr[n];
  //
  Double_t phi1localarr[n];
  //
  Double_t theta_min = 0.0;
  Double_t theta_max = delta_theta;
  //
  TVector3 r_local;
  r_local.SetXYZ(0.0,dist,R);
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
    TVector3 v1local;
    v1local = v1 - r_local;
    //
    x1local[i] = v1local.x();
    y1local[i] = v1local.y();
    z1local[i] = v1local.z();
    //
    h1_theta1->Fill(v1.Theta()*180/TMath::Pi());
    h1_theta1local->Fill(v1local.Theta()*180/TMath::Pi());
    //h1_phi1->Fill(v1.Phi()*180/TMath::Pi());
    //
    phi1arr[i] = v1.Phi()*180/TMath::Pi();
    phi1localarr[i] = v1local.Phi()*180/TMath::Pi();
    if(phi1_min>(v1.Phi()*180/TMath::Pi()))
      phi1_min = v1.Phi()*180/TMath::Pi();
    if(phi1_max<(v1.Phi()*180/TMath::Pi()))
      phi1_max = v1.Phi()*180/TMath::Pi();
    if(x1[i]<x1_min)
      x1_min = x1[i];
    if(y1[i]<y1_min)
      y1_min = y1[i];
    if(z1[i]<z1_min)
      z1_min = z1[i];
    if(x1[i]>x1_max)
      x1_max = x1[i];
    if(y1[i]>y1_max)
      y1_max = y1[i];
    if(z1[i]>z1_max)
      z1_max = z1[i];
    //
  }
  //
  z1_min += -0.1;
  z1_max += 0.1;
  TH1D *h1_phi1 = new TH1D("h1_phi1","h1_phi1",101, phi1_min - TMath::Abs((phi1_max - phi1_min)*0.1), phi1_max + TMath::Abs((phi1_max - phi1_min)*0.1));
  TH1D *h1_x1 = new TH1D("h1_x1","h1_x1",101, x1_min - TMath::Abs((x1_max - x1_min)*0.1), x1_max + TMath::Abs((x1_max - x1_min)*0.1));
  TH1D *h1_y1 = new TH1D("h1_x1","h1_y1",101, y1_min - TMath::Abs((y1_max - y1_min)*0.1), y1_max + TMath::Abs((y1_max - y1_min)*0.1));
  TH1D *h1_z1 = new TH1D("h1_x1","h1_z1",101, z1_min - TMath::Abs((z1_max - z1_min)*0.1), z1_max + TMath::Abs((z1_max - z1_min)*0.1));
  //
  TH1D *h1_phi1local = new TH1D("h1_phi1local","h1_phi1local",101, phi1_min - TMath::Abs((phi1_max - phi1_min)*0.1), phi1_max + TMath::Abs((phi1_max - phi1_min)*0.1));
//TH1D *h1_x1local = new TH1D("h1_x1","h1_x1",101, x1_min - TMath::Abs((x1_max - x1_min)*0.1), x1_max + TMath::Abs((x1_max - x1_min)*0.1));
//TH1D *h1_y1local = new TH1D("h1_x1","h1_y1",101, y1_min - TMath::Abs((y1_max - y1_min)*0.1), y1_max + TMath::Abs((y1_max - y1_min)*0.1));
//TH1D *h1_z1local = new TH1D("h1_x1","h1_z1",101, z1_min - TMath::Abs((z1_max - z1_min)*0.1), z1_max + TMath::Abs((z1_max - z1_min)*0.1));
  //
  for(Int_t i = 0;i<n;i++){
    h1_phi1->Fill(phi1arr[i]);
    h1_phi1local->Fill(phi1localarr[i]);
    h1_x1->Fill(x1[i]);
    h1_y1->Fill(y1[i]);
    h1_z1->Fill(z1[i]);
  }  

  //
  if(buildplot){
    TCanvas *c2 = new TCanvas("c2","c2",10,10,1200,800);
    c2->Divide(3,3);  
    c2->cd(1);
    h1_theta1->Draw();
    h1_theta1local->SetLineColor(kRed);
    h1_theta1local->Draw("same");
    c2->cd(2);
    h1_phi1->Draw();
    c2->cd(2);
    h1_phi1->Draw();
    c2->cd(4);
    h1_x1->Draw();
    c2->cd(5);
    h1_y1->Draw();
    c2->cd(6);
    h1_z1->Draw();

  }
  //
  //return 0;
}
