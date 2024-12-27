#!/bin/bash
#SBATCH --job-name=sandeep-openmp
#SBATCH --tasks-per-node=32
#SBATCH --nodelist=node4

cd $SLURM_SUBMIT_DIR
make
./main