Int_t uniform_spherical_dist(){
  //
  Double_t theta;
  Double_t costheta;
  Double_t phi;
  TRandom3 *rnd = new TRandom3(21341);
  //
  //Double_t delta_theta = TMath::ATan(0.396/(2650.0*1000.0));
  Double_t delta_theta = TMath::ATan(1500.0/(2650.0*1000.0));
  //  
  Double_t theta1 = 0.0*TMath::Pi()/180.0;
  Double_t phi1 = 0.0*TMath::Pi()/180.0;
  Double_t phi1_min =  1000;
  Double_t phi1_max = -1000;
  Double_t dist = 7.0;//km
  Double_t theta2 = TMath::ATan(dist*1000/(2650.0*1000.0)) + 0.0*TMath::Pi()/180.0;
  Double_t theta2deg = theta2*180/TMath::Pi();
  Double_t phi2_min =  1000;
  Double_t phi2_max = -1000;
  TString h1_theta2_title = "dist = ";
  h1_theta2_title += dist;
  h1_theta2_title += " km";
  cout<<"theta2 = "<<theta2<<endl;
  cout<<"theta2deg = "<<theta2deg<<endl;
  Double_t phi2 = 0.0*TMath::Pi()/180.0;
  //
  //Double_t theta1_local;
  //Double_t theta2_local;
  //
  //Double_t phi1_local;
  //Double_t phi2_local;
  //
  TH1D *h1_theta1 = new TH1D("h1_theta1","dist = 0.0 km",100, 0.0, (delta_theta*3.0)*180/TMath::Pi());
  TH1D *h1_theta2 = new TH1D("h1_theta2",h1_theta2_title.Data(),100, (theta2-delta_theta*3.0)*180/TMath::Pi(), (theta2+delta_theta*3.0)*180/TMath::Pi());
  //
  //TH1D *h1_phi1   = new TH1D("h1_phi1","h1_phi1",100, -TMath::Pi()*180/TMath::Pi(), TMath::Pi()*180/TMath::Pi());
  //TH1D *h1_phi2   = new TH1D("h1_phi2","h1_phi2",100, -delta_theta*1000*180/TMath::Pi(), delta_theta*1000*180/TMath::Pi());
  //
  Double_t R = 1.0;
  //  
  const Int_t n = 10000;
  //
  Double_t x1[n];
  Double_t y1[n];
  Double_t z1[n];
  //
  Double_t x2[n];
  Double_t y2[n];
  Double_t z2[n];
  //
  Double_t phi1arr[n];
  Double_t phi2arr[n];
  //
  Double_t theta_min = 0.0;
  Double_t theta_max = delta_theta;

  for(Int_t i = 0;i<n;i++){
    costheta = rnd->Uniform(TMath::Cos(theta_max),TMath::Cos(theta_min));
    theta = TMath::ACos(costheta);
    phi = (2.0*rnd->Uniform()-1.0)*TMath::Pi();
    TVector3 v1;
    v1.SetMagThetaPhi(R,theta,phi);
    TVector3 v2;
    v2.SetMagThetaPhi(R,theta,phi);
    //
    v1.RotateY(theta1);
    v1.RotateZ(phi1);
    //
    v2.RotateY(theta2);
    v2.RotateZ(phi2);
    //
    x1[i] = v1.x();
    y1[i] = v1.y();
    z1[i] = v1.z();
    //    
    x2[i] = v2.x();
    y2[i] = v2.y();
    z2[i] = v2.z();
    //
    h1_theta1->Fill(v1.Theta()*180/TMath::Pi());
    //h1_phi1->Fill(v1.Phi()*180/TMath::Pi());
    h1_theta2->Fill(v2.Theta()*180/TMath::Pi());
    //h1_phi2->Fill(v2.Phi()*180/TMath::Pi());
    //
    phi1arr[i] = v1.Phi()*180/TMath::Pi();
    phi2arr[i] = v2.Phi()*180/TMath::Pi();
    if(phi1_min>(v1.Phi()*180/TMath::Pi()))
      phi1_min = v1.Phi()*180/TMath::Pi();
    if(phi1_max<(v1.Phi()*180/TMath::Pi()))
      phi1_max = v1.Phi()*180/TMath::Pi();
    if(phi2_min>(v2.Phi()*180/TMath::Pi()))
      phi2_min = v2.Phi()*180/TMath::Pi();
    if(phi2_max<(v2.Phi()*180/TMath::Pi()))
      phi2_max = v2.Phi()*180/TMath::Pi();
  }
  //
  TH1D *h1_phi1 = new TH1D("h1_phi1","dist = 0.0 km",101, phi1_min - TMath::Abs((phi1_max - phi1_min)*0.1), phi1_max + TMath::Abs((phi1_max - phi1_min)*0.1));
  TH1D *h1_phi2 = new TH1D("h1_phi2",h1_theta2_title.Data(),101, phi2_min - TMath::Abs((phi2_max - phi2_min)*0.1), phi2_max + TMath::Abs((phi2_max - phi2_min)*0.1));
  //
  for(Int_t i = 0;i<n;i++){
    h1_phi1->Fill(phi1arr[i]);
    h1_phi2->Fill(phi2arr[i]);
  }  
  //
  h1_theta1->SetLineColor(kBlack);
  h1_phi1->SetLineColor(kBlack);
  h1_theta2->SetLineColor(kBlack);
  h1_phi2->SetLineColor(kBlack);
  //
  h1_theta1->SetLineWidth(3.0);
  h1_phi1->SetLineWidth(3.0);
  h1_theta2->SetLineWidth(3.0);
  h1_phi2->SetLineWidth(3.0);
  //
  TCanvas *c2 = new TCanvas("c2","c2",10,10,1200,800);
  c2->Divide(2,2);  
  c2->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_theta1->Draw();
  c2->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_phi1->Draw();
  c2->cd(3);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_theta2->Draw();
  c2->cd(4);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_phi2->Draw();
  //
  h1_theta1->GetXaxis()->SetTitle("Theta, deg");
  h1_phi1->GetXaxis()->SetTitle("Phi, deg");
  h1_theta2->GetXaxis()->SetTitle("Theta, deg");
  h1_phi2->GetXaxis()->SetTitle("Phi, deg");
  //
  return 0;
}
