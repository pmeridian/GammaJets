
import FWCore.ParameterSet.Config as cms

import sys
TYPE = sys.argv[2]
FUNC = sys.argv[3]

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

if TYPE  == 'MC'    : INPUTFILE = "outFile.root"

process.TnP_MuonID = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(True),

    InputFileNames = cms.vstring(INPUTFILE),
    InputTreeName = cms.string("myTree"),    
    InputDirectoryName = cms.string("myTaPDir"), 
    OutputFileName = cms.string("REPLACE_ME"),
                                    
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "60", "120", "GeV/c^{2}"),   

        probe_abseta = cms.vstring("Probe |#eta|", "0.", "2.5", ""),
        probe_eta = cms.vstring("Probe #eta", "-2.5", "2.5", ""),
        probe_pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV"),        
        probe_phi = cms.vstring("Probe #phi", "-3.0", "3.0", "rad"),

        numvtx = cms.vstring("Number of PV (DA)","0","100",""),

        puW30 = cms.vstring("weight for HLT30","0","10",""),
        puW50 = cms.vstring("weight for HLT50","0","10",""),
        puW75 = cms.vstring("weight for HLT75","0","10",""),
        puW90 = cms.vstring("weight for HLT90","0","10",""),
    ),

    Categories = cms.PSet(

        ## Cuts Sequence
        okMediumElePtEta = cms.vstring("okMediumElePtEta","dummy[pass=1,fail=0]"),  
        okMediumEleID = cms.vstring("okMediumEleID","dummy[pass=1,fail=0]"),  

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
                    "signalFractionInPassing[0.9]"
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
        
    ),

    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(21),

    WeightVariable = cms.string("puW30"),          

    Efficiencies = cms.PSet(), # will be filled later
)

ONE_BIN = cms.PSet(

    probe_pt  = cms.vdouble( 20, 25, 50, 200), 
    probe_abseta = cms.vdouble( 0, 1.4442, 2.5), 
)

OUTPUTFILE = "GJets_%s_TnP_Z_WEIGHTED.root" % (FUNC)
process.TnP_MuonID.OutputFileName = cms.string(OUTPUTFILE)

process.TnP_MuonID.Efficiencies.PASSING_all = cms.PSet(

    #EfficiencyCategoryAndState = cms.vstring("okMediumElePtEta","pass"),    # mettendone tanti si fa l'AND
    EfficiencyCategoryAndState = cms.vstring("okMediumEleID","pass"),        # mettendone tanti si fa l'AND

    UnbinnedVariables = cms.vstring("mass","puW30"),
    BinnedVariables = ONE_BIN.clone(
    ),
    BinToPDFmap = cms.vstring(FUNC),

    )


process.p = cms.Path(process.TnP_MuonID)
