#!/bin/tcsh
    
set data_json    = "`pwd`/jsonFiles/Cert_190456-195396_8TeV_PromptReco_Collisions12_JSON_v2.txt"
set puweight_53x = "`pwd`/nPU-Summer12_DD3.190456-201678-29Jun_Prompt.observed.root"

set location = "eth"
set version  = "v1"
set run = 0

if($#argv == 0 || $#argv < 3 || $#argv > 7 ) then
  echo "usage:  makeSingleGammaTreeNtp.csh <location> <version> <run if 1> <jsonfile> <pureweight>  <energy correction/smearing> "
  echo "        locations: cern roma eth"
  echo "        version: version string for redntp"
  echo "        run: default=0  set to 1 to execute"
  echo "        jsonfile: optional json to select good RUN_LS used for data (full path is required)"
  echo "        pu weight for MC: default=-1  set to 1 to store them"
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

set energyCorrection = -1
if ($#argv > 5) then
  set energyCorrection = $6
  set energyCorrectionName = `basename ${energyCorrection} .dat`
  echo "energyCorrection: ${energyCorrection}"
endif 

echo ""



#foreach class ( 52xv5 52xv5_data )
#foreach class ( 52xv5 )
#foreach class ( 52xv5_lisbon )
foreach class ( 53xv2 )
#foreach class ( 52xv5_data )
#foreach class ( 52xv5_lisbon 53xv1_data_lisbon )
#foreach class ( 53xv1_data_lisbon )
#    foreach preseltype ( preselectionCS cicpfloose preselectionMVA cicpfloosenoeleveto )
    foreach preseltype ( cicpfloose )
	if ( "`echo ${class} | grep data`XXX" != "XXX" ) then
	    set command="./makeSingleGammaTreeNtp_giulia.csh list.${class}/ redntp.${class}.${preseltype}.${energyCorrectionName}.${version} ${preseltype} ${location} ${run} $data_json -1 ${energyCorrection}"
	else 
	    if ( $puweight !=  -1 ) then
		if ( "`echo ${class} | grep 53x`XXX" != "XXX" ) then
		    set puweightFile = ${puweight_53x}
		endif
	    else
		set puweightFile = -1
	    endif

	    set command="./makeSingleGammaTreeNtp_giulia.csh list.${class}/ redntp.${class}.${preseltype}.${energyCorrectionName}.${version} ${preseltype} ${location} ${run} -1 ${puweightFile} ${energyCorrection}.MC"
	endif
	echo ${command}
	if ( $run == 1 ) then
	   ${command}
	endif
    end
end
