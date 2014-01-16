#!/bin/tcsh
    
set data_json_   = "`pwd`/../../scripts/jsonFiles/Cert_190456-208686_8TeV_22Jan2013ReReco_Collisions12_JSON.txt"

set puweight_53x       = "`pwd`/../../scripts/puFiles/PileupWeights_allHLT.root"
set puweight_53x_HLT30 = "`pwd`/../../scripts/puFiles/PileupWeights_HLT30_CaloIdVL.root"
set puweight_53x_HLT50 = "`pwd`/../../scripts/puFiles/PileupWeights_HLT50_CaloIdVL.root"
set puweight_53x_HLT75 = "`pwd`/../../scripts/puFiles/PileupWeights_HLT75_CaloIdVL.root"
set puweight_53x_HLT90 = "`pwd`/../../scripts/puFiles/PileupWeights_HLT90_CaloIdVL.root"
set puweight_53x_HLT135 = "`pwd`/../../scripts/puFiles/PileupWeights_HLT135.root"     
set puweight_53x_HLT150 = "`pwd`/../../scripts/puFiles/PileupWeights_HLT150.root"     

set location = "eth"
set version  = "v1"
set run = 0

if($#argv == 0 || $#argv < 3 || $#argv > 13 ) then
  echo "usage:  makeSingleGammaTreeNtp.csh <location> <version> <run if 1> <jsonfile> <pureweight> <pureweight_HLT30> <pureweight_HLT50> <pureweight_HLT75> <pureweight_HLT90> <energy correction/smearing>"
  echo "        locations: cern roma eth fnal"
  echo "        version: version string for redntp"
  echo "        run: default=0  set to 1 to execute"
  echo "        jsonfile: optional json to select good RUN_LS used for data (full path is required)"
  echo "        pu weight for MC: default=-1  set to 1 to store them"
  echo "        pu weight for MC, corresponding to HLT = 30: default=-1  set to 1 to store them"
  echo "        pu weight for MC, corresponding to HLT = 50: default=-1  set to 1 to store them"
  echo "        pu weight for MC, corresponding to HLT = 75: default=-1  set to 1 to store them"
  echo "        pu weight for MC, corresponding to HLT = 90: default=-1  set to 1 to store them"
  echo "        pu weight for MC, corresponding to HLT = 135: default=-1  set to 1 to store them"
  echo "        pu weight for MC, corresponding to HLT = 150: default=-1  set to 1 to store them"
  echo "        energy corrections"
  exit -1
endif

set location = $1
echo "location : $location "

set version = $2
echo "version : $version "

set run = $3
echo "run : $run "

if ($#argv > 3) then
  set data_json = $4
  echo "json : ${data_json}"
endif 

set puweight = -1
if ($#argv > 4) then
  set puweight = $5
  echo "pu weight: ${puweight}"
endif 

set puweight30 = -1
if ($#argv > 5) then
  set puweight30 = $6
  echo "pu weight 30: ${puweight30}"
endif 

set puweight50 = -1
if ($#argv > 6) then
  set puweight50 = $7
  echo "pu weight 50: ${puweight50}"
endif 

set puweight75 = -1
if ($#argv > 7) then
  set puweight75 = $8
  echo "pu weight 75: ${puweight75}"
endif 

set puweight90 = -1
if ($#argv > 8) then
  set puweight90 = $9
  echo "pu weight 90: ${puweight90}"
endif 

set puweight135 = -1
if ($#argv > 9) then
  set puweight135 = $10
  echo "pu weight 135: ${puweight135}"
endif 

set puweight150 = -1
if ($#argv > 10) then
  set puweight150 = $11
  echo "pu weight 150: ${puweight150}"
endif 

set energyCorrection = -1
if ($#argv > 11) then
  set energyCorrection = $12
  set energyCorrectionName = `basename ${energyCorrection} .dat`
  echo "energyCorrection: ${energyCorrection}"
endif 

echo ""

#foreach class ( 53xv2 )
foreach class ( 53xv6_data_CERN  53xv6_CERN)
#foreach class ( 53xv2_data )
#foreach class ( 53xv2_extra )
#    foreach preseltype ( preselectionCS cicpfloose preselectionMVA cicpfloosenoeleveto )
foreach preseltype ( gjetpresel )

	if ( "`echo ${class} | grep data`XXX" != "XXX" ) then
	    set command="./makeSingleGammaTreeNtp_giulia.csh ../../data/list.${class}/ redntp.${class}.${preseltype}.${energyCorrectionName}.${version} ${preseltype} ${location} ${run} $data_json -1 -1 -1 -1 -1 -1 -1 ${energyCorrection}"
	else 
	    if ( $puweight !=  -1 ) then
		if ( "`echo ${class} | grep 53x`XXX" != "XXX" ) then
		    set puweightFile = ${puweight_53x}
		endif
	    else
		set puweightFile = -1
	    endif

	    if ( $puweight30 != -1 ) then
		if ( "`echo ${class} | grep 53x`XXX" != "XXX" ) then
		    set puweightFile30 = ${puweight_53x_HLT30}
		endif
	    else
		set puweightFile30 = -1
	    endif

	    if ( $puweight50 != -1 ) then
		if ( "`echo ${class} | grep 53x`XXX" != "XXX" ) then
		    set puweightFile50 = ${puweight_53x_HLT50}
		endif
	    else
		set puweightFile50 = -1
	    endif

	    if ( $puweight75 != -1 ) then
		if ( "`echo ${class} | grep 53x`XXX" != "XXX" ) then
		    set puweightFile75 = ${puweight_53x_HLT75}
		endif
	    else
		set puweightFile75 = -1
	    endif

	    if ( $puweight90 != -1 ) then
		if ( "`echo ${class} | grep 53x`XXX" != "XXX" ) then
		    set puweightFile90 = ${puweight_53x_HLT90}
		endif
	    else
		set puweightFile90 = -1
	    endif

	    if ( $puweight135 != -1 ) then
		if ( "`echo ${class} | grep 53x`XXX" != "XXX" ) then
		    set puweightFile135 = ${puweight_53x_HLT135}
		endif
	    else
		set puweightFile135 = -1
	    endif

	    if ( $puweight150 != -1 ) then
		if ( "`echo ${class} | grep 53x`XXX" != "XXX" ) then
		    set puweightFile150 = ${puweight_53x_HLT150}
		endif
	    else
		set puweightFile150 = -1
	    endif

	    echo $puweightFile
	    echo $puweightFile30
	    echo $puweightFile50
	    echo $puweightFile75
	    echo $puweightFile90
	    echo $puweightFile135
	    echo $puweightFile150

	    set command="./makeSingleGammaTreeNtp_giulia.csh ../../data/list.${class}/ redntp.${class}.${preseltype}.${energyCorrectionName}.${version} ${preseltype} ${location} ${run} -1 ${puweightFile} ${puweightFile30} ${puweightFile50} ${puweightFile75} ${puweightFile90} ${puweightFile135} ${puweightFile150} ${energyCorrection}.MC"  
	endif
	echo ${command}
	if ( $run == 1 ) then
	   ${command}
	endif
    end
end
