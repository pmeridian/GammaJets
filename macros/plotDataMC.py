#!/usr/bin/env python

from optparse import OptionParser, make_option
from ROOT import *
import subprocess
import os

treeName="finalTree"
data = TChain(treeName)
mc = TChain(treeName)

text="CMS Preliminary #sqrt{s}=8 TeV"

variables={}
variables['ptPhot']='ptPhot'

plotPars={}
plotPars['ptPhot']=dict( name='ptPhot', nBins=60, xMin=0., xMax=300., xaxisLabel="#gamma p_{T} (GeV/c)")

cuts={}
cuts['All']='1' #just to avoid error
cuts['EB']='abs(etaPhot)<1.4442'
cuts['EE']='abs(etaPhot)>1.566 && abs(etaPhot)<2.5'

mc_types={}
mc_types['Signal']="isMatchedPhot==1"
mc_types['Bkg']="isMatchedPhot==0"

weight_var="weight"

draw_opts={}
draw_opts['data']=dict( SetMarkerSize=0.7,SetMarkerStyle=20,SetLineColor=1 )
draw_opts['mc_Bkg']=dict( SetLineColor=kMagenta,SetLineWidth=2,SetFillColor=kMagenta,SetFillStyle=1001 )
draw_opts['mc_Signal']=dict( SetLineColor=kCyan,SetLineWidth=2,SetFillColor=kCyan,SetFillStyle=1001 )

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
    c.SetLeftMargin(0.1)
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
                
def plot(variable,plotsDir,additional_text="",savefmts=[".C",".png",".pdf"]):
    c = TCanvas(variable,variable,1000,900)
    customizeCanvas(c)
    
    for cut in cuts.keys():
        histos[str(variable)+'_data_'+str(cut)]=TH1F(str(plotPars[str(variable)]['name'])+"_data_"+str(cut),str(plotPars[str(variable)]['name'])+"_data_"+str(cut),int(plotPars[str(variable)]['nBins']),float(plotPars[str(variable)]['xMin']),float(plotPars[str(variable)]['xMax']))
        histos[str(variable)+'_data_'+str(cut)].Sumw2()
        for type in mc_types.keys():
            histos[str(variable)+'_mc_'+type+"_"+str(cut)]=TH1F(str(plotPars[str(variable)]['name'])+"_mc_"+type+"_"+str(cut),str(plotPars[str(variable)]['name'])+"_mc_"+type+"_"+str(cut),plotPars[str(variable)]['nBins'],plotPars[str(variable)]['xMin'],plotPars[str(variable)]['xMax'])
            histos[str(variable)+'_mc_'+type+"_"+str(cut)].Sumw2()
        #Filling histos
        data.Project( histos[str(variable)+'_data_'+str(cut)].GetName(), str(variables[str(variable)]), str(cuts[cut]))
        histos[str(variable)+'_data_'+str(cut)].Print()
        for aopt in draw_opts['data'].keys():
            a=histos[str(variable)+'_data_'+str(cut)]
            eval('a.'+str(aopt)+'('+str(draw_opts['data'][aopt])+')')
            
        for mc_type in mc_types.keys():
            mc.Project( histos[str(variable)+'_mc_'+mc_type+"_"+str(cut)].GetName(), str(variables[str(variable)]), "("+str(cuts[cut])+"&&"+str(mc_types[mc_type])+")*"+weight_var )
            histos[str(variable)+'_mc_'+mc_type+"_"+str(cut)].Print()
            for aopt in draw_opts['mc_'+mc_type].keys():
                a=histos[str(variable)+'_mc_'+mc_type+"_"+str(cut)]
                eval('a.'+str(aopt)+'('+str(draw_opts['mc_'+mc_type][aopt])+')')

        c.cd(1)
        histos[str(variable)+'_data_'+str(cut)].Draw("PE")
        histos[str(variable)+'_data_'+str(cut)].SetMaximum(histos[str(variable)+'_data_'+str(cut)].GetMaximum()*1.4)
        histos[str(variable)+'_data_'+str(cut)].SetMinimum(0)
        histos[str(variable)+'_data_'+str(cut)].GetXaxis().SetTitle(str(plotPars[str(variable)]['xaxisLabel']))

        stack=THStack()
        mc_types_keys=mc_types.keys()
        mc_types_keys.sort()
        for mc_type in range(len(mc_types_keys)):
            stack.Add(histos[str(variable)+'_mc_'+mc_types_keys[mc_type]+"_"+str(cut)])
        stack.Draw("HSAME")
        histos[str(variable)+'_data_'+str(cut)].Draw("PESAME")

        a=TLegend(0.63,0.68,0.88,0.88)
        a.SetBorderSize(0)
        a.SetFillColor(0)
        a.SetTextSize(0.038)
        a.SetHeader(str(cut))
        a.AddEntry( histos[str(variable)+'_data_'+str(cut)],"Data","PL" )
        for mc_type in range(len(mc_types_keys)):
             a.AddEntry( histos[str(variable)+'_mc_'+mc_types_keys[mc_type]+"_"+str(cut)], mc_types_keys[mc_type], "F" )
        a.Draw()

        tex_m=TLatex();
        tex_m.SetNDC();
        tex_m.SetTextAlign(12);
        tex_m.SetTextSize(0.037);
        tex_m.SetLineWidth(2);
        tex_m.DrawLatex(0.25,0.94,text);

        if (additional_text != ""):
            tex_m.SetTextSize(0.045);
            tex_m.DrawLatex(0.63,0.63,additional_text);

                        
        c.SetLogy(0)
        for format in savefmts:
            c.SaveAs(plotsDir+"/"+str(variable)+str(cut)+format)
        c.Clear()
        pads=splitCanvas(c)
        pads[0].cd()
        gPad.SetLogy(1)
        histos[str(variable)+'_data_'+str(cut)].Draw("PE")
        histos[str(variable)+'_data_'+str(cut)].SetMaximum(histos[str(variable)+'_data_'+str(cut)].GetMaximum()*1.4)
        histos[str(variable)+'_data_'+str(cut)].SetMinimum(0)
        histos[str(variable)+'_data_'+str(cut)].GetXaxis().SetTitle(str(plotPars[str(variable)]['xaxisLabel']))
        stack.Draw("HSAME")
        histos[str(variable)+'_data_'+str(cut)].Draw("PESAME")

        a=TLegend(0.63,0.68,0.88,0.88)
        a.SetBorderSize(0)
        a.SetFillColor(0)
        a.SetTextSize(0.038)
        a.SetHeader(str(cut))
        a.AddEntry( histos[str(variable)+'_data_'+str(cut)],"Data","PL" )
        for mc_type in range(len(mc_types_keys)):
             a.AddEntry( histos[str(variable)+'_mc_'+mc_types_keys[mc_type]+"_"+str(cut)], mc_types_keys[mc_type], "F" )
        a.Draw()

        tex_m=TLatex();
        tex_m.SetNDC();
        tex_m.SetTextAlign(12);
        tex_m.SetTextSize(0.037);
        tex_m.SetLineWidth(2);
        tex_m.DrawLatex(0.25,0.94,text);

        if (additional_text != ""):
            tex_m.SetTextSize(0.045);
            tex_m.DrawLatex(0.63,0.63,additional_text);

        histos[str(variable)+'_data_'+str(cut)].SetMaximum(histos[str(variable)+'_data_'+str(cut)].GetMaximum()*4.)
        histos[str(variable)+'_data_'+str(cut)].SetMinimum(0.1)
        pads[1].cd()
        pads[1].SetBottomMargin(0.2)
        pads[1].SetGridy(1)
        ratio=histos[str(variable)+'_data_'+str(cut)].Clone("ratio")
        for mc_type in range(len(mc_types_keys)):
            if (mc_type==0):
                sum=histos[str(variable)+'_mc_'+mc_types_keys[mc_type]+"_"+str(cut)].Clone("sum")
            else:
                sum.Add(histos[str(variable)+'_mc_'+mc_types_keys[mc_type]+"_"+str(cut)])
        ratio.Divide(sum)
        ratio.SetMaximum(3)
        ratio.SetMinimum(0.2)
        ratio.GetYaxis().SetLabelSize(0.07)
        ratio.GetXaxis().SetLabelSize(0.07)
        ratio.GetXaxis().SetTitleSize(0.08)
        ratio.GetXaxis().SetTitleOffset(1.)
        ratio.Draw("PE")
        aL=TLine(float(plotPars[str(variable)]['xMin']),1,float(plotPars[str(variable)]['xMax']),1)
        aL.SetLineColor(4)
        aL.SetLineWidth(2)
        aL.Draw()
        ratio.Draw("PESAME")
        for format in savefmts:
            c.SaveAs(plotsDir+"/"+str(variable)+str(cut)+"_log"+format)

def main(options,args):

    print "+++++++++++++++++++++++++++++++++++++++++++"
    print "Processing with options: "
    print options
    print "+++++++++++++++++++++++++++++++++++++++++++"

    plotsDir=options.plotsDir
    additionalText=options.additionalText
    
    try:
        os.mkdir(plotsDir)
    except:
        pass
    
    lines = [line.strip() for line in open(options.dataFiles)]
    for line in lines:
        if line.startswith('#'):
            continue
        data.Add(line)

    lines = [line.strip() for line in open(options.mcFiles)]
    for line in lines:
        if line.startswith('#'):
            continue
        mc.Add(line)

    for variable in variables.keys():
        plot(variable,plotsDir,additionalText)

    
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
        make_option("--numberOfCPU",
                    action="store", type="int", dest="numberOfCPU",
                    default=-1,
                    help="", metavar=""
                    )
        ])
    
    (options, args) = parser.parse_args()
    
    main( options, args) 
