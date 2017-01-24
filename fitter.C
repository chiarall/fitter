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

    // // G e n e r a t e   e v e n t s
  // // -----------------------------
  //
  // Sample 10000 events in (x,y) from the model
  RooDataSet* modelData = myPDF->generate(RooArgSet(*x,*y),10000) ;

  // // F i t   m o d e l   t o   d a t a
  // // -----------------------------
  //
  // // Fit pdf to data
  myPDF->fitTo(*modelData) ;
  // // Print values of mean and sigma (that now reflect fitted values and errors)
  pdfGenerator->print();

  // ------------------------------------------
  // Plot histograms
  // ------------------------------------------


  // frame for x projection
  RooPlot* xframe = x->frame();
  // frame for y projection
  RooPlot* yframe = y->frame();

      // Plot x distribution of data and projection of model on x = Int(dy) model(x,y)
      // Plot y distribution of data and projection of model on y = Int(dx) model(x,y)
  
  modelData->plotOn(yframe);
  myPDF->plotOn(yframe);

}

int main(int argc, char **argv){
  TApplication theApp("App",&argc, argv);
  fitter();
  theApp.Run();
 return 0;
}
