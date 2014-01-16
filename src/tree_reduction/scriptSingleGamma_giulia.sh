#!/bin/bash

domain=`dnsdomainname`
stagein='false'
stagein_nconcurrent_copies=3
main_dir=$1
ssh_opts="-x -q -o BatchMode=yes -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null"
scp_opts="-o BatchMode=yes -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null"

function xrdcopy {
#    echo "xrdcp $1 `pwd`/`basename $1`"
#    (xrdcp $1 `pwd`/`basename $1`)&
    (xrdcp $1 $2/`basename $1`)&
    pid=$!
    wait $pid
    status=$?
    if [ $status -ne 0 ]; then
        echo "`date` `hostname` $1 $status" >> $main_dir/log/stagein_error.log
    else
        echo "`date` `hostname` $1 $2/`basename $1`" >> $main_dir/log/stagein_success.log
    fi
}


function copy_list {
    for file in `cat $1 | egrep -v "^#"`; do
	echo "Copying $file"
	    while [ `jobs | wc -l` -ge ${stagein_nconcurrent_copies} ];
	      do
#         echo "Sleeping 5"                                                                                                                                                                                                                                                                       
	      sleep 5
	    done
	    if [ ! -r "`pwd`/`basename $file`" ]; then
#		(xrdcopy $file)&
		(xrdcopy $file $2)&
	    fi
    done
    while [ `jobs | wc -l` -ne 1 ];
      do
#      echo "Waiting for file to finish"                                                                                                                                                                                                                                                                      `jobs | wc -l` 
      sleep 5
 done

}

function modify_list {
    touch `pwd`/`basename $1`.mod
    for file in `cat $1 | egrep -v "^#"`; do
	echo $2/`basename $file` >>  $2/`basename $1`.mod
    done 
}


if [ "$domain" == "psi.ch" ]; then
    . $HOME/.bash_profile
elif [ "$domain" == "fnal.gov" ]; then
    echo "Sourcing FNAL CMSSW environment"
    source /uscmst1/prod/sw/cms/shrc uaf
fi


echo "Sourcing specific CMSSW release environment from $1"
cd $1
pwd
eval `scramv1 runtime -sh`
if [[ -z "${CMSSW_BASE}" ]]; then
    echo "Problem setting the CMSSW environment. Exit"
    exit -1
fi
echo "Done"

protocol=`echo $3 | awk -F ':' '{print $1}'`
echo "Stageout protocol is ${protocol}"

if [ "$domain" != "roma1.infn.it" ]; then
    if [ "${protocol}" == "root" ]; then
	redirector=`echo "$3" | awk -F '//' '{print $2}'`
#	castordir=`dirname $3`
#	filename=`basename $3`
#	xrootdir=/cms/local/`echo $castordir | awk -F '/' '{for (i=NF-3; i<=NF; i++) { printf "%s/",$i};}'`
	fullpath=`echo $3 | awk -F '//' '{print $3}' | sed -e 's%^%/%g' | sed -e "s%//%/%g"`
	xrootdir=`dirname ${fullpath}`
	filename=`basename ${fullpath}`
	echo "Creating dir ${protocol}://${redirector}//${xrootdir}"
	xrd ${redirector} mkdir  ${xrootdir}
	echo "Output ${filename} will be copied in ${protocol}://${redirector}/${xrootdir}"
    elif [ "${protocol}" == "sftp" ]; then
	redirector=`echo "$3" | awk -F '//' '{print $2}'`
#	xrootdir=/cms/local/`echo $castordir | awk -F '/' '{for (i=NF-3; i<=NF; i++) { printf "%s/",$i};}'`
	fullpath=`echo $3 | awk -F '//' '{print $3}' | sed -e 's%^%/%g' | sed -e "s%//%/%g"`
	xrootdir=`dirname ${fullpath}`
	filename=`basename ${fullpath}`
	echo "Creating dir ${protocol}://${redirector}//${xrootdir}"
	ssh ${ssh_opts} ${redirector} mkdir -p ${xrootdir}
	echo "Output ${filename} will be copied in ${protocol}://${redirector}/${xrootdir}"
    fi
else
    rootdir=`dirname $3`
    filename=`basename $3`
#    rootdir=/t3/`echo $castordir | awk -F '/' '{for (i=NF-3; i<=NF; i++) { printf "%s/",$i};}'`
    echo "Creating dir ${rootdir}"
    mkdir -p ${rootdir}
    echo "Output ${filename} will be copied in ${rootdir}"
    tempdir=`mktemp -d`
    if [ "$stagein" == "true" ]; then
	copy_list $2 $tempdir
    fi
fi
#else
#    filename=$2
#fi

if [ "$domain" != "roma1.infn.it" ]; then
    pwd
    cd -
    echo "Now I'm working in ${PWD}"
else
    cd $tempdir
fi

echo dir is ${PWD}
echo dir2 is ${CMSSW_BASE} 
echo file is $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} ${11} ${12}
list=$2
if [ "$stagein" == "true" ] &&  [ "$domain" == "roma1.infn.it" ]; then
    modify_list $list $tempdir
    list=`pwd`/`basename $list`.mod
fi
echo file2 is ${CMSSW_BASE}/src/GammaJets/src/tree_reduction/tmp/singlegammaApp_giulia ${list} ${filename} $5 $6 $7 $8 $9 ${10} ${11} ${12} #$4 ${8} ${9} $5 $6 $7 

if [ ! -f  ${CMSSW_BASE}/src/GammaJets/src/tree_reduction/tmp/singlegammaApp_giulia ]; then
    echo "Executable  ${CMSSW_BASE}/src/GammaJets/src/tree_reduction/tmp/singlegammaApp_giulia not found. Exit"
    exit -1
fi

${CMSSW_BASE}/src/GammaJets/src/tree_reduction/tmp/singlegammaApp_giulia ${list} ${filename} $5 $6 $7 $8 $9 ${10} ${11} ${12} #$4 $8 $9 $5 $6 $7 
exit_stat=$?

#if [ "$domain" == "cern.ch" ]; then
if [ ${exit_stat} != 0 ]; then
    echo `date` ${xrootdir}/${filename} ${exit_stat} >> $1/log/runerror.jobs
    exit ${exit_stat}
else
    echo `date` ${xrootdir}/${filename} >> $1/log/runsuccess.jobs
fi
#fi


if [ "$domain" != "roma1.infn.it" ]; then
    if [ "${protocol}" == "root" ]; then
	xrdcp ${filename} root://${redirector}//${xrootdir}/${filename}
	exit_stat1=$?
	if [ ${exit_stat1} != 0 ]; then
	    echo `date` `hostname` ${xrootdir}/${filename} ${exit_stat1} >> $1/log/xrootcopyerror.jobs
	else
	    echo `date` `hostname` ${xrootdir}/${filename} >> $1/log/xrootcopysuccess.jobs
	fi
    elif [ "${protocol}" == "sftp" ]; then
	ssh ${ssh_opts} ${redirector} rm -rf ${redirector}:${xrootdir}/${filename}
	scp ${scp_opts} ${filename} ${redirector}:${xrootdir}/${filename}
	exit_stat1=$?
	if [ ${exit_stat1} != 0 ]; then
	    echo `date` `hostname` ${xrootdir}/${filename} ${exit_stat1} >> $1/log/scpcopyerror.jobs
	else
	    echo `date` `hostname` ${xrootdir}/${filename} >> $1/log/scpcopysuccess.jobs
	fi
    fi
else 
    cp ${filename} ${rootdir}/${filename}
    exit_stat1=$?
    if [ ${exit_stat1} != 0 ]; then
	echo `date` `hostname` ${rootdir}/${filename} ${exit_stat1} >> $1/log/copyerror.jobs
    else
	echo `date` `hostname` ${rootdir}/${filename} >> $1/log/copysuccess.jobs
    fi
    if [ "$stagein" == "true" ]; then 
	echo "Cleaning ${tempdir}"
	cd -
	rm -rf ${tempdir}
    fi
fi
