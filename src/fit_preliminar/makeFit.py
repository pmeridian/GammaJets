#!/usr/bin/env python

from optparse import OptionParser, make_option
from ROOT import *
import subprocess
import multiprocessing
import os

gSystem.Load('libRooFit')

treeName="finalTree"
data = TChain(treeName)
mc = TChain(treeName)

#Global text print on top of the plots
text="CMS Preliminary #sqrt{s}=8 TeV"

# associate name of the variable to the expression to print it. This list should contain all the variables to plot
variables={}
variables['combinedPfIso03Phot']='combinedPfIso03Phot'

#variables needed to perform fit, excluding fit variable
fitVariables={}
fitVariables['etaPhot']=dict(name='etaPhot', xmin=-2.5, xmax=2.5)
fitVariables['mvaIdPhot']=dict(name='mvaIdPhot', xmin=-1., xmax=1.)
#fitVariables['combinedPfIso03Phot']=dict(name='combinedPfIso03Phot', xmin=-10, xmax=20)
fitVariables['isMatchedPhot']=dict(name='isMatchedPhot', xmin=-1., xmax=2.)
fitVariables['weight']=dict(name='weight', xmin=0, xmax=100)



#characteristics of the plot of a given variable
plotPars={}
plotPars['combinedPfIso03Phot']=dict( name='combinedPfIso03Phot', nBins=200, xMin=-5, xMax=15, xaxisLabel="combined PfIso #DeltaR=0.3 (GeV)")

#possible selections for the plots
cuts={}
#cuts['All']='1' #just to avoid error
cuts['EB_WP08']='abs(etaPhot)<1.4442  && mvaIdPhot>0.878893'
cuts['EE_WP08']='abs(etaPhot)>1.566 && abs(etaPhot)<2.5  && mvaIdPhot>0.850808'
cuts['EB_WP09']='abs(etaPhot)<1.4442  && mvaIdPhot>0.812948'
cuts['EE_WP09']='abs(etaPhot)>1.566 && abs(etaPhot)<2.5  && mvaIdPhot>0.73721'
cuts['EB_WP095']='abs(etaPhot)<1.4442  && mvaIdPhot>0.711099'
cuts['EE_WP095']='abs(etaPhot)>1.566 && abs(etaPhot)<2.5  && mvaIdPhot>0.581733'

#different types of MC (and corresponding selection to differentiate them using ntuple variables)
mc_types={}
mc_types['Signal']="isMatchedPhot==1"
mc_types['Bkg']="isMatchedPhot==0"

#name of the variable to use as weight in MC
weight_var="weight"

#options to draw data and MC plots
draw_opts={}
#draw_opts['data']=dict( SetMarkerSize=0.7,SetMarkerStyle=20,SetLineColor=1 )
draw_opts['mc_Bkg']=dict( SetLineColor=kMagenta,SetLineWidth=2,SetFillColor=kMagenta,SetFillStyle=1001, SetMarkerColor=kMagenta)
draw_opts['mc_Signal']=dict( SetLineColor=kCyan,SetLineWidth=2,SetFillColor=kCyan,SetFillStyle=1001, SetMarkerColor=kCyan )

histos={}
rooDataSets={}
rooRealVars={}
rooPdfs={}
graphs={}

ROOT.gROOT.SetBatch()
ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetOptStat(0)
gROOT.ProcessLine(".L myFitTo.C++")

def customizeCanvas(c):
    c.Range(0,0,1,1)
    c.SetFillColor(0)
    c.SetBorderMode(0)
    c.SetBorderSize(2)
    c.SetTickx(1)
    c.SetLeftMargin(0.13)
    c.SetRightMargin(0.07)
    c.SetTopMargin(0.09)
    c.SetBottomMargin(0.1)
    c.SetFrameFillStyle(0)
    c.SetFrameBorderMode(0)

def splitCanvas(c):
    pads=[]
    pads.append(TPad("pad1","pad1",0,0.3,1.,1.))
    pads.append(TPad("pad2","pad2",0,0.,1.,0.3))
    for pad in pads:
        pad.Draw()
    return pads

def drawText(additional_text):
    tex_m=TLatex()
    tex_m.SetNDC()
    tex_m.SetTextAlign(12)
    tex_m.SetTextSize(0.037)
    tex_m.SetLineWidth(2)
    tex_m.DrawLatex(0.25,0.94,text)
    
    if (additional_text != ""):
        tex_m.SetTextSize(0.045)
        tex_m.DrawLatex(0.63,0.63,additional_text)

def declareRooRealVars(argSet):
    for variable in fitVariables.keys():
        rooRealVars[fitVariables[str(variable)]['name']] = RooRealVar(fitVariables[str(variable)]['name'], fitVariables[str(variable)]['name'], fitVariables[str(variable)]['xmin'], fitVariables[str(variable)]['xmax'])
        argSet.add(rooRealVars[fitVariables[str(variable)]['name']])

def signalPdf(var):    
    landaumean = RooRealVar("landaumean", "landaumean" , -1.8, -7., 5.) 
    landausigma = RooRealVar("landausigma", "landausigma" , 1.0, 0.1, 4.0) 
    my_landau = RooLandau("my_landau", "landau distribution", var, landaumean, landausigma)
    Lambda = RooRealVar("Lambda", "Lambda", -1., -100., 0.)
    A = RooRealVar("A", "A", 0.01, 0.001, 1.)
    m = RooRealVar("m", "m", -100., -10000., 0.)
    my_expo = RooGenericPdf("my_expo", "my shifted expo", "A*exp(lambda*(var-m))", RooArgList(var, A, Lambda, m))
    sig_pdf = RooProdPdf("sig_pdf","expo (X) landau", RooArgSet(var,my_expo,my_landau), RooLinkedList()) 
    return sig_pdf

def backgroundPdf(var):    
    gaussmean = RooRealVar("gaussmean", "gaussmean" , -1.8, -7., 5.) 
    gausssigma = RooRealVar("gausssigma", "gausssigma" , 1.0, 0.1, 4.0) 
    my_gauss = RooGaussian("my_gauss", "gauss distribution", var, gaussmean, gausssigma)
    Lambda = RooRealVar("Lambda", "Lambda", -1., -100., 0.)
    A = RooRealVar("A", "A", 0.01, 0.001, 1.)
    m = RooRealVar("m", "m", -100., -10000., 0.)
    my_expo = RooGenericPdf("my_expo", "my shifted expo", "A*exp(lambda*(var-m))", RooArgList(var, A, Lambda, m))
    bkg_pdf = RooProdPdf("bkg_pdf","expo (X) gauss",RooArgSet(my_expo,my_gauss), RooLinkedList()) 
    return bkg_pdf

#def plot(variable,plotsDir,additional_cuts="1",pars['additional_text']="",savefmts=[".C",".png",".pdf"]):
def plot(pars,savefmts=[".C",".png",".pdf",".root"]):
    print "preparing ArgSet"
    argSet = RooArgSet('argSet')
#    declareRooRealVars(argSet)
    for variable in fitVariables.keys():
        rooRealVars[fitVariables[str(variable)]['name']] = RooRealVar(fitVariables[str(variable)]['name'], fitVariables[str(variable)]['name'], fitVariables[str(variable)]['xmin'], fitVariables[str(variable)]['xmax'])
        argSet.add(rooRealVars[fitVariables[str(variable)]['name']])
    combinedPfIso03Phot = RooRealVar('combinedPfIso03Phot', 'combinedPfIso03Phot', -10., 20.)
    argSet.add(combinedPfIso03Phot)
#    list=RooLinkedList()
    print "creating canvas"
    c = TCanvas(pars['variable'],pars['variable'],1000,900)
    customizeCanvas(c)
    outputFile_plots = TFile(str(pars['plotsDir'])+'/plots_'+str(pars['variable'])+'.root', 'RECREATE')
    print "creating complete dataset"
    all = RooDataSet('all', 'all', argSet, RooFit.WeightVar(rooRealVars[fitVariables['weight']['name']]), RooFit.Import(mc)) #Import(mc)?
#    all = RooDataSet('all', 'all', argSet, RooFit.Import(mc)) #Import(mc)?
    print "starting for"
    for cut in cuts.keys():
        for type in mc_types.keys():
            rooDataSets[str(cut)+'_mc_'+str(type)] = all.reduce(str(cuts[cut])+"&&"+str(mc_types[type]))
            rooDataSets[str(cut)+'_mc_'+str(type)].SetName('dataset_'+str(cut)+'_mc_'+str(type))
            print "Reduced dataset created with name: "+rooDataSets[str(cut)+'_mc_'+str(type)].GetName()
            debug_histo = rooDataSets[str(cut)+'_mc_'+str(type)].createHistogram(combinedPfIso03Phot, rooRealVars[fitVariables['etaPhot']['name']])
            debug_histo.Draw()
            for format in savefmts:
                c.SaveAs(pars['plotsDir']+"/debugHisto_"+str(cut)+format)
            histos[str(pars['variable'])+'_mc_'+type+"_"+str(cut)]=TH1F(str(plotPars[str(pars['variable'])]['name'])+"_mc_"+type+"_"+str(cut),str(plotPars[str(pars['variable'])]['name'])+"_mc_"+type+"_"+str(cut),plotPars[str(pars['variable'])]['nBins'],plotPars[str(pars['variable'])]['xMin'],plotPars[str(pars['variable'])]['xMax'])
            histos[str(pars['variable'])+'_mc_'+type+"_"+str(cut)].Sumw2()
            mc.Project( histos[str(pars['variable'])+'_mc_'+type+"_"+str(cut)].GetName(), str(variables[str(pars['variable'])]), "("+str(cuts[cut])+"&&"+pars['additional_cuts']+"&&"+str(mc_types[type])+")*"+weight_var )
#            mc.Project( histos[str(pars['variable'])+'_mc_'+type+"_"+str(cut)].GetName(), str(variables[str(pars['variable'])]), "("+str(cuts[cut])+"&&"+pars['additional_cuts']+"&&"+str(mc_types[type])+")" )
            histos[str(pars['variable'])+'_mc_'+type+"_"+str(cut)].Print()
            for aopt in draw_opts['mc_'+type].keys():
                a=histos[str(pars['variable'])+'_mc_'+type+"_"+str(cut)]
                eval('a.'+str(aopt)+'('+str(draw_opts['mc_'+type][aopt])+')')
        #preparing pdfs
        print "preparing pdfs"
#        rooPdfs['Signal']=signalPdf(rooRealVars[fitVariables['combinedPfIso03Phot']['name']])
        landaumean = RooRealVar("landaumean", "landaumean" , -0.5, -7., 5.) 
        landausigma = RooRealVar("landausigma", "landausigma" , 1.0, 0.00001, 20.) 
        my_landau = RooLandau("my_landau", "landau distribution", combinedPfIso03Phot, landaumean, landausigma)
        tau_s = RooRealVar("tau_s", "tau_s", -0.4, -10000., 0.)
        my_expo_s = RooExponential("my_expo_s", "my expo_s", combinedPfIso03Phot, tau_s)
        sig_pdfs = RooArgList(my_expo_s, my_landau)
        nsig = RooRealVar("nsig", "expexted number of ev for sig", 360000., 100., 100000000.)
        signal_ProdPdf = RooProdPdf("signal_ProdPdf","expo (X) landau, not extended", sig_pdfs)
        rooPdfs['Signal'] = RooExtendPdf("sig_pdf", "expo (X) landau, extended", signal_ProdPdf, nsig)
#        rooPdfs['Signal'] = RooFFTConvPdf("sig_pdf","expo (X) landau", combinedPfIso03Phot,my_expo, my_landau)
#        rooPdfs['Signal'] = my_landau
#        rooPdfs['Bkg']=backgroundPdf(rooRealVars[fitVariables['combinedPfIso03Phot']['name']])
        gaussmean = RooRealVar("gaussmean", "gaussmean" , -0.8, -7., 5.) 
        gausssigma = RooRealVar("gausssigma", "gausssigma" , 0.2, 0.00001, 20.0) 
        my_gauss = RooGaussian("my_gauss", "gauss distribution", combinedPfIso03Phot, gaussmean, gausssigma)
        tau_b = RooRealVar("tau_b", "tau_b", -1., -10000., 0.)
        my_expo_b = RooExponential("my_expo_b", "my expo_b", combinedPfIso03Phot, tau_b)
        bkg_pdfs = RooArgList(my_expo_b, my_gauss)
        nbkg = RooRealVar("nbkg", "expexted number of ev for bkg", 50000., 100., 100000000.)
        bkg_ProdPdf = RooProdPdf("bkg_prodPdf","expo (X) gauss, not extended", bkg_pdfs)
        rooPdfs['Bkg'] = RooExtendPdf("bkg_pdf", "expo (X) landau, extended", bkg_ProdPdf, nbkg)
#        rooPdfs['Bkg'] = RooFFTConvPdf("bkg_pdf","expo (X) gauss",combinedPfIso03Phot,my_expo_b,my_gauss)
#        rooPdfs['Bkg'] = my_gauss
        frame = combinedPfIso03Phot.frame(RooFit.Title("Fit to combinedPfIso03Phot")) 
        rooPdfs['Signal'].plotOn(frame, RooFit.LineColor(kCyan), RooFit.Normalization(1.0,RooAbsReal.RelativeExpected))
        rooPdfs['Bkg'].plotOn(frame, RooFit.LineColor(kMagenta), RooFit.Normalization(1.0,RooAbsReal.RelativeExpected))
        print "drawing"
        print "draw first histo"
        histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].Draw("E")
        print "set max"
        histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].SetMaximum(histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].GetMaximum()*1.4)
        print "set min"
        histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].SetMinimum(0)
        print "set xlabel"
        histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].GetXaxis().SetTitle(str(plotPars[str(pars['variable'])]['xaxisLabel']))
        print "set ylabel"        
        histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].GetYaxis().SetTitle('Entries/'+str(histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].GetBinWidth(1)))
        print "set title"
        histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].GetYaxis().SetTitleOffset(1.5)
        print "draw second histo"
        histos[str(pars['variable'])+'_mc_Bkg_'+str(cut)].Draw("ESAME")
        print "draw fits"
        frame.Draw("same")

        print "preparing Legend"
        #Legend
        a=TLegend(0.63,0.68,0.88,0.88)
        a.SetBorderSize(0)
        a.SetFillColor(0)
        a.SetTextSize(0.038)
        a.SetHeader(str(cut))
        print "adding entries"
        for mc_type in mc_types.keys():
             a.AddEntry( histos[str(pars['variable'])+'_mc_'+mc_type+"_"+str(cut)], mc_type+', '+str(rooPdfs[str(mc_type)].GetName()), "F" )
        print "drawing legend"
        a.Draw()
       
        for format in savefmts:
            c.SaveAs(pars['plotsDir']+"/debugHisto_PDF_"+str(cut)+format)
        print "Signal pdf with name: "+rooPdfs['Signal'].GetName()
        #fit pdfs to datasets
        print "fitting datasets to pdfs"
#        fitlist = RooLinkedList()
 #       fitlist.Add(RooFit.FitOptions("v"))
        count = 1
        for mc_type in mc_types.keys():
            print "fit #"+str(count)
            count += 1
            myFitTo(rooPdfs[str(mc_type)], rooDataSets[str(cut)+'_mc_'+str(mc_type)])
        frame = combinedPfIso03Phot.frame(RooFit.Title("Fit to combinedPfIso03Phot")) 
        rooPdfs['Signal'].plotOn(frame, RooFit.LineColor(kCyan))
        rooPdfs['Bkg'].plotOn(frame, RooFit.LineColor(kMagenta))
        print frame.GetName()

        print "drawing"
        print "draw first histo"
        histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].Draw("E")
        print "set max"
        histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].SetMaximum(histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].GetMaximum()*1.4)
        print "set min"
        histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].SetMinimum(0)
        print "set xlabel"
        histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].GetXaxis().SetTitle(str(plotPars[str(pars['variable'])]['xaxisLabel']))
        print "set ylabel"        
        histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].GetYaxis().SetTitle('Entries/'+str(histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].GetBinWidth(1)))
        print "set title"
        histos[str(pars['variable'])+'_mc_Signal_'+str(cut)].GetYaxis().SetTitleOffset(1.5)
        print "draw second histo"
        histos[str(pars['variable'])+'_mc_Bkg_'+str(cut)].Draw("ESAME")
        print "draw fits"
        frame.Draw("same")

        print "preparing Legend"
        #Legend
        a=TLegend(0.63,0.68,0.88,0.88)
        a.SetBorderSize(0)
        a.SetFillColor(0)
        a.SetTextSize(0.038)
        a.SetHeader(str(cut))
        print "adding entries"
        for mc_type in mc_types.keys():
             a.AddEntry( histos[str(pars['variable'])+'_mc_'+mc_type+"_"+str(cut)], mc_type+', '+str(rooPdfs[str(mc_type)].GetName()), "F" )
        print "drawing legend"
        a.Draw()

        #Additional text
        drawText(pars['additional_text'])

        #Save plots
        #c.SetLogy(0)
        for format in savefmts:
            c.SaveAs(pars['plotsDir']+"/fitTo_"+str(pars['variable'])+str(cut)+format)
    outputFile_plots.Write()
    outputFile_plots.Close()
  
    
def main(options,args):

    print "+++++++++++++++++++++++++++++++++++++++++++"
    print "Processing with options: "
    print options
    print "+++++++++++++++++++++++++++++++++++++++++++"

    plotsDir=options.plotsDir
    additionalText=options.additionalText
    additionalCuts=options.additionalCuts

    #Creating output dir
    try:
        os.mkdir(plotsDir)
    except:
        pass

    #Reading data files list
    lines = [line.strip() for line in open(options.dataFiles)]
    for line in lines:
        if line.startswith('#'):
            continue
        data.Add(line)

    #Reading mc files list
    lines = [line.strip() for line in open(options.mcFiles)]
    for line in lines:
        if line.startswith('#'):
            continue
        mc.Add(line)
    #Setting up parallel processing
    ncpu=multiprocessing.cpu_count()

    if (options.numberOfCPU>0):
        ncpu=options.numberOfCPU
        
    pool = multiprocessing.Pool(processes=ncpu)

    #run all the samples in parallel 
    pars=[ dict(variable=x,plotsDir=plotsDir,additional_cuts=additionalCuts,additional_text=additionalText) for x in variables.keys() ]
    #      print pars
    pool.map(plot, pars)

    #for variable in variables.keys():
    #    plot(variable,plotsDir,additionalCuts,additionalText)

    
if __name__ == "__main__":
    parser = OptionParser(option_list=[
        make_option("--dataFiles",
                    action="store", type="string", dest="dataFiles",
                    default="data.txt",
                    help="", metavar=""
                    ),
        make_option("--mcFiles",
                    action="store", type="string", dest="mcFiles",
                    default="mc.txt",
                    help="", metavar=""
                    ),
        make_option("--plotsDir",
                    action="store", type="string", dest="plotsDir",
                    default="plots/",
                    help="", metavar=""
                    ),
        make_option("--additionalText",
                    action="store", type="string", dest="additionalText",
                    default="",
                    help="", metavar=""
                    ),
        make_option("--additionalCuts",
                    action="store", type="string", dest="additionalCuts",
                    default="1",
                    help="", metavar=""
                    ),
        make_option("--numberOfCPU",
                    action="store", type="int", dest="numberOfCPU",
                    default=-1,
                    help="", metavar=""
                    )
        ])
    
    (options, args) = parser.parse_args()
    
    main( options, args) 
