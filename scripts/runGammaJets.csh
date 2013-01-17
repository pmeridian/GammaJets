#!/bin/tcsh
    
set data_json    = "`pwd`/jsonFiles/Cert_190456-195396_8TeV_PromptReco_Collisions12_JSON_v2.txt"
set puweight_52x = "`pwd`/puFiles/nPU-Summer12_DD3.190456-201678-29Jun_Prompt.observed.root"

set version  = "v1"
set run = 0

if($#argv == 0 || $#argv < 1 || $#argv > 5 ) then
  echo "usage:  makeSingleGammaTreeNtp.csh <version> <run if 1> <jsonfile> <pureweight> "
  echo "        version: version string for redntp"
  echo "        run: default=0  set to 1 to execute"
  echo "        jsonfile: optional json to select good RUN_LS used for data (full path is required)"
  echo "        pu weight for MC: default=-1  set to 1 to store them"
  exit -1
endif

set version = $1
echo "version : $version "

set run = $2
echo "run : $run "

if ($#argv > 2) then
  set data_json = $3
  echo "json : ${data_json}"
endif 

set puweight = -1
if ($#argv > 3) then
  set puweight = $4
  echo "pu weight: ${puweight}"
endif 

echo ""

#foreach class ( 52xv5_lisbon 53xv1_data_lisbon )
foreach class ( 52xv5_lisbon )
    if ( "`echo ${class} | grep data`XXX" != "XXX" ) then
	set command="./makeGammaJetsTreeNtp.csh ../data/list.${class}/ redntp.${class}.${version} ${run} $data_json -1"
    else 
	if ( $puweight !=  -1 ) then
	    if ( "`echo ${class} | grep 52x`XXX" != "XXX" ) then
		set puweightFile = ${puweight_52x}
	    endif
	    else
		set puweightFile = -1
	    endif

	    set command="./makeGammaJetsTreeNtp.csh ../data/list.${class}/ redntp.${class}.${version} ${run} -1 ${puweightFile}"
    endif
    echo ${command}
    if ( $run == 1 ) then
	${command}
    endif
end
