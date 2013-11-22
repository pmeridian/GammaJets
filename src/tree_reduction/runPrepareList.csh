#!/bin/csh
# $Id: runPrepareList.csh,v 1.2 2013/06/24 09:56:45 meridian Exp $

if( $#argv<3  ) then
  echo "usage:  runPrepareList.csh  <list dir>  <directory> <location>   [run if 1]"
  exit 0
endif

set prepareListCommand = prepareList.csh

set run = 0

if( $#argv>2 ) then
  set run = $4
endif

set listdir = $1

set srmdir = "$2"

set location = $3

echo "Configuring list for $location"

if ( "$location" == "cern" ) then
    set lsCommand="rfdir"
else if ( "$location" == "xrootd" || "$location" == "eos" ) then
    set lsCommand="/afs/cern.ch/project/eos/installation/0.1.0-22d/bin/eos.select find"
else if ( "$location" == "eosfnal" ) then
    set lsCommand="xrd cmseos.fnal.gov"
else if ( "$location" == "fnal" ) then
    set lsCommand="find"
else if ( "$location" == "eth" ) then
    set lsCommand="lcg-ls"
endif 

echo "lsCommand is $lsCommand"

rm -rf ${listdir}/allFiles.txt
mkdir -p ${listdir}
touch ${listdir}/allFiles.txt

if ($location == "xrootd" || $location == "eos") then 
#    echo "${lsCommand} -type f ${srmdir}"
    ${lsCommand} -f "${srmdir}"  >> ${listdir}/allFiles.txt
else if ($location == "eosfnal") then 
#    echo "${lsCommand} -type f ${srmdir}"
    ${lsCommand} dirlistrec "${srmdir}" | awk '{print $5}' | grep .root >> ${listdir}/allFiles.txt
else if ($location == "fnal") then 
#    echo "${lsCommand} -type f ${srmdir}"
    ${lsCommand} "${srmdir}" -type f | grep .root | sed -e 's%/pnfs/cms/WAX/11%%g'>> ${listdir}/allFiles.txt
else if ($location == "cern") then 
    foreach dir (`${lsCommand} "${srmdir}" | awk '{print $9}'`)
	${lsCommand} "${srmdir}/${dir}" | awk '{print $9}' | xargs -I file echo ${srmdir}/${dir}/file >> ${listdir}/allFiles.txt
    end
else 
    ${lsCommand} "${srmdir}" | awk -F '/' '{print $NF}' | xargs -I {} ${lsCommand} "${srmdir}/{}" >> ${listdir}/allFiles.txt
endif

cd ${listdir}/
#if ( $location == "cern" ) then
#    foreach file (`ls *.txt`)
#	echo $file >> allFiles.txt
#	rm -rf $file
#    end
#endif


if ($location == "xrootd" || $location == "eos") then    
#    echo "${lsCommand} -d ${srmdir}  | awk -F '/' '{print NF}'" 
    ${lsCommand} -d "${srmdir}"  | awk -F '/' '{ if (NF>1) {dir=NF-1; print $dir}}' | xargs -I {} ../${prepareListCommand} allFiles.txt {}  ${location} ${run} >! makeLists.log
else if ($location == "eosfnal") then    
#    echo "${lsCommand} -d ${srmdir}  | awk -F '/' '{print NF}'" 
#    ${lsCommand} dirlist "${srmdir}"  | awk '{print $5}' |  awk -F '/' '{ if (NF>1) {dir=NF; print $dir}}' 
    ${lsCommand} dirlist "${srmdir}"  | awk '{print $5}' |  awk -F '/' '{ if (NF>1) {dir=NF; print $dir}}' | xargs -I {} ../${prepareListCommand} allFiles.txt {}  ${location} ${run} >! makeLists.log
else if ($location == "fnal") then    
    ${lsCommand} "${srmdir}" -maxdepth 1 -type d  |  sed '1d' | awk -F '/' '{ if (NF>1) {dir=NF; print $dir}}' | xargs -I {} ../${prepareListCommand} allFiles.txt {}  ${location} ${run} >! makeLists.log
else if ($location == "cern") then 
    ${lsCommand} "${srmdir}" | awk '{print $9}' | xargs -I {} ../${prepareListCommand} allFiles.txt {}  ${location} ${run} >! makeLists.log
else 
    ${lsCommand} "${srmdir}" | awk -F '/' '{print $NF}' | xargs -I {} ../${prepareListCommand} allFiles.txt {} ${location} ${run} >! makeLists.log
endif

if( $run != 1 ) then
  rm -rf ${listdir}
endif
