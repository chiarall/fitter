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


  // Set setSigmaVal
  pdfGenerator->setSigmaXval(3);
  // Set setSigmaVal
  pdfGenerator->setSigmaYval(2);

  // --------------------------------
  // Generate events
  // --------------------------------

  // Sample 10000 events in (x,y) from the model
  RooDataSet* modelData = myPDF->generate(RooArgSet(*x,*y),10000);

  // --------------------------------
  // Fit model to data
  // --------------------------------

  myPDF->fitTo(*modelData);
  // Print values of mean and sigma
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
