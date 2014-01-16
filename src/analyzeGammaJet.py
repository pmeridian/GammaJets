#!/usr/bin/env python

# Chiara: example, how to run it:
#./analyzeGammaJet.py --samplesDat=samples_paolo.dat --cuts=cuts.dat --numberOfCPU=-1

from optparse import OptionParser, make_option
from ROOT import *
import subprocess
import os
import imp
import multiprocessing
from itertools import repeat

#Some global options
xrootd_server="pccmsrm24.cern.ch"
output_dir="/cmsrm/pc24/crovelli/GammaJets/ridottissime"
tmp_dir="/tmp/"+str(os.environ['USER'])

mc_dir="root://pccmsrm24.cern.ch/cmsrm/pc24/crovelli/GammaJets/reduced/redntp.53xv6_CERN.gjetpresel.noCorr.v1"
data_dir="root://pccmsrm24.cern.ch/cmsrm/pc24/crovelli/GammaJets/reduced/redntp.53xv6_data_CERN.gjetpresel.noCorr.v1"

cuts={}
#The cuts will be passed as parameters
samples={}

def main(options,args):

    print "+++++++++++++++++++++++++++++++++++++++++++"
    print "Processing with options: "
    print options

    
    gROOT.ProcessLine(".L GammaJetAnalysis.C++")

    #Reading cuts dat
    filename  = options.cutsDat
    handle = open(filename, 'r')
    cfo = imp.load_source("pycfg", filename, handle)
    cuts = cfo.cuts
    handle.close()

    print "Cuts: "
    print cuts
    print "+++++++++++++++++++++++++++++++++++++++++++"

    #Reading samples dat
    filename  = options.samplesDat
    handle = open(filename, 'r')
    cfo = imp.load_source("pycfg", filename, handle)
    samples = cfo.samples
    handle.close()

    #print samples
    
    #defining a number of workers as much as the number of cpus in the machine
    ncpu=multiprocessing.cpu_count()

    if (options.numberOfCPU>0):
        ncpu=options.numberOfCPU
        
    pool = multiprocessing.Pool(processes=ncpu)

    #run all the samples in parallel
    pool.map( analyzeSample, zip(samples.keys(),repeat(cuts),repeat(samples)) )


def analyzeSample( (sample,mycuts,samples) ):
#    print sample,mycuts,samples
    #the real worker code
    print "Analyzing sample "+ sample + ": " + str(samples[sample])
    f=TFile.Open(samples[sample][4]+"/"+samples[sample][1])
    a=f.Get("AnaTree")
    a_h1=f.Get("ptphotgen1")
    #        a.Print()

    analyzer = GammaJetAnalysis(a)
    analyzer.sampleIndex=samples[sample][0]
    analyzer.sampleName=str(sample)
    analyzer.sampleSize=a_h1.Integral()
    analyzer.normLumi=mycuts['normLumi']
    analyzer.xsec=samples[sample][2]
    analyzer.kfac=samples[sample][3]
    analyzer.hltcut=mycuts['hltcut']
    analyzer.hltiso=mycuts['hltiso']
    analyzer.mvaIDWP=mycuts['mvaIDWP']
    analyzer.mvaWeights_EB=mycuts['mvaWeights_EB']
    analyzer.mvaWeights_EE=mycuts['mvaWeights_EE']
    analyzer.selectionType=mycuts['selectionType']
    outfileName=str(sample)+"_hltcut"+str(analyzer.hltcut)+"_hltiso"+str(analyzer.hltiso)+"_mvaWP"+str(analyzer.mvaIDWP)+".root"
    analyzer.outputFile=tmp_dir+"/"+outfileName
    #to be linked to the hlt cut in the future
    analyzer.ptphot1_mincut=mycuts['ptMin']
    analyzer.ptphot1_maxcut=mycuts['ptMax']
    analyzer.Loop()
    
    #Copying file towards final destination
    rm_command="xrd "+xrootd_server+" rm "+output_dir+"/"+outfileName
    # subprocess.call(rm_command,shell=True)    # chiara: questo e' temporaneo  
    #copy_command="xrdcp "+tmp_dir+"/"+outfileName+" root://"+xrootd_server+"//"+output_dir+"/"+outfileName
    copy_command="mv "+tmp_dir+"/"+outfileName+" "+output_dir+"/"+outfileName    # chiara: questo e' temporaneo 
    subprocess.check_call(copy_command,shell=True)
    print "Copied file into "+output_dir+"/"+outfileName


if __name__ == "__main__":
    parser = OptionParser(option_list=[
        make_option("--samplesDat",
                    action="store", type="string", dest="samplesDat",
                    default="samples.dat",
                    help="", metavar=""
                    ),
        make_option("--cutsDat",
                    action="store", type="string", dest="cutsDat",
                    default="cuts.dat",
                    help="", metavar=""
                    ),
        make_option("--numberOfCPU",
                    action="store", type="int", dest="numberOfCPU",
                    default=-1,
                    help="", metavar=""
                    ),
        ])
    
    (options, args) = parser.parse_args()
    
    main( options, args) 
