#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooLinkedList.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"

RooFitResult* myFitTo(RooAbsPdf& pdf, RooAbsData& data){

  return pdf.fitTo(data, RooFit::Extended(kTRUE), RooFit::SumW2Error(kTRUE));
}
