#ifndef PDF_NEW
#define PDF_NEW

#include "RooAddPdf.h"
#include "RooRealVar.h"

#ifndef ROOT_TObject
#include "TObject.h"
#endif

class PDF : public TObject{

RooRealVar* xvar;
RooRealVar* meanXvar;
RooRealVar* sigmaXvar;

RooRealVar* yvar;
RooRealVar* meanYvar;
RooRealVar* sigmaYvar;

public:
  PDF();
  RooAddPdf* createPDF();
  void print();
  void setSigmaVal(double val);
  RooRealVar* getX();
  RooRealVar* getY();

  ClassDef(PDF,1);

};

#endif
