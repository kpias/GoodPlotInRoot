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

int pty_plot_v2 (int optInput = 2, int optDraw = 1) {
  Float_t Tb = 3.25 , mnuc = 0.939, Ebeam = Tb + mnuc,
          pbeam = sqrt (Ebeam*Ebeam + mnuc*mnuc) ,
          Bbeam = pbeam/(Ebeam+mnuc), Ynn = atanh (Bbeam);
          
  gStyle->SetOptStat (0);
  gStyle->SetLegendBorderSize (0);
  gStyle->SetLegendTextSize   (0.055);
  gStyle->SetLabelSize  (0.055, "XYZ");
  gStyle->SetNdivisions ( 505 , "XYZ");
  gStyle->SetTextFont (42);
  
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
  
  TCanvas* c1 = new TCanvas ("c1", "", 800, 600);
  c1->SetGrid (0, 0);
  c1->SetTopMargin    (0.10);
  c1->SetBottomMargin (0.13);
  c1->SetRightMargin  (0.13);
  c1->SetLeftMargin   (0.13);
    
  h->UseCurrentStyle();
  h->Draw ("colz");

  h->GetXaxis()->SetTitle ("y");
  h->GetXaxis()->CenterTitle (true);
  h->GetXaxis()->SetTitleOffset (1.10);
  h->GetXaxis()->SetTitleSize(0.055);
  h->GetYaxis()->SetTitle ("p_{T} (GeV/c)");
  h->GetYaxis()->CenterTitle (true);
  h->GetYaxis()->SetTitleOffset (1.0);
  h->GetYaxis()->SetTitleSize(0.055);
  
  if (optDraw == 0)
    return 0;
  else {
    TF1* fpty_th1 = new TF1 ("fptyth1", pt_y_theta, 0, 10, 2);
    fpty_th1->SetParameters (2. , 0.939);
    fpty_th1->SetNpx (500);
    fpty_th1->SetLineColor (14);
    fpty_th1->SetLineStyle (1);
    fpty_th1->SetLineWidth (1);
    fpty_th1->Draw ("same");
  
    TF1* fpty_th2 = new TF1 ("fptyth2", pt_y_theta, 0, 10, 2);
    fpty_th2->SetParameters (25. , 0.939);
    fpty_th2->SetLineColor (13);
    fpty_th2->SetLineStyle (1);
    fpty_th2->SetLineWidth (1);
    fpty_th2->SetNpx (500);
    fpty_th2->Draw ("same");

    TF1* fpty_p0 = new TF1 ("fptyp0", pt_y_ptot , 0.8, 0.925, 2);
    fpty_p0->SetParameters (1.0 , 0.939);
    fpty_p0->SetLineColor (13);
    fpty_p0->SetLineStyle (1);
    fpty_p0->SetLineWidth (1);
    fpty_p0->SetNpx (500);
    fpty_p0->Draw ("same");
    
    TF1* fpty_p1 = new TF1 ("fptyp1", pt_y_ptot , 1.16, 1.497, 2);
    fpty_p1->SetParameters (2.0 , 0.939);
    fpty_p1->SetLineColor (13);
    fpty_p1->SetLineStyle (1);
    fpty_p1->SetLineWidth (1);
    fpty_p1->SetNpx (500);
    fpty_p1->Draw ("same");
  
    TF1* fpty_p2 = new TF1 ("fptyp2", pt_y_ptot , 1.39, 2.146, 2);
    fpty_p2->SetLineColor (13);
    fpty_p2->SetLineStyle (1);
    fpty_p2->SetLineWidth (1);
    fpty_p2->SetParameters (4.0 , 0.939);
    fpty_p2->SetNpx (500);
    fpty_p2->Draw ("same");
  }
  TLine* lYnn = new TLine (Ynn, 0., Ynn, 2.);
  lYnn->SetLineWidth (2);
  lYnn->SetLineStyle (3);
  lYnn->SetLineColor (13);
  lYnn->Draw ("same");
  
  TLatex l;
  l.SetNDC (1);
  l.SetTextFont (42);
  l.SetTextSize (0.049);
  l.DrawLatex (0.135, 0.94, "Au+Au, #it{T}_{Beam} = 3.25A GeV, b = [0..16] fm, protons");
  l.SetTextAngle (82);
  l.SetTextSize (0.04);
  l.DrawLatex (0.505, 0.755, "#vartheta_{L} = 25#circ");
  l.SetTextAngle (15);
  l.DrawLatex (0.66, 0.16, "#vartheta_{L} = 2#circ");
  l.SetTextAngle (90);
  l.DrawLatex (0.405, 0.7, "Y_{NN}");
  l.SetTextAngle (-75);
  l.DrawLatex (0.59, 0.485, "p_{Lab} = 4 GeV");
  l.SetTextAngle (-75);
  l.DrawLatex (0.487, 0.331, "2 GeV");
  l.SetTextAngle (-78);
  l.DrawLatex (0.39, 0.28, "1 GeV");
  return 0;
}
