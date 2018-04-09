#!/bin/sh
#$ -V
#$ -cwd
#$ -S /bin/bash
#$ -N CS4379Hwk4
#$ -o $JOB_NAME.o$JOB_ID
#$ -e $JOB_NAME.e$JOB_ID
#$ -q omni
#$ -pe fill 9 # Must request square values
#$ -P quanah

module load gnu openmpi
mpirun --machinefile machinefile.$JOB_ID -np $NSLOTS ./hwk4
