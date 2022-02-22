Int_t uniform_spherical_dist_old(){
  //
  Double_t theta;
  Double_t costheta;
  Double_t phi;
  //
  TH1D *h1_theta = new TH1D("h1_theta","h1_theta",400,-10.0*TMath::Pi()/180.0,190.0*TMath::Pi()/180.0);
  TH1D *h1_phi   = new TH1D("h1_phi","h1_phi",400,-190.0*TMath::Pi()/180.0,190.0*TMath::Pi()/180.0);
  //
  TH1D *h1_theta_c = new TH1D("h1_theta_c","h1_theta_c",1200,-10.0*TMath::Pi()/180.0,190.0*TMath::Pi()/180.0);
  TH1D *h1_phi_c   = new TH1D("h1_phi_c","h1_phi_c",12000,-190.0*TMath::Pi()/180.0,190.0*TMath::Pi()/180.0);
  TH1D *h1_theta_c2 = new TH1D("h1_theta_c2","h1_theta_c2",1200,-10.0*TMath::Pi()/180.0,190.0*TMath::Pi()/180.0);
  TH1D *h1_phi_c2   = new TH1D("h1_phi_c2","h1_phi_c2",12000,-190.0*TMath::Pi()/180.0,190.0*TMath::Pi()/180.0);
  TH1D *h1_theta_c3 = new TH1D("h1_theta_c3","h1_theta_c3",800,-10.0*TMath::Pi()/180.0,190.0*TMath::Pi()/180.0);
  TH1D *h1_phi_c3   = new TH1D("h1_phi_c3","h1_phi_c3",12000,-190.0*TMath::Pi()/180.0,190.0*TMath::Pi()/180.0);
  //
  TRandom3 *rnd = new TRandom3(21341);
  //  
  const Int_t n = 10000;
  const Int_t ne = 10000;
  //
  Double_t xe[n];
  Double_t ye[n];
  Double_t ze[n];
  //
  Double_t x[n];
  Double_t y[n];
  Double_t z[n];
  //
  Double_t x2[n];
  Double_t y2[n];
  Double_t z2[n];
  //
  Double_t x3[n];
  Double_t y3[n];
  Double_t z3[n];
  //
  Double_t x4[n];
  Double_t y4[n];
  Double_t z4[n];
  //
  Double_t R = 1.0;
  //
  Double_t theta_c = 0.0*TMath::Pi()/180.0;
  Double_t phi_c = 0.0*TMath::Pi()/180.0;
  //Double_t theta_c2 = TMath::ATan(0.3/2650.0);
  Double_t theta_c2 = 20.0*TMath::Pi()/180.0;
  Double_t phi_c2 = 10.0*TMath::Pi()/180.0;
  //Double_t theta_c3 = TMath::ATan(40.0/2650.0);
  Double_t theta_c3 = 10.0*TMath::Pi()/180.0;
  Double_t phi_c3 = 30.0;
  //Double_t delta_theta = TMath::ATan(0.00396/2650.0);
  Double_t delta_theta = 3.0*TMath::Pi()/180.0;
  //Double_t delta_phi = 5.0*TMath::Pi()/180.0;
  //
  Double_t theta_min = 0.0*TMath::Pi()/180.0;
  Double_t theta_max = delta_theta + theta_min;
  //
  //Double_t phi_c = 10.0*TMath::Pi()/180.0;
  //Double_t delta_theta = 5.0*TMath::Pi()/180.0;
  //Double_t delta_phi = 5.0*TMath::Pi()/180.0;
  
  for(Int_t i = 0;i<n;i++){
    costheta = 2.0*rnd->Uniform()-1.0;
    theta = TMath::ACos(costheta);
    //theta = (1.0*rnd->Uniform()-0.0)*TMath::Pi();
    phi = (2.0*rnd->Uniform()-1.0)*TMath::Pi();

    h1_theta->Fill(theta);
    h1_phi->Fill(phi);
    
    x[i] = R*TMath::Sin(theta)*TMath::Cos(phi);
    y[i] = R*TMath::Sin(theta)*TMath::Sin(phi);
    z[i] = R*TMath::Cos(theta);
    
  }

  TVector3 v0;
  v0.SetMagThetaPhi(R,0.0,0.0);

  TVector3 vc;
  vc.SetMagThetaPhi(R,theta_c,phi_c);
  TVector3 vc2;
  vc2.SetMagThetaPhi(R,theta_c2,phi_c2);
  TVector3 vc3;
  vc3.SetMagThetaPhi(R,theta_c3,phi_c3);
  
  for(Int_t i = 0;i<n;i++){
    costheta = rnd->Uniform(TMath::Cos(theta_max),TMath::Cos(theta_min));
    theta = TMath::ACos(costheta);
    //theta = (1.0*rnd->Uniform()-0.0)*TMath::Pi();
    phi = (2.0*rnd->Uniform()-1.0)*TMath::Pi();
    //phi = (2.0*rnd->Uniform()-1.0)*1.0*TMath::Pi()/180.0+10.0*TMath::Pi()/180.0;
    TVector3 v1;
    v1.SetMagThetaPhi(R,theta,phi);
    TVector3 v2;
    v2.SetMagThetaPhi(R,theta,phi);
    TVector3 v3;
    v3.SetMagThetaPhi(R,theta,phi);
    //
    v1.RotateY(theta_c);
    v1.RotateZ(phi_c);
    //
    v2.RotateY(theta_c2);
    v2.RotateZ(phi_c2);
    //
    v3.RotateY(theta_c3);
    v3.RotateZ(phi_c3);
    //
    x2[i] = v1.x();
    y2[i] = v1.y();
    z2[i] = v1.z();
    //    
    x3[i] = v2.x();
    y3[i] = v2.y();
    z3[i] = v2.z();
    //    
    x4[i] = v3.x();
    y4[i] = v3.y();
    z4[i] = v3.z();

    h1_theta_c->Fill(v1.Theta());
    h1_phi_c->Fill(v1.Phi());
    h1_theta_c2->Fill(v2.Theta());
    h1_phi_c2->Fill(v2.Phi());
    h1_theta_c3->Fill(v3.Theta());
    h1_phi_c3->Fill(v3.Phi());

    //
    /*
    x2[i] = R*TMath::Sin(theta)*TMath::Cos(phi) + vd.x();
    y2[i] = R*TMath::Sin(theta)*TMath::Sin(phi) + vd.y();
    z2[i] = R*TMath::Cos(theta)+ vd.z();
    //    
    x3[i] = R*TMath::Sin(theta)*TMath::Cos(phi) + vd2.x();
    y3[i] = R*TMath::Sin(theta)*TMath::Sin(phi) + vd2.y();
    z3[i] = R*TMath::Cos(theta)+ vd2.z();
    //    
    x4[i] = R*TMath::Sin(theta)*TMath::Cos(phi) + vd3.x();
    y4[i] = R*TMath::Sin(theta)*TMath::Sin(phi) + vd3.y();
    z4[i] = R*TMath::Cos(theta)+ vd3.z();
    */
  }

  TCanvas *c1 = new TCanvas("c1","c1",10,10,800,800);
  TGraph2D *gr = new TGraph2D(n,x,y,z);
  gr->SetMarkerColor(kBlack);
  gr->SetMarkerStyle(7);
  TGraph2D *gr2 = new TGraph2D(n,x2,y2,z2);
  gr2->SetMarkerColor(kRed);
  gr2->SetMarkerStyle(7);
  TGraph2D *gr3 = new TGraph2D(n,x3,y3,z3);
  gr3->SetMarkerColor(kBlue);
  gr3->SetMarkerStyle(7);
  TGraph2D *gr4 = new TGraph2D(n,x4,y4,z4);
  gr4->SetMarkerColor(kMagenta);
  gr4->SetMarkerStyle(7);

  gr->SetTitle("");
  gr->Draw("P");
  gr2->Draw("sameP");
  gr3->Draw("sameP");
  gr4->Draw("sameP");

  gr->GetXaxis()->SetTitle("x");
  gr->GetYaxis()->SetTitle("y");
  gr->GetZaxis()->SetTitle("z");

  TCanvas *c2 = new TCanvas("c2","c2",10,10,1600,800);
  c2->Divide(2,1);  
  c2->cd(1);
  h1_theta->Draw();
  c2->cd(2);
  h1_phi->Draw();

  TCanvas *c3 = new TCanvas("c3","c3",10,10,900,900);
  c3->Divide(2,3);  
  c3->cd(1);
  h1_theta_c->Draw();
  c3->cd(2);
  h1_phi_c->Draw();
  c3->cd(3);
  h1_theta_c2->Draw();
  c3->cd(4);
  h1_phi_c2->Draw();
  c3->cd(5);
  h1_theta_c3->Draw();
  c3->cd(6);
  h1_phi_c3->Draw();

  return 0;
}
