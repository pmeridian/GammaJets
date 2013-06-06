import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing

# Example: cmsRun fitElectronID-pt-eta_Functions_mixedBins.py fileList=reducedTnP_data.list r9Weight=0 puWeight=0 func=gpOne sampleName=data efficiencyType=okMVA_005
# In teh line below 'analysis' is an instance of VarParsing object

options = VarParsing ('analysis')

options.register ('fileList',
                     '',
                     VarParsing.multiplicity.singleton,
                     VarParsing.varType.string,
                     "List of files to be processed")

options.register ('r9Weight',
                  0,
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.int,
                  "do R9 reweighting")

options.register ('puWeight',
                  0,
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.int,
                  "do PU reweighting")

options.register ('func',
                  'gpOne',
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "model for fitting")

options.register ('sampleName',
                  '',
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "name of the data (for the output file)")

options.register ('efficiencyType',
                  '',
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "which efficiency do you want?")

options.register ('ptBins',
                  '20, 30, 40, 50, 200',
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "ptBins")

options.register ('etaBins',
                  ' 0, 1.4442, 2.5',
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "ptBins")

options.parseArguments()
  
#import sys
#TYPE = sys.argv[2]
#FUNC = sys.argv[3]

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

r9weightExpression='1'
if (options.r9Weight==1):
    r9weightExpression='((probe_abseta<1.479)*r9WeightEB + (probe_abseta>1.479)*r9WeightEE)'

puWeightExpression='1'
if (options.puWeight==1):
    puWeightExpression='puW'



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

INPUTFILE = []
for file in [ line.strip() for line in open(options.fileList,'r') if not line.strip().startswith('#') ]:
    print file
    INPUTFILE.append(file)

#if TYPE  == 'MC'    : INPUTFILE = "root://pccmsrm27.cern.ch///cms/local/meridian/GammaJets/TandP/DYJetsToLL_M-50_madgraph_tagTight_HLT.root"
#if TYPE  == 'DATA'  : INPUTFILE = "/afs/cern.ch/user/c/crovelli/myWorkspace/gammaJets/CMSSW_5_3_6/src/GammaJets/src/TagAndProbeZ/outFile_DoubleElectron_tagTight.root"

process.TnP_MuonID = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    NumCPU = cms.uint32(4),
    SaveWorkspace = cms.bool(True),

    InputFileNames = cms.vstring(INPUTFILE),
    InputTreeName = cms.string("myTree"),    
    InputDirectoryName = cms.string("myTaPDir"), 
    OutputFileName = cms.string("REPLACE_ME"),
                                    
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "62", "118", "GeV/c^{2}"),   

        probe_abseta = cms.vstring("Probe |#eta|", "0.", "2.5", ""),
        probe_eta = cms.vstring("Probe #eta", "-2.5", "2.5", ""),
        probe_pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV"),        
        probe_phi = cms.vstring("Probe #phi", "-3.0", "3.0", "rad"),
        probe_r9 = cms.vstring("Probe r9", "0.", "1.2", ""),
        numvtx = cms.vstring("Number of PV (DA)","0","100",""),
        puW = cms.vstring("PU weight","0","10",""),
        r9WeightEB = cms.vstring("r9 weight EB ","0","20",""),
        r9WeightEE = cms.vstring("r9 weight EE ","0","20",""),
    ),

    Expressions = cms.PSet(
        weight = cms.vstring("weight", puWeightExpression+'*'+r9weightExpression , "puW", "probe_abseta", "r9WeightEB", "r9WeightEE"),   
    ),

    Categories = cms.PSet(

        ## Cuts Sequence
        okLooseEleID = cms.vstring("okLooseEleID","dummy[pass=1,fail=0]"),
        okMediumEleID = cms.vstring("okMediumEleID","dummy[pass=1,fail=0]"),  
        okTightEleID = cms.vstring("okTightEleID","dummy[pass=1,fail=0]"),  
    
    okMVA_005 = cms.vstring("okMVA_005","dummy[pass=1,fail=0]"),
    okMVA_01 = cms.vstring("okMVA_01","dummy[pass=1,fail=0]"),
    okMVA_02 = cms.vstring("okMVA_02","dummy[pass=1,fail=0]"),

        # chiara: questo sarebbe da mettere
        # tag_HLT_HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC8_Mass30_TagLeg = cms.vstring("legTag1","dummy[pass=1,fail=0]"),
    ),

    PDFs = cms.PSet(
         
        CBVoigtianPlusChebychevBackground = cms.vstring(
            "mean[90,80,100]",
            "sigma[3,1,20]",
            "CBShape::cbs(mass, mean, sigma, alpha[3., 0.5, 5.], n[1, 0., 100.])",
            "Voigtian::vs(mass, mean, width[2.495], sigma)",
            "SUM::signal(f1[0.6, 0.4, 0.8]*cbs,f2[0.3, 0.2, 0.8]*vs)",
            "Chebychev::backgroundPass(mass, {cPass[0,-0.5,0.5], cPass2[0,-0.5,0.5]})",
            "Chebychev::backgroundFail(mass, {cFail[0,-0.5,0.5], cFail2[0,-0.5,0.5]})",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),                        

        CBVoigtianPlusExponentialBackground = cms.vstring(
                "mean[90,80,100]",
                "sigma[3,1,20]",
                "CBShape::cbs(mass, mean, sigma, alpha[3., 0.5, 5.], n[1, 0., 100.])",
                "Voigtian::vs(mass, mean, width[2.495], sigma)",
                "SUM::signal(f1[0.6, 0.4, 0.8]*cbs,f2[0.3, 0.2, 0.8]*vs)",
                "Exponential::backgroundPass(mass, lp[0,-5,5])",
                "Exponential::backgroundFail(mass, lf[0,-5,5])",
                "efficiency[0.9,0,1]",
                "signalFractionInPassing[0.9]"
        ),
        

        gaussPlusLinear = cms.vstring(
                #"EXPR::signal('(@1<@0)*exp(-(@0-@1)*(@0-@1)/(@2*@2 + @3*(@0-@1)*(@0-@1))) + (@1>=@0)*exp(-(@0-@1)*(@0-@1)/(@4*@4 + @5*(@0-@1)*(@0-@1)))',mean[88.5, 80.0, 91.25],mass, sigmaL[2.3, 0.5, 10.0],alphaL[0.23],sigmaR[2.0, 0.5, 3.0],alphaR[0.1,0,3])",

                "EXPR::signal('(@1<@0)*exp(-(@0-@1)*(@0-@1)/(@2*@2 + @3*(@0-@1)*(@0-@1))) + (@1>=@0)*exp(-(@0-@1)*(@0-@1)/(@4*@4 + @5*(@0-@1)*(@0-@1)))',mean[84.5, 83.0, 91.25],mass, sigmaL[5.0, 1.0, 12.0],alphaL[0.2,0.15,0.40],sigmaR[3.0, 2.0, 7.0],alphaR[0.1,0.1,2.0])",

                #"RooVoigtian::signal(mass, mean[91.2, 80.0, 100.0],gamma[10,0,100], sigma[2.3, 0.5, 10.0])",

                "RooExponential::backgroundPass(mass, cPass[0,-10,10])",
                "RooExponential::backgroundFail(mass, cFail[0,-10,10])",

                ## "RooPolynomial::backgroundPass(mass, {cPass1[0,-100,100],cPass2[0,-100,100]},2)",
                ## "RooPolynomial::backgroundFail(mass, {cFail1[0,-100,100],cFail2[0,-100,100]},2)",
                "efficiency[0.5,0,1]",
                "signalFractionInPassing[0.9]"
                ),

        #gaussPlusLinear = cms.vstring(
        #        "EXPR::signal('(@1<@0)*exp(-(@0-@1)*(@0-@1)/(@2*@2 + @3*(@0-@1)*(@0-@1))) + (@1>=@0)*exp(-(@0-@1)*(@0-@1)/(@4*@4 + @5*(@0-@1)*(@0-@1)))',mean[91.2, 80.0, 100.0],mass, sigmaL[2.3, 0.5, 10.0],alphaL[0.23],sigmaR[2.3, 0.5, 10.0],alphaR[0.2,0,3])",
                
                #"RooVoigtian::signal(mass, mean[91.2, 80.0, 100.0],gamma[10,0,100], sigma[2.3, 0.5, 10.0])",
       #         "RooExponential::backgroundPass(mass, cPass[0,-10,10])",
       #         "RooExponential::backgroundFail(mass, cFail[0,-10,10])",
                ## "RooPolynomial::backgroundPass(mass, {cPass1[0,-100,100],cPass2[0,-100,100]},2)",
                ##             "RooPolynomial::backgroundFail(mass, {cFail1[0,-100,100],cFail2[0,-100,100]},2)",
       #         "efficiency[0.5,0,1]",
       #         "signalFractionInPassing[0.9]"
       #         ),

        vpvPlusExpo = cms.vstring(
                "Voigtian::signal1(mass, mean1[90,80,100], width[2.495], sigma1[2,1,3])",
                "Voigtian::signal2(mass, mean2[90,80,100], width,        sigma2[4,2,10])",
                "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
                "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
                "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
                "efficiency[0.9,0,1]",
                "signalFractionInPassing[0.9]"
                ),

        gpOne = cms.vstring(
                    "Voigtian::signal1Pass(mass, mean1Pass[90,80,100], width[2.495], sigma1Pass[2,1,3])",
                    "Voigtian::signal2Pass(mass, mean2Pass[90,80,100], width,        sigma2Pass[4,2,10])",
                    "SUM::signalPass(vFracPass[0.8,0,1]*signal1Pass, signal2Pass)",
                    "Voigtian::signal1Fail(mass, mean1Fail[90,80,100], width[2.495], sigma1Fail[2,1,3])",
                    "Voigtian::signal2Fail(mass, mean2Fail[90,80,100], width, sigma2Fail[4,2,10])",
                    "SUM::signalFail(vFracFail[0.8,0,1]*signal1Fail, signal2Fail)",
                    "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
                    "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
                    "efficiency[0.9,0,1]",
                    "signalFractionInPassing[0.9,0,1]"
                    ),

        gpTwo = cms.vstring(
                    "Voigtian::signal1Pass(mass, mean1[90,80,100],     width[2.495], sigma1[2,1,3])",
                    "Voigtian::signal2Pass(mass, mean2Pass[90,80,100], width,        sigma2Pass[4,2,10])",
                    "SUM::signalPass(vFracPass[0.8,0,1]*signal1Pass, signal2Pass)",
                    "Voigtian::signal2Fail(mass, mean2Fail[90,80,100], width,        sigma2Fail[4,2,10])",
                    "SUM::signalFail(vFracFail[0.8,0,1]*signal1Pass, signal2Fail)",
                    "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
                    "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
                    "efficiency[0.9,0,1]",
                    "signalFractionInPassing[0.9]"
                    ),
        
        cruijffPlusExpo = cms.vstring(
                    "EXPR::signal('(@1<@0)*exp(-(@0-@1)*(@0-@1)/(@2*@2 + @3*(@0-@1)*(@0-@1))) + (@1>=@0)*exp(-(@0-@1)*(@0-@1)/(@4*@4 + @5*(@0-@1)*(@0-@1)))',mean[91.2, 80.0, 100.0],mass, sigmaL[2.3, 0.5, 10.0],alphaL[0.23],sigmaR[2.3, 0.5, 10.0],alphaR[0.2,0,3])",
                    "RooExponential::backgroundPass(mass, cPass[0,-10,10])",
                    "RooExponential::backgroundFail(mass, cFail[0,-10,10])",
                    "efficiency[0.5,0,1]",
                    "signalFractionInPassing[0.9]"
                    ),
    ),

    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(40),

    WeightVariable = cms.string("weight"),          

    Efficiencies = cms.PSet(), # will be filled later
)

ptB=[ float(i) for i in options.ptBins.split(',') ]
etaB=[ float(i) for i in options.etaBins.split(',') ]
ONE_BIN = cms.PSet(
    probe_pt  = cms.vdouble(  ptB ), 
    probe_abseta = cms.vdouble( etaB ),

#    probe_pt  = cms.vdouble( 20, 30 ), 
#    probe_abseta = cms.vdouble( 0, 1.4442 ),
)

OUTPUTFILE = "%s_%s_%s_TnP_Z%s%s.root" % (options.sampleName, options.efficiencyType, options.func, '_R9WEIGHT' if options.r9Weight else '', '_PUWEIGHT' if options.puWeight else '')

process.TnP_MuonID.OutputFileName = cms.string(OUTPUTFILE)

process.TnP_MuonID.Efficiencies.PASSING_all = cms.PSet(

    #EfficiencyCategoryAndState = cms.vstring("okMediumEleID","pass"),        # mettendone tanti si fa l'AND
    EfficiencyCategoryAndState = cms.vstring( options.efficiencyType,"pass" ),
    #EfficiencyCategoryAndState = cms.vstring("okMVA_01","pass"),
    #EfficiencyCategoryAndState = cms.vstring("okMVA_02","pass"),
    
    UnbinnedVariables = cms.vstring("mass","puW"),
    BinnedVariables = ONE_BIN.clone(
    ),
    BinToPDFmap = cms.vstring(options.func)
)

process.p = cms.Path(process.TnP_MuonID)
