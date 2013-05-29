#!/bin/bash

domain=`dnsdomainname`
stagein='true'
nconcurrent_copies=3
main_dir=$1

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
	    while [ `jobs | wc -l` -ge ${nconcurrent_copies} ];
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
fi

cd $1
eval `scramv1 runtime -sh`

if [ "$domain" == "cern.ch" ]; then
    redirector=pccmsrm27.cern.ch
    castordir=`dirname $3`
    filename=`basename $3`
    xrootdir=/cms/local/`echo $castordir | awk -F '/' '{for (i=NF-3; i<=NF; i++) { printf "%s/",$i};}'`
    echo "Creating dir root://${redirector}//${xrootdir}"
    xrd mkdir ${redirector} ${xrootdir}
    echo "Output ${filename} will be copied in root://${redirector}/${xrootdir}"
elif [ "$domain" == "roma1.infn.it" ]; then
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
else
    filename=$2
fi

if [ "$domain" == "cern.ch" ]; then
    cd -
elif [ "$domain" == "roma1.infn.it" ]; then
    cd $tempdir
fi

echo dir is ${PWD}
echo dir2 is $CMSSW_BASE 
echo file is $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} 
list=$2
if [ "$stagein" == "true" ] &&  [ "$domain" == "roma1.infn.it" ]; then
    modify_list $list $tempdir
    list=`pwd`/`basename $list`.mod
fi
echo file2 is ${CMSSW_BASE}/src/GammaJets/src/tree_reduction/tmp/singlegammaApp_giulia ${list} ${filename} $5 $6 $7 $8 $9 ${10} #$4 ${8} ${9} $5 $6 $7 

${CMSSW_BASE}/src/GammaJets/src/tree_reduction/tmp/singlegammaApp_giulia ${list} ${filename} $5 $6 $7 $8 $9 ${10} #$4 $8 $9 $5 $6 $7 
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
	echo `date` `hostname` ${xrootdir}/${filename} ${exit_stat1} >> $1/log/xrootcopyerror.jobs
    else
	echo `date` `hostname` ${xrootdir}/${filename} >> $1/log/copysuccess.jobs
    fi
elif [ "$domain" == "roma1.infn.it" ]; then
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
