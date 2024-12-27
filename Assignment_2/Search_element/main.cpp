#include <mpi.h>

#include <iostream>

#include <cstdlib>

#include <ctime>

#include "vector_io.h"
 
int main(int argc, char** argv) {

    int rank, size;

    double average_execution_time = 0.0; // Initialize to 0

    std::vector<int> array;

    const int NUM_TRIALS = 20;           // Number of search trials

    int* local_array = nullptr;

    int local_size, target, global_index = -1, local_index = -1;

    bool found = false;
 
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
 
    if (rank == 0) {

        // Root process reads the array from file

        array = read_from_file("input.bin");  // Assuming input file is named input.bin

    }
 
    // Get the total array size

    int N = array.size();

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {

        array.resize(N);

    }
 
    // Broadcast the entire array to all processes

    MPI_Bcast(array.data(), N, MPI_INT, 0, MPI_COMM_WORLD);
 
    // Divide the array among processes

    local_size = N / size;

    local_array = new int[local_size];

    MPI_Scatter(array.data(), local_size, MPI_INT, local_array, local_size, MPI_INT, 0, MPI_COMM_WORLD);
 
    // Perform the search NUM_TRIALS times

    for (int trial = 0; trial < NUM_TRIALS; ++trial) {

        if (rank == 0) {

            target = rand() % 5000000 + 1; // Generate a new random target

            std::cout << "Trial " << trial + 1 << ": Searching for target " << target << std::endl;

        }
 
        // Start timing

        double start_time = MPI_Wtime();
 
        // Broadcast the target to all processes

        MPI_Bcast(&target, 1, MPI_INT, 0, MPI_COMM_WORLD);
 
        // Reset variables for each trial

        global_index = -1;

        local_index = -1;

        found = false;
 
        // Search for the target in the local portion of the array

        for (int i = 0; i < local_size; ++i) {

            if (local_array[i] == target) {

                local_index = i;

                found = true;

                break;

            }

        }
 
        // Calculate the global index if found

        if (found) {

            global_index = rank * local_size + local_index;

        }
 
        // Gather found indices from all processes to the root

        int global_indices[size];

        MPI_Gather(&global_index, 1, MPI_INT, global_indices, 1, MPI_INT, 0, MPI_COMM_WORLD);
 
        // Root process determines the result

        if (rank == 0) {

            bool global_found = false;

            for (int i = 0; i < size; ++i) {

                if (global_indices[i] != -1) {

                    global_index = global_indices[i];

                    global_found = true;

                    break;

                }

            }

            double end_time = MPI_Wtime();

            double execution_time = end_time - start_time;
 
            // Accumulate execution time for averaging

            average_execution_time += execution_time;
 
            if (global_found) {

                std::cout << "Element found at global index: " << global_index << std::endl;

            } else {

                std::cout << "Element not found in the array." << std::endl;

            }

            std::cout << "Execution time for Trial " << trial + 1 << ": " << execution_time << " seconds" << std::endl;

            std::cout << "--------------------------------------------" << std::endl;

        }

    }
 
    if (rank == 0) {

        // Compute and display average execution time

        average_execution_time /= NUM_TRIALS;

        std::cout << "Average Execution Time: " << average_execution_time << " seconds" << std::endl;

    }
 
    // Cleanup

    delete[] local_array;

    MPI_Finalize();

    return 0;

}
 