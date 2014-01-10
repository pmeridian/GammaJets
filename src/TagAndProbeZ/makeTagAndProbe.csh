#!/bin/tcsh
# $Id: makeTagAndProbe.csh,v 1.4 2013/06/06 16:25:59 gdimperi Exp $

# change if needed
#set castordir = /castor/cern.ch/user/m/meridian/Higgs/reduced
#set castordir = /castor/cern.ch/user/g/gdimperi/Higgs/reduced
set castordir = sftp://meridian@cmsrm-an.roma1.infn.it///t3/users/meridian/GammaJets/TandP/reduced

set photonIDweights_EB = /afs/cern.ch/user/m/meridian/public/photonIDweights/TMVA_EBpf_BDT.weights.xml
set photonIDweights_EE = /afs/cern.ch/user/m/meridian/public/photonIDweights/TMVA_EEpf_BDT.weights.xml
set preselections      = ( tandp2012 )

if($#argv == 0 || $#argv < 5 || $#argv > 13 ) then
#  echo "usage: makeTagAndProbeTreeNtp.csh <inlist> <outdir> <pre-selection> <location> <run if 1> <jsonfile> <puweight> <energy correction/smearing>"
  echo "usage: makeSingleGammaTreeNtp.csh <inlist> <outdir> <pre-selection> <location> <run if 1> <jsonfile> <puweight> <energy correction/smearing> <puweight_HLT30> <puweight_HLT50> <puweight_HLT75> <puweight_HLT90>"
  echo "       inlist: valid directory containing list files OR valid list file"
  echo "       outdir: will be created in current directory in rome or on castor at cern"
  echo "               check |castordir| at the beginning of script"
  echo "       preselection:  $preselections"
  echo "       locations: cern roma eth"
  echo "       run: default=0  set to 1 to execute"
  echo "       jsonfile: optional json to select good RUN_LS"
  echo "       puweight: optional file for puweight"
  echo "       puweight_HLT30: optional file for puweight, HLT threshold = 30"
  echo "       puweight_HLT50: optional file for puweight, HLT threshold = 50"
  echo "       puweight_HLT75: optional file for puweight, HLT threshold = 75"
  echo "       puweight_HLT90: optional file for puweight, HLT threshold = 90"
  echo "       r9weight: optional file for r9weight"
  echo "       energy correction file"
  exit 0
endif

# submit the job only if the cmscaf1nd argument is 1
set listdir  = list.V27.41x 
if ($#argv > 0) then
  set listdir = $1
  if(-f $listdir) then
       echo "<$listdir> is a single file"
  else if( -d $listdir ) then
       echo "<$listdir> is a directory"
   else 
    exit -1
  endif
endif 

set outdir = ""
if ($#argv > 1) then
  set outdir = $2
  echo "outdir : $outdir "
endif 

setenv selection  ""
if ($#argv > 2) then
  setenv selection  $3
  set found = 0
  foreach i  ( $preselections )
    if( $selection == $i ) set found = 1
  end
  if($found == 0) then
    echo "bad preselection <$selection>. Choose from $preselections"
    exit -1
  end
  echo "selection : $selection "
endif 

# location: roma or cern or eth
set location = ""
if ($#argv > 3) then
  set location = $4
  echo "location : $location "
  if( $location != roma && $location != cern && $location != eth &&  $location != fnal) then
    echo "bad location. options: roma or cern or eth"
    exit -1
endif 

set run = 0
if ($#argv > 4) then
  set run = $5
  echo "run : $run "
endif 

set json = -1
if ($#argv > 5) then
  set json = $6
  echo "json : $json "
endif 

set puweight = -1
if ($#argv > 6) then
  set puweight = $7
  echo "puweight : $puweight "
endif 

set puweight30 = -1
if ($#argv > 7) then
  set puweight30 = $8
  echo "puweight30 : $puweight30 "
endif

set puweight50 = -1
if ($#argv > 8) then
  set puweight50 = $9
  echo "puweight50 : $puweight50 "
endif
 
set puweight75 = -1
if ($#argv > 9) then
  set puweight75 = $10
  echo "puweight75 : $puweight75 "
endif

set puweight90 = -1
if ($#argv > 10) then
  set puweight90 = $11
  echo "puweight90 : $puweight90 "
endif

set r9weight = -1
if ($#argv > 11) then
  set r9weight = $12
  echo "r9weight : $r9weight "
endif

set energyCorrection = -1
if ($#argv > 12) then
  set energyCorrection = $13
  echo "energyCorrection: ${energyCorrection}"
endif 

echo "------   ready ro run at $location ------------------"

# logfiles always stored locally
set logdir = "$PWD/log/$outdir"
set jobdir = "$PWD/jobs/$outdir"
if($run == 1) mkdir -p $logdir
mkdir -p $jobdir

# choose queue, location based on location
if ($location == "cern" ) then
  set photonIDweights_EB = /afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_withRho_EB/TMVAClassification_BDTG.weights.xml
  set photonIDweights_EE = /afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_withRho_EE/TMVAClassification_BDTG.weights.xml
  set queue = 8nh
  set outdir = $castordir/$outdir
  set prefix = ""
  echo "chiara: " $outdir
  #if($run == 1) rfmkdir $outdir  # chiara
  echo "$outdir created on castor"
else if ($location == "roma" ) then
  set photonIDweights_EB = /cmshome/meridian/photonIDweights/TMVA_EBpf_BDT.weights.xml
  set photonIDweights_EE = /cmshome/meridian/photonIDweights/TMVA_EEpf_BDT.weights.xml
  set queue = "cmsan"
  set outdir = $castordir/$outdir
  set prefix = ""
  if($run == 1) mkdir -p $outdir
else if ($location == "eth" ) then
  set queue = "short.q"
  set outdir = $outdir
  set prefix = ""
  if($run == 1) mkdir -p $outdir
else if ($location == "fnal" ) then
  set photonIDweights_EB = /uscms/home/meridian/photonIDWeights/TMVAClassification_BDTG.weights.EB.xml
  set photonIDweights_EE = /uscms/home/meridian/photonIDWeights/TMVAClassification_BDTG.weights.EE.xml
  set queue = "condor"
  set outdir = $castordir/$outdir
  set prefix = ""
  if($run == 1) mkdir -p $outdir
endif 

echo "queue : $queue "
echo "output files: $outdir"
echo "log files: $logdir"
echo "pre-selection: $selection"

# app to run
#set app = ./tmp/singlegammaApp_forMVA
set app = ./tmp/tagandprobeApp

if(! -e $app ) then
  echo "missing executable $app"
  exit 0
endif 

## if listdir is one file only
if(-f $listdir) then
   set sample  = `echo $listdir  | awk  'BEGIN{FS="/"}{print $NF}' | awk 'BEGIN{FS="."}{print $1}'`
   set listdir = `echo $listdir  | awk  'BEGIN{FS="/"}{print $1}'`
   setenv listfile $listdir
   setenv rootfile "${prefix}${outdir}/redntp_${sample}.root"     
#   setenv rootfile "${prefix}${outdir}/redntp_${sample}_forMVA.root" 
   set jobname = "${sample}"
   set logfile = "${logdir}/${sample}.txt"
   set logerrfile = "${logdir}/${sample}_err.txt"
   set listfile = "${listdir}/${sample}.list"

   if ($location == "cern" || $location == "roma") then  
     set command = "bsub -q ${queue} -o $logfile  -e $logerrfile -J ${jobname} `pwd`/scriptTagAndProbe.sh ${PWD} ${PWD}/${listfile} ${rootfile} ${selection} ${json} ${puweight} ${puweight30} ${puweight50} ${puweight75} ${puweight90} ${r9weight} ${photonIDweights_EB} ${photonIDweights_EE} ${energyCorrection}"# "
   else if ($location == "eth" ) then
     set command = "qsub -q ${queue} -o $logfile -e $logerrfile `pwd`/scriptTagAndProbe.sh ${PWD} ${PWD}/${listfile} ${rootfile} ${selection} ${json} ${puweight} ${puweight30} ${puweight50} ${puweight75} ${puweight90} ${r9weight} ${photonIDweights_EB} ${photonIDweights_EE} ${energyCorrection}"# ${photonIDweights_EB} ${photonIDweights_EE}"
   endif  

   echo "---------------------------"
   echo "job name: ${jobname}"
   echo " command: ${command}"
   if($run == 1) then
     ${command}
   endif

  ## if input is a directory
else if(-d $listdir) then
  foreach i ( `/bin/ls -1 ${listdir} | grep ".list" | awk 'BEGIN{FS="."}{print $1}' | xargs  -I sample echo sample ` )
   set  sample = $i
   echo "sample : $sample"

   if( "`echo $sample | egrep -e "^G_Pt_"`XXX" != "XXX" ) then
     echo "skipping $sample"
     continue
   endif

   setenv rootfile "${prefix}${outdir}/redntp_${sample}.root"
   set jobname = "${sample}"
   set logfile = "${logdir}/${sample}.txt"
   set logerrfile = "${logdir}/${sample}_err.txt"
   setenv listfile  "${listdir}/${sample}.list"

   if ($location == "cern" || $location == "roma") then  
     set command = "bsub -q ${queue} -o $logfile -e $logerrfile -J ${jobname} `pwd`/scriptTagAndProbe.sh ${PWD} ${PWD}/${listfile} ${rootfile} ${selection} ${json} ${puweight} ${puweight30} ${puweight50} ${puweight75} ${puweight90} ${r9weight} ${photonIDweights_EB} ${photonIDweights_EE} ${energyCorrection}"# ${photonIDweights_EB} ${photonIDweights_EE}"
   else if ($location == "fnal") then  
#    echo "Creating  ${jobdir}/job_condor_${jobname}"
     cat <<EOF >! ${jobdir}/job_condor_${jobname}
universe = vanilla
Executable = `pwd`/scriptTagAndProbe.sh
Requirements = Memory >= 199 &&OpSys == "LINUX"&& (Arch != "DUMMY" )&& Disk > 1000000
Should_Transfer_Files = NO
#WhenToTransferOutput = ON_EXIT
Output = $logfile
Error = $logerrfile
Log = $logfile
#notify_user = ${LOGNAME}@FNAL.GOV
notify_user = nobody
Arguments =  ${PWD} ${PWD}/${listfile} ${rootfile} ${selection} ${json} ${puweight} ${puweight30} ${puweight50} ${puweight75} ${puweight90}  ${r9weight} ${photonIDweights_EB} ${photonIDweights_EE} ${energyCorrection}
#${photonIDweights_EB} ${photonIDweights_EE}
Queue
EOF
     set command = "condor_submit ${jobdir}/job_condor_${jobname}"
   else if ($location == "eth" ) then
     set command = "qsub -q ${queue} -o $logfile -e $logerrfile  `pwd`/scriptTagAndProbe.sh ${PWD} ${PWD}/${listfile} ${rootfile} ${selection} ${json} ${puweight} ${puweight30} ${puweight50} ${puweight75} ${puweight90} ${r9weight} ${photonIDweights_EB} ${photonIDweights_EE} ${energyCorrection}"# ${photonIDweights_EB} ${photonIDweights_EE}"
   endif  

   echo "---------------------------"
   echo "job name: ${jobname}"
   echo " command: ${command}"
   if($run == 1) then
     ${command}
   endif
  end
endif
