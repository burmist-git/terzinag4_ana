Int_t weight_estimate(){
  //
  Double_t D  = 394.0;    //m
  Double_t L  = 350.0;    //mm
  Double_t dl = 4.0;      //mm
  //
  Double_t Dcor = 362.0;  //mm
  Double_t dlcor = 13;    //mm
  //
  Double_t Dmin_oring = Dcor;
  Double_t Dmax_oring = D;
  //
  Double_t Dbig_mirror = 394.0;   //mm
  Double_t Dsmall_mirror = 144.0; //mm
  //
  Double_t rho_al   = 2.7;   //g/cm^3
  Double_t rho_sio2 = 2.2;   //g/cm^3
  //http://www.mt-berlin.com/frames_cryst/descriptions/quartz%20.htm
  Double_t rho_cristallsio2 = 2.65;   //g/cm^3
  //
  Double_t m_structMat = 2.0;//kg
  //
  Double_t S  = TMath::Pi()*D*D/4.0;
  Double_t ll = TMath::Pi()*D;
  //
  Double_t Scorr  = TMath::Pi()*Dcor*Dcor/4.0;
  //
  Double_t V_backWall = S*dl;
  Double_t V_wall = ll*L*dl;
  //
  Double_t V_corr = Scorr*dlcor;
  //
  Double_t V_oring = V_backWall - Scorr*dl;
  //
  Double_t m_backWall = V_backWall*rho_al;
  Double_t m_wall = V_wall*rho_al;
  Double_t m_oring = V_oring*rho_al;
  //
  Double_t m_corr = V_corr*rho_cristallsio2;
  Double_t S_bigmirror = TMath::Pi()*Dbig_mirror*Dbig_mirror/4.0;
  Double_t S_smallmirror = TMath::Pi()*Dsmall_mirror*Dsmall_mirror/4.0;
  //
  Double_t m_bigmirror = m_corr;
  Double_t m_smallmirror = m_bigmirror/(S_bigmirror/S_smallmirror);
  //
  Double_t m_asic = 0.093;       //kg per ASIC++
  Int_t n_asic    = 32;
  Double_t m_sipm = 0.05/1000.0; //kg per SiPM
  Int_t n_sipm = 1024;
  //
  cout<<"-----------------------"<<endl;
  cout<<"V_backWall    = "<<V_backWall/1000.0<<"  cm^3"<<endl
      <<"V_wall        = "<<V_wall/1000.0<<"   cm^3"<<endl
      <<"V_oring       = "<<V_oring/1000.0<<"  cm^3"<<endl;
  cout<<"-----------------------"<<endl;
  cout<<"V_corr        = "<<V_corr/1000.0<<"  cm^3"<<endl;
  cout<<"-----------------------"<<endl;
  cout<<"S_bigmirror   = "<<S_bigmirror/1000000.0<<" m^2"<<endl;
  cout<<"S_smallmirror = "<<S_smallmirror/1000000.0<<" m^2"<<endl;
  cout<<"-----------------------"<<endl;


  cout<<"--------------------------"<<endl;
  cout<<"Back Wall    = "<<m_backWall/1000000.0<<"  kg"<<endl
      <<"Wall         = "<<m_wall/1000000.0<<"  kg"<<endl
      <<"Oring        = "<<m_oring/1000000.0<<" kg"<<endl;
  cout<<"Corrector    = "<<m_corr/1000000.0<<"  kg"<<endl;
  cout<<"Big mirror   = "<<m_bigmirror/1000000.0<<"  kg"<<endl;
  cout<<"Small mirror = "<<m_smallmirror/1000000.0<<" kg"<<endl;
  cout<<"Struct. mat. = "<<2.0<<"        kg"<<endl;
  cout<<"--------------------------"<<endl;  
  cout<<"Redout       = "<<m_asic*n_asic<<"    kg"<<endl;
  cout<<"Sipm         = "<<m_sipm*n_sipm<<"   kg"<<endl;
  cout<<"--------------------------"<<endl;  
  cout<<"Total        = "
      <<(m_backWall + m_wall + m_oring +
	 m_corr + m_bigmirror + m_smallmirror)/1000000.0 +
    m_structMat + m_asic*n_asic + m_sipm*n_sipm
      <<"  kg"<<endl;
  cout<<"--------------------------"<<endl;

  //Double_t S_smallmirror = TMath::Pi()*Dsmall_mirror*Dsmall_mirror/4.0;
  //
  //Double_t m_bigmirror = m_corr;
  //Double_t m_smallmirror = m_bigmirror/(S_bigmirror/S_smallmirror);



  //
  //Double_t S = TMath::Pi()*D*D/4.0;
  //Double_t V_backWall = S*dl;
  //  
  
  
  
  return 0;
}
