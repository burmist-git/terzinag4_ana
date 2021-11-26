Int_t small_mirror_spot(){
  const Int_t nn = 5;
  Double_t x[nn];
  Double_t s[nn];
  Double_t errx[nn];
  Double_t errs[nn];
  //
  x[0] = 0.0;
  s[0] = 2.325;
  errx[0] = 0.0;
  errs[0] = 0.005;
  //
  x[1] = 1.0;
  s[1] = 1.555;
  errx[1] = 0.0;
  errs[1] = 0.005;
  //
  x[2] = 2.0;
  s[2] = 0.825;
  errx[2] = 0.0;
  errs[2] = 0.005;
  //
  x[3] = 3.0;
  s[3] = 0.075;
  errx[3] = 0.0;
  errs[3] = 0.005;
  //
  x[4] = 4.0;
  s[4] = -0.675;
  errx[4] = 0.0;
  errs[4] = 0.005;

  TGraphErrors *gr = new TGraphErrors(5,x,s,errx,errs);
  
  gr->Draw("AP");
  
  return 0.0;
}
