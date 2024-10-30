Double_t pt_y_theta (Double_t* xarg, Double_t* par)  {
  Double_t y = xarg[0] ,
           theta = par[0] ,
           mass  = par[1] ;
           
  Double_t u = sinh(y) * tan ( theta * M_PI/180. ) ,
           pt_value = 
           (u < 1.) ? mass * u / sqrt(1. - u*u) : 0. ;

  return (pt_value > 0. ) ? pt_value : 10. ;
}

Double_t pt_y_ptot (Double_t* xarg, Double_t *par) {
  Double_t y  = xarg[0] ,
         ptot = par[0] ,
         mass = par[1] ;
         
  Double_t u = pow(ptot, 2.) - pow(mass*sinh(y) , 2.);

  return (u > 0.) ? sqrt(u) / cosh(y) : 0. ;
}

int pty_plot (int optInput = 1, int optDraw = 1) {
  Float_t Tb = 3.25 , mnuc = 0.939, Ebeam = Tb + mnuc,
          pbeam = sqrt (Ebeam*Ebeam + mnuc*mnuc) ,
          Bbeam = pbeam/(Ebeam+mnuc), Ynn = atanh (Bbeam);
  TFile* f;
  TH2F * h;

  if (optInput == 1) {
    f = new TFile ("phqmd_auau3.25GeV_u2t_prot.root");
    h = new TH2F ("hptyraw", "", 50, -0.5, 3, 50, 0, 2);
    TTree* t = (TTree*) f->Get ("t");
    t->Project ("hptyraw", "pt:ylab") ;
  }
  else if (optInput == 2) {
    f = new TFile ("phqmd_auau3.25GeV_cbmreco_prot.root"); 
    h = (TH2F*) f->Get ("prot_pty");
    h->SetName ("hptyreco");
  }
  h->Draw ("colz");

  if (optDraw == 0)
    return 0;
  else {
    TF1* fpty_th1 = new TF1 ("fptyth1", pt_y_theta, 0, 10, 2);
    fpty_th1->SetParameters (2. , 0.939);
    fpty_th1->Draw ("same");
  
    TF1* fpty_th2 = new TF1 ("fptyth2", pt_y_theta, 0, 10, 2);
    fpty_th2->SetParameters (25. , 0.939);
    fpty_th2->Draw ("same");

    TF1* fpty_p0 = new TF1 ("fptyp0", pt_y_ptot , 0, 10, 2);
    fpty_p0->SetParameters (1.0 , 0.939);
    fpty_p0->Draw ("same");
    
    TF1* fpty_p1 = new TF1 ("fptyp1", pt_y_ptot , 0, 10, 2);
    fpty_p1->SetParameters (2.0 , 0.939);
    fpty_p1->Draw ("same");
  
    TF1* fpty_p2 = new TF1 ("fptyp2", pt_y_ptot , 0, 10, 2);
    fpty_p2->SetParameters (4.0 , 0.939);
    fpty_p2->Draw ("same");
  }
  TLine* lYnn = new TLine (Ynn, 0., Ynn, 2.);
  lYnn->SetLineWidth (2);
  lYnn->Draw ("same");
  return 0;
}
