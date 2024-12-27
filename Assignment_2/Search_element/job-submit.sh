#!/bin/bash
#SBATCH --job-name=mpi_search            # Job name
#SBATCH --nodes=4                        # Number of nodes
#SBATCH --tasks-per-node=32              # Tasks per node
#SBATCH --nodelist=node[4-7]             # Specific nodes to use
#SBATCH --output=output.log              # Output file for the job
#SBATCH --error=error.log                # Error file for the job

module load openmpi                      # Load the OpenMPI module
cd $SLURM_SUBMIT_DIR                     # Change to the directory where the job was submitted

mpicxx -o main_ruff main_ruff.cpp                  # Compile the MPI program

process_counts=(1 8 16 32 64)            # Define the number of processes to test

# Run the program for each process count
for p in "${process_counts[@]}"; do
    echo "Running with $p processes"
    mpirun -np $p ./main_ruff >> results_${p}_procs.txt
    echo "----------------------------------------" >> results_${p}_procs.txt
done
