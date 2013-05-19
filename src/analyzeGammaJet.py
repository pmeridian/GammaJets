#!/usr/bin/env python

from optparse import OptionParser, make_option
from ROOT import *
import subprocess
import os
import multiprocessing

#Some global options
xrootd_server="pccmsrm27.cern.ch"
output_dir="/cms/local/meridian/GammaJets/output"
tmp_dir="/tmp/"+str(os.environ['USER'])

mc_dir="root://pccmsrm27.cern.ch///cms/local/crovelli/GammaJets/reduced/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged2/"
data_dir="root://pccmsrm27.cern.ch///cms/local/crovelli/GammaJets/reduced/redntp.53xv2_data.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged2"

samples={}
             #  name                     #index        #filename                                     #xsec    #kfac         #directory
samples["QCDEM_Pt_20_30_8TeV_pythia6"]=[1,"redntp_QCD_Pt_20_30_EMEnriched_TuneZ2star_8TeV_pythia6.root",288600000 * 0.0101 ,1., mc_dir]
samples["QCDEM_Pt_30_80_8TeV_pythia6"]=[2,"redntp_QCD_Pt_30_80_EMEnriched_TuneZ2star_8TeV_pythia6.root",74330000 * 0.0621 ,1. , mc_dir]
samples["QCDEM_Pt_80_170_8TeV_pythia6"]=[3,"redntp_QCD_Pt_80_170_EMEnriched_TuneZ2star_8TeV_pythia6.root",1191000 * 0.1539 ,1., mc_dir]
samples["QCDEM_Pt_170_250_8TeV_pythia6"]=[4,"redntp_QCD_Pt_170_250_EMEnriched_TuneZ2star_8TeV_pythia6.root",30990 * 0.148 ,1. , mc_dir]
samples["QCDEM_Pt_250_350_8TeV_pythia6"]=[5,"redntp_QCD_Pt_250_350_EMEnriched_TuneZ2star_8TeV_pythia6.root",4250 * 0.131 ,1. , mc_dir]
samples["QCDEM_Pt_350_8TeV_pythia6"]=[6,"redntp_QCD_Pt_350_EMEnriched_TuneZ2star_8TeV_pythia6.root",810 * 0.11 ,1. , mc_dir]

#samples["G_Pt-0to15_8TeV_pythia6"]=[6,"redntp_G_Pt-0to15_TuneZ2star_8TeV_pythia6.root",90601456 ,1., mc_dir]
samples["G_Pt-15to30_8TeV_pythia6"]=[7,"redntp_G_Pt-15to30_TuneZ2star_8TeV_pythia6.root",200061.7 ,1. ,mc_dir]
samples["G_Pt-30to50_8TeV_pythia6"]=[8,"redntp_G_Pt-30to50_TuneZ2star_8TeV_pythia6.root",19931.62 ,1. ,mc_dir]
samples["G_Pt-50to80_8TeV_pythia6"]=[9,"redntp_G_Pt-50to80_TuneZ2star_8TeV_pythia6.root", 3322.309, 1. ,mc_dir]
samples["G_Pt-80to120_8TeV_pythia6"]=[10,"redntp_G_Pt-80to120_TuneZ2star_8TeV_pythia6.root",558.2865 , 1. ,mc_dir]
samples["G_Pt-120to170_8TeV_pythia6"]=[11,"redntp_G_Pt-120to170_TuneZ2star_8TeV_pythia6.root",108.0068,1. ,mc_dir]
samples["G_Pt-170to300_8TeV_pythia6"]=[12,"redntp_G_Pt-170to300_TuneZ2star_8TeV_pythia6.root",30.12207,1. ,mc_dir]
samples["G_Pt-300to470_8TeV_pythia6"]=[13,"redntp_G_Pt-300to470_TuneZ2star_8TeV_pythia6.root",0.2119244,1. ,mc_dir]
samples["G_Pt-470to800_8TeV_pythia6"]=[14,"redntp_G_Pt-470to800_TuneZ2star_8TeV_pythia6.root",0.2119244,1. ,mc_dir]
samples["G_Pt-800to1400_8TeV_pythia6"]=[15,"redntp_G_Pt-800to1400_TuneZ2star_8TeV_pythia6.root",0.007077847,1. ,mc_dir]
samples["G_Pt-1400to1800_8TeV_pythia6"]=[16,"redntp_G_Pt-1400to1800_TuneZ2star_8TeV_pythia6.root",4.510327e-5,1. ,mc_dir]

#data sampleIndex=0 for data
samples["Photon-Run2012A-recover-06Aug2012"]=[0, "redntp_Photon-Run2012A-recover-06Aug2012-v1.root" , 1, 1 ,data_dir]
samples["Photon_Run2012A-13Jul2012"] = [0,"redntp_Photon_Run2012A-13Jul2012-v1.root",1,1,data_dir]
samples["Photon_Run2012B-13Jul2012"] = [0,"redntp_SinglePhoton_Run2012B-13Jul2012-v1.root",1,1,data_dir]
samples["Photon_Run2012C-24Aug2012"] = [0,"redntp_SinglePhoton_Run2012C-24Aug2012-v1.root",1,1,data_dir]
samples["Photon_Run2012C-EcalRecover_11Dec2012"] = [0,"redntp_SinglePhoton_Run2012C-EcalRecover_11Dec2012-v1.root",1,1,data_dir]
samples["Photon_Run2012C-PromptReco-v2"] = [0,"redntp_SinglePhoton_Run2012C-PromptReco-v2.root",1,1,data_dir]
samples["Photon_Run2012D-PromptReco-v1"] = [0, "redntp_SinglePhoton_Run2012D-PromptReco-v1.root",1,1,data_dir]

#The cuts will be passed as parameters
cuts={}

def analyzeSample(sample):
    #the real worker code
    print "Analyzing sample "+sample
    f=TFile.Open(samples[sample][4]+"/"+samples[sample][1])
    a=f.Get("AnaTree")
    a_h1=f.Get("ptphotgen1")
    #        a.Print()

    analyzer = GammaJetAnalysis(a)
    analyzer.sampleIndex=samples[sample][0]
    analyzer.sampleName=str(sample)
    analyzer.sampleSize=a_h1.Integral()
    analyzer.normLumi=cuts['normLumi']
    analyzer.xsec=samples[sample][2]
    analyzer.kfac=samples[sample][3]
    analyzer.hltcut=cuts['hltcut']
    analyzer.mvaIDWP=cuts['mvaIDWP']
    outfileName=str(sample)+"_hltcut"+str(analyzer.hltcut)+"_mvaWP"+str(analyzer.mvaIDWP)+".root"
    analyzer.outputFile=tmp_dir+"/"+outfileName
    #to be linked to the hlt cut in the future
    analyzer.ptphot1_mincut=cuts['ptMin']
    analyzer.ptphot1_maxcut=cuts['ptMax']
    analyzer.Loop()
    
    #Copying file towards final destination
    rm_command="xrd "+xrootd_server+" rm "+output_dir+"/"+outfileName
    subprocess.call(rm_command,shell=True)
    copy_command="xrdcp "+tmp_dir+"/"+outfileName+" root://"+xrootd_server+"//"+output_dir+"/"+outfileName 
    subprocess.check_call(copy_command,shell=True)
    print "Copied file into "+output_dir+"/"+outfileName


def main(options,args):

    print "+++++++++++++++++++++++++++++++++++++++++++"
    print "Processing with options: "
    print options
    print "+++++++++++++++++++++++++++++++++++++++++++"
    
    gROOT.ProcessLine(".L GammaJetAnalysis.C++")

    #getting cuts from command line
    cuts['normLumi']=options.normLumi
    cuts['hltcut']=options.hltcut
    cuts['mvaIDWP']=options.mvaIDWP
    cuts['ptMin']=options.ptMin
    cuts['ptMax']=options.ptMax

    print cuts
    
    #defining a number of workers as much as the number of cpus in the machine
    ncpu=multiprocessing.cpu_count()

    if (options.numberOfCPU>0):
        ncpu=options.numberOfCPU
        
    pool = multiprocessing.Pool(processes=ncpu)

    #run all the samples in parallel
    pool.map(analyzeSample, samples.keys())

if __name__ == "__main__":
    parser = OptionParser(option_list=[
        make_option("--normLumi",
                    action="store", type="float", dest="normLumi",
                    default=1000,
                    help="", metavar=""
                    ),
        make_option("--hltCut",
                    action="store", type="int", dest="hltcut",
                    default=30,
                    help="", metavar=""
                    ),
        make_option("--ptMax",
                    action="store", type="int", dest="ptMax",
                    default=999999.,
                    help="", metavar=""
                    ),
        make_option("--ptMin",
                    action="store", type="int", dest="ptMin",
                    default=-999999.,
                    help="", metavar=""
                    ),
        make_option("--mvaIDWP",
                    action="store", type="int", dest="mvaIDWP",
                    default="2",
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
