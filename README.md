# Parallel Computing with MPI and OpenMP

This repository demonstrates parallel programming concepts using **MPI (Message Passing Interface)** and **OpenMP (Open Multi-Processing)**. It includes:

- **Element Search using MPI**: A distributed search algorithm leveraging MPI for parallel computation across multiple nodes.  
- **Prefix Sum using OpenMP**: A parallel implementation of the prefix sum algorithm using OpenMP.  

The repository also contains test files and job submission scripts for deployment in HPC (High-Performance Computing) environments.

---

## Repository Structure

```plaintext
.
├── tests_files/
│   ├── mpi/
│   │   ├── input.bin
│   ├── openmp/
│   │   ├── input_10k.bin            # Input file with 10,000 elements
│   │   ├── input_30k.bin            # Input file with 30,000 elements
│   │   ├── output_10k.bin           # Output file for 10,000 elements
│   │   ├── output_30k.bin           # Output file for 30,000 elements
│   ├── vector_io.h
├── prefix_sum/
│   ├── openmp_jobsubmit.sh          # SLURM job script for OpenMP program
│   ├── main.cpp                     # OpenMP implementation for prefix sum
├── Search_element/                
│   ├── mpi_job_submit.sh            # SLURM job script for MPI program
│   ├── main.cpp                     # MPI implementation for element search
└── README.md                        # This README file
```

---

## Features

### 1. **Element Search using MPI**
- Distributed search for a random target in a large array.
- Utilizes MPI for parallel execution across multiple processes.
- Measures execution time and averages performance over multiple trials.

#### How to Run
1. **Compile the Code**:
   ```bash
   mpicxx -o main main.cpp
   ```
2. **Submit the Job**:
   - Use the provided SLURM job script:
     ```bash
     sbatch mpi_job_submit.sh
     ```
3. **Output**:
   - Execution results are saved in `results_<process_count>_procs.txt`.

---

### 2. **Prefix Sum using OpenMP**
- Computes the prefix sum of an array in parallel using OpenMP.
- Compares performance against a sequential baseline.
- Outputs execution times, speedups, and validates results.

#### How to Run
1. **Prepare the Environment**:
   - Ensure OpenMP support is enabled in your compiler.

2. **Compile the Code**:
   - Add a `Makefile` or compile manually:
     ```bash
     g++ -fopenmp -o main main.cpp
     ```

3. **Submit the Job**:
   - Use the provided SLURM job script:
     ```bash
     sbatch openmp_jobsubmit.sh
     ```

4. **Output**:
   - Logs performance metrics and writes results to `output1.txt`.

---

## Test Files

Test files for both implementations are located in the `tests_files/` directory. These include:

- `mpi/input.bin`: Input file for MPI program.  
- `openmp/input_10k.bin` and `openmp/input_30k.bin`: Input files for OpenMP program.  

---

## Dependencies

- **MPI Implementation**: Requires OpenMPI or MPICH.  
- **OpenMP Support**: Use a compiler like GCC (`g++`) with OpenMP enabled.  
- **SLURM**: For job scheduling in an HPC environment.  

---
