int firstPlot () 
{
  /*** Stage 1: generating some dummy data ***/
  
  TH1F* h = new TH1F ("h", "My histo", 200, -14, 10);
  h->FillRandom ("gaus", 30000);
  
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
  
  h->Draw ();
  f->Draw ("same");
  g->Draw ("P");

  return 0;
}
