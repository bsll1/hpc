#!/bin/bash

#PBS -l walltime=0:02:00                                                                                                                                                               
#PBS -l nodes=1:ppn=8                                                                                                                                                                  
#PBS -n 'dmytrenko_lab4'                                                                                                                                                           

cd /home/grid/testbed/tb099/lab4/hpc

./lab4.out 1000 3 > Node8.txt

