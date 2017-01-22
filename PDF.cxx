#include "PDF.h"
#include <iostream>
#include "RooGaussian.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooPolynomial.h"
#include "RooRealVar.h"
#include "TObject.h"

ClassImp(PDF)

PDF::PDF(): TObject(){
  //Define the observable x, the mean and the sigma of the gaussian for the x observable
  xvar = new RooRealVar("xvar","xvar",-10,10);
  meanXvar = new RooRealVar("meanXvar","mean of gaussian for x variable",1,-10,10);
  sigmaXvar = new RooRealVar("sigmaXvar","width of gaussian for x variable",1,0.1,10);

  //Define the observable y, the mean and the sigma of the gaussian for the y observable
  yvar = new RooRealVar("yvar","yvar",-10,10);
  meanYvar = new RooRealVar("meanYvar","mean of gaussian for y variable",1,-10,10);
  sigmaYvar = new RooRealVar("sigmaYvar","width of gaussian for y variable",1,0.1,10);
}

RooAddPdf * PDF::createPDF(){
  // Construct the signal pdf gauss(x)*gauss(y)
  RooGaussian* gaussianX = new RooGaussian("gaussianX","gaussian PDF for x variable",*xvar,*meanXvar,*sigmaXvar);
  RooGaussian* gaussianY = new RooGaussian("gaussianY","gaussian PDF for y variable",*yvar,*meanYvar,*sigmaYvar);
  RooProdPdf* sig = new RooProdPdf("sig","signal PDF",*gaussianX,*gaussianY);

  // Construct the background pdf (flat in x,y)
  RooPolynomial* px = new RooPolynomial("px","px",*xvar);
  RooPolynomial* py = new RooPolynomial("py","py",*yvar);
  RooProdPdf* bkg = new RooProdPdf("bkg","background PDF",*px,*py);

  RooRealVar* f_sig = new RooRealVar("f_sig","fraction of signal",0.,1.);
  RooAddPdf* model = new RooAddPdf("model","model",RooArgList(*sig,*bkg),*f_sig);

  return model;
}

void PDF::setSigmaVal(double val){
  sigmaXvar->setVal(val);
}

void PDF::print(){
  meanXvar->Print() ;
  sigmaXvar->Print() ;
  meanYvar->Print() ;
  sigmaYvar->Print() ;
}

RooRealVar* PDF::getX(){
  return xvar;
}

RooRealVar* PDF::getY(){
  return yvar;
}
