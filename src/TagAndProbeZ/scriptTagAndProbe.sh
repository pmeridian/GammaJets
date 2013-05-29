#!/bin/bash

domain=`dnsdomainname`

if [ "$domain" == "psi.ch" ]; then
    . $HOME/.bash_profile
fi

cd $1
eval `scramv1 runtime -sh`

if [ "$domain" == "cern.ch" ]; then
    redirector=pccmsrm27.cern.ch
    castordir=`dirname $3`
    filename=`basename $3`
    ## rfmkdir ${castordir}   chiara!
    xrootdir=/cms/local/`echo $castordir | awk -F '/' '{for (i=NF-3; i<=NF; i++) { printf "%s/",$i};}'`
    echo "Creating dir root://${redirector}//${xrootdir}"
    xrd ${redirector} mkdir ${xrootdir}
    echo "Output ${filename} will be copied in root://${redirector}/${xrootdir}"
else
    filename=$2
fi

if [ "$domain" == "cern.ch" ]; then
    cd -
fi

echo dir is ${CMSSW_BASE} 
echo file is $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} 
# $1   --->   ${PWD} 
# $2   --->   ${PWD}/${listfile} 
# $3   --->   ${rootfile} 
# $4   --->   ${selection} 
# $5   --->   ${json} 
# $6   --->   ${puweight} 
# $7   --->   ${puweight_HLT30}
# $8   --->   ${puweight_HLT50}
# $9   --->   ${puweight_HLT75}
# $10   --->   ${puweight_HLT90}

# $11   --->   ${energyCorrection} 
# $12   --->   ${photonIDweights_EB} 
# $13   --->   ${photonIDweights_EE}

echo file2 is ${CMSSW_BASE}/src/GammaJets/src/tree_reduction/tmp/tagandprobeApp $2 ${filename} $5 $6 $7 $8 $9 ${10} #$4 ${8} ${9} $5 $6 $7

#echo ${CMSSW_BASE}/src/GammaJets/src/TagAndProbeZ/tmp/tagandprobeApp $2 ${filename} $5 $6 $7 
#echo ${CMSSW_BASE}/src/GammaJets/src/tree_reduction/tmp/tagandprobeApp_forMVA $2 ${filename} #$4 ${8} ${9} $5 $6 $7 


${CMSSW_BASE}/src/GammaJets/src/TagAndProbeZ/tmp/tagandprobeApp $2 ${filename} $5 $6 $7 $8 $9 ${10} 
#${CMSSW_BASE}/src/GammaJets/src/tree_reduction/tmp/tagandprobeApp_forMVA $2 ${filename} #$4 $8 $9 $5 $6 $7 

exit_stat=$?

if [ "$domain" == "cern.ch" ]; then
    if [ ${exit_stat} != 0 ]; then
	echo `date` ${xrootdir}/${filename} ${exit_stat} >> $1/log/runerror.jobs
	exit ${exit_stat}
    else
	echo `date` ${xrootdir}/${filename} >> $1/log/runsuccess.jobs
    fi
fi

if [ "$domain" == "cern.ch" ]; then
    xrdcp ${filename} root://${redirector}//${xrootdir}/${filename}
    exit_stat1=$?
    if [ ${exit_stat1} != 0 ]; then
	echo `date` ${xrootdir}/${filename} ${exit_stat1} >> $1/log/xrootcopyerror.jobs
    else
	echo `date` ${xrootdir}/${filename} >> $1/log/copysuccess.jobs
    fi
fi