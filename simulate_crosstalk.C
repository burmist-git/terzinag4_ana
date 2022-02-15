Bool_t crosstalk(Double_t prob, TRandom3 *rnd);

Int_t simulate_crosstalk(){
  TRandom3 *rnd = new TRandom3();
  Double_t ampl = 0;
  TH1D *h1 = new TH1D("h1","h1",100,-0.5,100.5);  
    for(Int_t i = 0;i<10000;i++){
      ampl = 0;
      do
	ampl = ampl + rnd->Gaus(10,1.5);
      while(crosstalk(0.1,rnd));
      h1->Fill(ampl);
    }
    h1->Draw(); 
   return 0;
}

Bool_t crosstalk(Double_t prob, TRandom3 *rnd){
  if(rnd->Uniform()<=prob)
      return true;
  return false;
}

/*
  for(Int_t j = 0;j<30;j++){
  TH1D *h1 = new TH1D("h1","h1",100,-0.5,100.5);  
  for(Int_t i = 0;i<1;i++){
  do {
  h1->Fill(rnd->Gaus(10,1));
  }
  while(crosstalk(0.2,rnd));
  }
  cout<<h1->GetEntries()<<endl;
  delete h1;
  }
*/  
