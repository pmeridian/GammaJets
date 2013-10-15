#!/usr/bin/env python

from optparse import OptionParser, make_option
from ROOT import *
import subprocess
import multiprocessing
import os

treeName="finalTree"
#data = TChain(treeName)
mc = TChain(treeName)

#Global text print on top of the plots
text="CMS Preliminary #sqrt{s}=8 TeV"

# associate name of the variable to the expression to print it. This list should contain all the variables to plot
variables={}
variables['ptPhotGen']='ptPhotGen'
variables['ptPhot']='ptPhot'
#variables['etaPhot']='etaPhot'
#variables['mvaIdPhot']='mvaIdPhot'
#variables['nvtx']='nvtx'
#variables['combinedPfIso03Phot']='combinedPfIso03Phot'
#variables['rho']='rho'

#characteristics of the plot of a given variable
plotPars={}
plotPars['ptPhotGen']=dict( name='ptPhotGen', nBins=200, xMin=0., xMax=300., xaxisLabel="#gamma p_{T} (GeV)")
plotPars['ptPhot']=dict( name='ptPhot', nBins=200, xMin=0., xMax=300., xaxisLabel="#gamma p_{T} (GeV)")
#plotPars['etaPhot']=dict( name='etaPhot', nBins=60, xMin=-3., xMax=3., xaxisLabel="#gamma #eta")
#plotPars['mvaIdPhot']=dict( name='mvaIdPhot', nBins=100, xMin=0., xMax=1., xaxisLabel="#gamma MVA output")
#plotPars['nvtx']=dict( name='nvtx', nBins=41, xMin=-0.5, xMax=40.5, xaxisLabel="nvtx")
#plotPars['combinedPfIso03Phot']=dict( name='combinedPfIso03Phot', nBins=200, xMin=-5, xMax=15, xaxisLabel="combined PfIso #DeltaR=0.3 (GeV)")
#plotPars['rho']=dict( name='rho', nBins=100, xMin=0, xMax=40, xaxisLabel="#rho (GeV)")

#possible selections for the plots
cuts={}
#cuts['All']='1' #just to avoid error
cuts['EBgen']='abs(etaPhotGen)<1.4442'
cuts['EEgen']='abs(etaPhotGen)>1.566 && abs(etaPhotGen)<2.5'
cuts['EB']='abs(etaPhot)<1.4442'
cuts['EE']='abs(etaPhot)>1.566 && abs(etaPhot)<2.5'

efficiencyCuts={}
efficiencyCuts['recoAndID']='ptPhot>0'
#different types of MC (and corresponding selection to differentiate them using ntuple variables"
#mc_types={}
#mc_types['Signal']="isMatchedPhot==1"
#mc_types['Bkg']="isMatchedPhot==0"

#name of the variable to use as weight in MC
weight_var="weight"

#options to draw data and MC plots
draw_opts={}
draw_opts['effStudy']=dict( SetMarkerSize=0.7,SetMarkerStyle=20,SetLineColor=1 )
#draw_opts['mc_Bkg']=dict( SetLineColor=kMagenta,SetLineWidth=2,SetFillColor=kMagenta,SetFillStyle=1001 )
#draw_opts['mc_Signal']=dict( SetLineColor=kCyan,SetLineWidth=2,SetFillColor=kCyan,SetFillStyle=1001 )

histos={}

ROOT.gROOT.SetBatch()
ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetOptStat(0)

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
        
#def plot(variable,plotsDir,additional_cuts="1",pars['additional_text']="",savefmts=[".C",".png",".pdf"]):
def plot(pars,savefmts=[".C",".png",".pdf"]):
    c = TCanvas(pars['variable'],pars['variable'],1000,900)
    customizeCanvas(c)

    for cut in cuts.keys():
        histos[str(pars['variable'])+'_mc_'+str(cut)]=TH1F(str(plotPars[str(pars['variable'])]['name'])+"_mc_"+str(cut),str(plotPars[str(pars['variable'])]['name'])+"_mc_"+str(cut),int(plotPars[str(pars['variable'])]['nBins']),float(plotPars[str(pars['variable'])]['xMin']),float(plotPars[str(pars['variable'])]['xMax']))
        histos[str(pars['variable'])+'_mc_'+str(cut)].Sumw2()
        mc.Project( histos[str(pars['variable'])+'_mc_'+str(cut)].GetName(), str(variables[str(pars['variable'])]), "("+str(cuts[cut])+")*"+weight_var )
        histos[str(pars['variable'])+'_mc_'+str(cut)].Print()
        for numCut in efficiencyCuts.keys():
            histos[str(pars['variable'])+'_mc_'+str(cut)+'_'+str(numCut)]=TH1F(str(plotPars[str(pars['variable'])]['name'])+"_mc_"+str(cut)+'_'+str(numCut),str(plotPars[str(pars['variable'])]['name'])+"_mc_"+str(cut)+'_'+str(numCut),int(plotPars[str(pars['variable'])]['nBins']),float(plotPars[str(pars['variable'])]['xMin']),float(plotPars[str(pars['variable'])]['xMax']))
            histos[str(pars['variable'])+'_mc_'+str(cut)+'_'+str(numCut)].Sumw2()
            mc.Project( histos[str(pars['variable'])+'_mc_'+str(cut)+'_'+str(numCut)].GetName(), str(variables[str(pars['variable'])]), "("+str(cuts[cut])+"&&"+str(efficiencyCuts[numCut])+")*"+weight_var )
            histos[str(pars['variable'])+'_mc_'+str(cut)+'_'+str(numCut)].Print()

            
#            ratio=TGraphAsymmErrors(histos[str(pars['variable'])+'_mc_'+str(cut)+'_'+str(numCut)],histos[str(pars['variable'])+'_mc_'+str(cut)])
#            #histos[str(pars['variable'])+'_mc_'+str(cut)].Draw()
#            histos[str(pars['variable'])+'_mc_'+str(cut)].Draw("")
#            histos[str(pars['variable'])+'_mc_'+str(cut)+'_'+str(numCut)].Draw("SAME")
#
#            c.SetLogy(1)
#            for format in savefmts:
#                c.SaveAs(pars['plotsDir']+"/"+str(pars['variable'])+str(cut)+'_'+str(numCut)+format)
#
#            c.SetLogy(0)
#            ratio.Draw("AP")
#            for format in savefmts:
#                c.SaveAs(pars['plotsDir']+"/"+str(pars['variable'])+str(cut)+'_'+str(numCut)+"_eff"+format)
#


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

#    #Reading data files list
#    lines = [line.strip() for line in open(options.dataFiles)]
#    for line in lines:
#        if line.startswith('#'):
#            continue
#        data.Add(line)

    #Reading mc files list
    lines = [line.strip() for line in open(options.mcFiles)]
    for line in lines:
        if line.startswith('#'):
            continue
        print "Adding file "+str(line) 
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
#        make_option("--dataFiles",
#                    action="store", type="string", dest="dataFiles",
#                    default="data.txt",
#                    help="", metavar=""
#                    ),
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
