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
  // **************************************
  // ** PDF for the x observable         **
  // ** signal: gaussian  (gaussianX)    **
  // ** background: polynomial  (px)     **
  // **************************************

  //Define the observable x, the mean and the sigma of the gaussian for the x observable
  xvar = new RooRealVar("xvar","xvar",-10,10);
  meanXvar = new RooRealVar("meanXvar","mean of gaussian for x variable",1,-10,10);
  sigmaXvar = new RooRealVar("sigmaXvar","width of gaussian for x variable",1,0.1,10);
  // signal PDF for the x observable
  gaussianX = new RooGaussian("gaussianX","gaussian PDF for x variable",*xvar,*meanXvar,*sigmaXvar);

  // background PDF for the x observable
  px = new RooPolynomial("px","px",*xvar);

  // **************************************
  // ** PDF for the y observable         **
  // ** signal: gaussian  (gaussianY)    **
  // ** background: polynomial  (py)     **
  // **************************************

  //Define the observable y, the mean and the sigma of the gaussian for the y observable
  yvar = new RooRealVar("yvar","yvar",-10,10);
  meanYvar = new RooRealVar("meanYvar","mean of gaussian for y variable",1,-10,10);
  sigmaYvar = new RooRealVar("sigmaYvar","width of gaussian for y variable",1,0.1,10);
  // signal PDF for the y observable
  gaussianY = new RooGaussian("gaussianY","gaussian PDF for y variable",*yvar,*meanYvar,*sigmaYvar);

  // background PDF for the y observable
  py = new RooPolynomial("py","py",*yvar);


}

RooAbsPdf * PDF::createPDF(){


  // ********************************
  // *** construct the signal pdf  **
  // ********************************
  // x and y not correlated -> construct the signal pdf gaussianX * gaussianY
  RooProdPdf* sig_pdf = new RooProdPdf("sig_pdf","signal PDF",*gaussianX,*gaussianY);

  // *********************************************
  // *** construct the background pdf px * py ****
  // *********************************************
  RooProdPdf* bkg_pdf = new RooProdPdf("bkg_pdf","background PDF",*px,*py);

  // fraction of signal f_sig
  RooRealVar* f_sig = new RooRealVar("f_sig","fraction of signal",0.,1.);

  // ********************************************
  // ** model = f_sig * sig + (1-f_sig) * bkg  **
  // ********************************************
  RooAddPdf* model = new RooAddPdf("model","model",RooArgList(*sig_pdf,*bkg_pdf),*f_sig);

  return model;
}

void PDF::setSigmaXval(double val){
  sigmaXvar->setVal(val);
}

void PDF::setSigmaYval(double val){
  sigmaYvar->setVal(val);
}

void PDF::setMeanXval(double val){
  meanXvar->setVal(val);
}

void PDF::setMeanYval(double val){
  meanYvar->setVal(val);
}

void PDF::print(){
  meanXvar->Print() ;
  sigmaXvar->Print() ;
  meanYvar->Print() ;
  sigmaYvar->Print() ;
}

 RooAbsPdf * PDF::getSigPDF(){
   return gaussianX;
 }

 RooAbsPdf * PDF::getBkgPDF(){
   return px;
 }

RooRealVar * PDF::getX(){
  return xvar;
}

RooRealVar * PDF::getY(){
  return yvar;
}
