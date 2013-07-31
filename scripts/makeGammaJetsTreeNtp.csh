#!/bin/tcsh
# $Id: makeGammaJetsTreeNtp.csh,v 1.1 2013/01/17 14:13:25 crovelli Exp $

# change if needed
set castordir = /castor/cern.ch/user/c/crovelli/GammaJets/reduced

if($#argv == 0 || $#argv < 2 || $#argv > 5 ) then
  echo "usage: makeGammaJetsTreeNtp.csh <inlist> <outdir> <run if 1> <jsonfile> <puweight>"
  echo "       inlist: valid directory containing list files OR valid list file"
  echo "       outdir: will be created in current directory in rome or on castor at cern"
  echo "               check |castordir| at the beginning of script"
  echo "       run: default=0  set to 1 to execute"
  echo "       jsonfile: optional json to select good RUN_LS"
  echo "       puweight: optional file for puweight"
  exit 0
endif

# submit the job only if the 2nd argument is 1
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

set run = 0
if ($#argv > 2) then
  set run = $3
  echo "run : $run "
endif 

set json = -1
if ($#argv > 3) then
  set json = $4
  echo "json : $json "
endif 

set puweight = -1
if ($#argv > 5) then
  set puweight = $5
  echo "puweight : $puweight "
endif 

echo "------   ready ro run  ------------------"

# logfiles always stored locally
set logdir = "$PWD/log/$outdir"
if($run == 1) mkdir -p $logdir

# choose queue, location based on location
set queue = 8nh
set outdir = $castordir/$outdir
set prefix = ""
echo "chiara: outdie = " $outdir
echo "$outdir created on castor"

echo "queue : $queue "
echo "output files: $outdir"
echo "log files: $logdir"

# app to run
set app = ../src/tmp/gammaJetsApp

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
   set jobname = "${sample}"
   set logfile = "${logdir}/${sample}.txt"
   set logerrfile = "${logdir}/${sample}_err.txt"
   set listfile = "${listdir}/${sample}.list"

   set command = "bsub -q ${queue} -o $logfile -J ${jobname} scriptGammaJets.sh ${PWD} ${PWD}/${listfile} ${rootfile} ${json} ${puweight}"

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

   set command = "bsub -q ${queue} -o $logfile -J ${jobname} scriptGammaJets.sh ${PWD} ${PWD}/${listfile} ${rootfile} ${json} ${puweight}"

   echo "---------------------------"
   echo "job name: ${jobname}"
   echo " command: ${command}"
   if($run == 1) then
     ${command}
   endif


  end

endif
