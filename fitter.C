#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include "TApplication.h"

#include "PDF.h"
using namespace std ;
using namespace RooFit ;




void fitter(){

  PDF * pdfGenerator = new PDF();
  RooAddPdf* myPDF = pdfGenerator->createPDF();

  RooRealVar* x = pdfGenerator->getX();
  RooRealVar* y = pdfGenerator->getY();

  // Construct plot frame in 'x'
  //RooPlot* xframe = x->frame(Title("Gaussian p.d.f.")) ;

  //
  // // P l o t   m o d e l   a n d   c h a n g e   p a r a m e t e r   v a l u e s
  // // ---------------------------------------------------------------------------
  //
  // // Plot gauss in frame (i.e. in x)
  //myPDF->plotOn(xframe) ;
  //
  // // Change the value of sigma to 3
  //pdfGenerator->setSigmaVal(3) ;
  //
  // // Plot gauss in frame (i.e. in x) and draw frame on canvas
  //myPDF->plotOn(xframe,LineColor(kRed)) ;
  //
  //
  // // G e n e r a t e   e v e n t s
  // // -----------------------------
  //
  // Sample 10000 events in (x,y) from the model
  RooDataSet* modelData = myPDF->generate(RooArgSet(*x,*y),10000) ;
  //
  // // Make a second plot frame in x and draw both the
  // // data and the p.d.f in the frame
  //RooPlot* xframe2 = x->frame(Title("Gaussian p.d.f. with data")) ;
  //data->plotOn(xframe2) ;
  //myPDF->plotOn(xframe2) ;
  //
  //
  // // F i t   m o d e l   t o   d a t a
  // // -----------------------------
  //
  // // Fit pdf to data
  myPDF->fitTo(*modelData) ;
  // // Print values of mean and sigma (that now reflect fitted values and errors)
  pdfGenerator->print();
  //
  // // Draw all frames on a canvas
  // TCanvas* c = new TCanvas("rf101_basics","rf101_basics",800,400) ;
  // c->Divide(2) ;
  // c->cd(1) ; gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.6) ;
  // xframe->Draw() ;
  // c->cd(2) ; gPad->SetLeftMargin(0.15) ; xframe2->GetYaxis()->SetTitleOffset(1.6) ;
  // xframe2->Draw() ;

}

int main(int argc, char **argv){
  TApplication theApp("App",&argc, argv);
  fitter();
  theApp.Run();
 return 0;
}
