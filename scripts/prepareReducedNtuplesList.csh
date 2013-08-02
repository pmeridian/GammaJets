#!/bin/bash

find $1 -maxdepth 1 -type f  | grep ".root" > /tmp/list
#cat /tmp/list
cat /tmp/list | awk -F 'redntp_' '{printf "%s\n",$2}' | sed -e 's%\(.*\)_\(.*\).root%\1%g' | sort | uniq> /tmp/samples

for sample in `cat /tmp/samples`; do
#    echo $sample
    cat /tmp/list | grep ${sample} > $2/${sample}.list
    echo "$2/${sample}.list written"
done

