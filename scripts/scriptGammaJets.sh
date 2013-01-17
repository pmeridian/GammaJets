#!/bin/bash

domain=`dnsdomainname`

cd $1
eval `scramv1 runtime -sh`

redirector=pccmsrm27.cern.ch
castordir=`dirname $3`
filename=`basename $3`
xrootdir=/cms/local/`echo $castordir | awk -F '/' '{for (i=NF-3; i<=NF; i++) { printf "%s/",$i};}'`
echo "Creating dir root://${redirector}//${xrootdir}" 
xrd mkdir ${redirector} ${xrootdir}
echo "Output ${filename} will be copied in root://${redirector}/${xrootdir}"
cd -

echo dir is $CMSSW_BASE file is $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} 
echo ${CMSSW_BASE}/src/GammaJets/src/tmp/gammaJetsApp $2 ${filename} $4 $5 
   
${CMSSW_BASE}/src/GammaJets/src/tmp/gammaJetsApp $2 ${filename} $4 $5 
exit_stat=$?

if [ ${exit_stat} != 0 ]; then
    echo `date` ${xrootdir}/${filename} ${exit_stat} >> $1/log/runerror.jobs
    exit ${exit_stat}
else
    echo `date` ${xrootdir}/${filename} >> $1/log/runsuccess.jobs
fi

xrdcp ${filename} root://${redirector}//${xrootdir}/${filename}
exit_stat1=$?
if [ ${exit_stat1} != 0 ]; then
    echo `date` ${xrootdir}/${filename} ${exit_stat1} >> $1/log/xrootcopyerror.jobs
else
    echo `date` ${xrootdir}/${filename} >> $1/log/copysuccess.jobs
fi
