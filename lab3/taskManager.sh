#!/bin/bash

#PBS -l walltime=0:02:00                                                                                                                                                               
#PBS -l nodes=2:ppn=2                                                                                                                                                                  
#PBS -n 'dmytrenko_lab3'                                                                                                                                                          

ml icc
ml openmpi
cd /home/grid/testbed/tb099/lab3

a=$1
b=100
zero=0
one=1

if [ "$a" -eq "$one" ]
then
>helloResult.txt
fi

if [ "$a" -le "$b" ]
then
node="$(./hello)"
#echo "${node}"
countL=`cat helloResult.txt | grep ${node} | wc -l`
if [ "$countL" -eq "$zero" ]
then
  echo "${node} 1">>helloResult.txt
else
  count=`cat helloResult.txt | grep ${node} | awk -F' ' '{print $2}'`
  count=$((count+1))
  sed /^${node}/d helloResult.txt >helloResult.txt
  echo "${node} ${count}">>helloResult.txt
fi
#./hello>> helloResult.txt
echo -e "\n">>helloResult.txt

counter=$((a+1))
coproc read -t 60 && wait "$!" || true

./taskManager.sh $counter
fi
