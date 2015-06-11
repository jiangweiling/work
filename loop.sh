#!/bin/bash
src_dir=$1
des_dir=$2
mkdir -p ${des_dir}
for input in ${src_dir}/*
do
	output=`echo $input|sed 's/ /_/g'`
	input=$(echo $input|sed 's/ /\ /g')
	output="${des_dir}/`basename $output`"
	cat "${input}" | ./filter.sh >> ${output}
done

