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

void plotFunction(PDF* pdfObject,RooDataSet* modelData);

void fitter(){

  PDF * pdfGenerator = new PDF();
  RooAbsPdf* myPDF = pdfGenerator->createPDF();

  RooRealVar* x = pdfGenerator->getX();
  RooRealVar* y = pdfGenerator->getY();

  // Set setSigmaVal
  pdfGenerator->setSigmaXval(1);
  // Set setSigmaVal
  pdfGenerator->setSigmaYval(1);

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

  plotFunction(pdfGenerator,modelData);

}

int main(int argc, char **argv){
  TApplication theApp("App",&argc, argv);
  fitter();
  theApp.Run();
 return 0;
}

void plotFunction(PDF* pdfObject, RooDataSet* modelData){

  RooRealVar* x = pdfObject->getX();
  RooRealVar* y = pdfObject->getY();

  RooAbsPdf* pdfSigX = pdfObject->getSigPDF();
  RooAbsPdf* pdfBkgX = pdfObject->getBkgPDF();

  RooAbsPdf* myPDF = pdfObject->getModel();
  // ------------------------------------------
  // Plot histograms
  // ------------------------------------------
  // frame for x projection
  RooPlot* xframe = x->frame();
  // frame for y projection
  RooPlot* yframe = y->frame();

  TCanvas* c = new TCanvas("x observable","x observable",800,400);
  c->Divide(2);
  c->cd(1);
  // Plot x distribution of data and projection of model on x = Int(dy) model(x,y)
  modelData->plotOn(xframe);
  myPDF->plotOn(xframe);
  myPDF->plotOn(xframe,Components(pdfSigX->GetName()),LineColor(kRed));
  xframe->getAttLine()->SetLineWidth(1.0);
  myPDF->plotOn(xframe,Components(pdfBkgX->GetName()),LineColor(kBlack));
  xframe->getAttLine()->SetLineWidth(1.0);
  xframe->getAttLine()->SetLineStyle(kDashed);
  xframe->Draw();
  c->cd(2);
  // Plot y distribution of data and projection of model on y = Int(dx) model(x,y)
  modelData->plotOn(yframe);
  myPDF->plotOn(yframe);
  yframe->Draw();

}
