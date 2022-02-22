void print_v_info(TVector3  const &v);
void print_pointer_v_info(TVector3 *v);

Int_t vec_test(){
  //
  Double_t R = 1;
  Double_t theta = 45.0*TMath::Pi()/180.0;
  Double_t phi = 45.0*TMath::Pi()/180.0;
  TVector3 v;
  TVector3 *vv = new TVector3();
  v.SetMagThetaPhi(R,theta,phi);
  vv->SetMagThetaPhi(R,theta,phi);
  //
  print_v_info(v);
  v.RotateZ(-phi);
  v.RotateY(-theta);
  print_v_info(v);
  v.RotateY(theta);
  v.RotateZ(phi);
  print_v_info(v);
  //  
  print_pointer_v_info(vv);
  vv->RotateZ(-phi);
  vv->RotateY(-theta);
  print_pointer_v_info(vv);
  vv->RotateY(theta);
  vv->RotateZ(phi);
  print_pointer_v_info(vv);
  //vv->RotateZ(-phi);
  //

  TVector3 vt1(1,1,1);
  TVector3 vt2(2,2,2);
  TVector3 vt3 = vt1-vt2;

  print_v_info(vt1);
  
  return 0;
}

void print_v_info(TVector3  const &v){
  cout<<v.x()<<endl
      <<v.y()<<endl
      <<v.z()<<endl;
  cout<<v.Theta()<<endl
      <<v.Phi()<<endl;
  cout<<"--------"<<endl;
}

void print_pointer_v_info(TVector3 *v){
  cout<<v->x()<<endl
      <<v->y()<<endl
      <<v->z()<<endl;
  cout<<"--------"<<endl;
}
