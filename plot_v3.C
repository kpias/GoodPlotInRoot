int plot_v3 () {
  gStyle->SetOptStat (0);
  gStyle->SetLegendBorderSize (0);
  gStyle->SetLegendTextSize   (0.055);
  gStyle->SetLabelSize  (0.055, "XY");
  gStyle->SetNdivisions ( 505 , "XY");
  gStyle->SetTextFont (42);

  /*** Stage 1: generating some dummy data ***/
  
  TH1F* h = new TH1F ("h", "", 200, -14, 10);
  h->FillRandom ("gaus", 30000);
  h->GetXaxis()->SetTitle ("Position (#mum)");
  h->GetXaxis()->CenterTitle (true);
  h->GetXaxis()->SetTitleOffset (1.25);
  h->GetXaxis()->SetTitleSize(0.055);
  h->GetYaxis()->SetTitle ("Rate (arb. units)");
  h->GetYaxis()->CenterTitle (true);
  h->GetYaxis()->SetTitleOffset (1.5);
  h->GetYaxis()->SetTitleSize(0.055);
  
  TF1* f = new TF1 ("f", "1000*abs(sin(x)/x)", -14, 14);

  Int_t i = 0;
  Double_t x[50], y[50], ex[50], ey[50];
  for (Double_t xval = -9; xval <= 9; xval++, i++) {
    x[i]  = xval;
    y[i]  = 1000 * sin ( (xval + 9)/10 ) ;
    ex[i] = 0.3;
    ey[i] = (xval+9) * 3 ;
  }

  TGraphErrors* g = new TGraphErrors (i, x, y, ex, ey);

  /*** Stage 2: Data visualization ***/
        
  TCanvas* c1 = new TCanvas ("c1", "", 800, 600);
  c1->SetTopMargin    (0.05);
  c1->SetBottomMargin (0.15);
  c1->SetRightMargin  (0.04);
  c1->SetLeftMargin   (0.16);
  
  h->Draw ();
  f->Draw ("same");
  g->Draw ("P");

  TLegend* leg = new TLegend (0.21, 0.67, 0.48, 0.90, "", "NDC");
  leg->AddEntry ( h , "   Experiment" , "f"  );
  leg->AddEntry ("f", "   Model"      , "l"  );
  leg->AddEntry ("g", "   Efficiency" , "lep");
  leg->Draw ();
  return 0;
}
