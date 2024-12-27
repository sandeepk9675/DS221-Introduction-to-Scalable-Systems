#include <iostream>
#include <vector>
#include <omp.h>
#include <numeric>  // For std::iota
#include <ctime>    // For timing

// Function to compute the sequential prefix sum
void sequential_prefix_sum(const std::vector<int>& A, std::vector<int>& B) {
    B[0] = A[0];
    for (size_t i = 1; i < A.size(); ++i) {
        B[i] = B[i - 1] + A[i];
    }
}

// Function to compute the parallel prefix sum
void parallel_prefix_sum(const std::vector<int>& A, std::vector<int>& B, int num_threads) {
    size_t n = A.size();
    std::vector<int> offset(num_threads, 0);  // Vector to store offsets for each thread

    // Step 1: Partial prefix sums in parallel
    #pragma omp parallel num_threads(num_threads)
    {
        int tid = omp_get_thread_num();
        int chunk_size = (n + num_threads - 1) / num_threads;
        size_t start = tid * chunk_size;
        size_t end = std::min(start + chunk_size, n);

        // Compute local prefix sum for each thread
        if (start < n) {
            B[start] = A[start];
            for (size_t i = start + 1; i < end; ++i) {
                B[i] = B[i - 1] + A[i];
            }
            // Store the last element as offset for each chunk (only if not the first thread)
            if (tid > 0) {
                offset[tid] = B[end - 1];
            }
        }
    }

    // Step 2: Compute global offsets
    for (int i = 1; i < num_threads; ++i) {
        offset[i] += offset[i - 1];
    }

    // Step 3: Apply offsets to each chunk in parallel
    #pragma omp parallel num_threads(num_threads)
    {
        int tid = omp_get_thread_num();
        int chunk_size = (n + num_threads - 1) / num_threads;
        size_t start = tid * chunk_size;
        size_t end = std::min(start + chunk_size, n);

        // Add the offset to each element of the current chunk, if not the first thread
        if (tid > 0 && start < n) {
            for (size_t i = start; i < end; ++i) {
                B[i] += offset[tid - 1];
            }
        }
    }
}

int main() {
    // Experiment parameters
    std::vector<int> array_sizes = {1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000 };
    std::vector<int> thread_counts = {2, 4, 8, 16, 32, 64};

    // Loop over each array size
    for (int size : array_sizes) {
        std::vector<int> A(size);
        std::iota(A.begin(), A.end(), 1);  // Fill A with 1, 2, ..., size
        std::vector<int> B(size);

        // Sequential execution time (baseline)
        double seq_time = 0.0;
        for (int i = 0; i < 5; ++i) {
            double start_time = omp_get_wtime();
            sequential_prefix_sum(A, B);
            seq_time += (omp_get_wtime() - start_time);
        }
        seq_time /= 5;
        std::cout << "Array Size: " << size << " | Sequential Time: " << seq_time << "s\n";

        // Loop over each thread count
        for (int threads : thread_counts) {
            double parallel_time = 0.0;
            
            // Run the parallel prefix sum 5 times and average the times
            for (int i = 0; i < 5; ++i) {
                double start_time = omp_get_wtime();
                parallel_prefix_sum(A, B, threads);
                parallel_time += (omp_get_wtime() - start_time);
            }
            parallel_time /= 5;

            // Calculate and print the speedup
            double speedup = seq_time / parallel_time;
            std::cout << "Threads: " << threads << " | Parallel Time: " << parallel_time 
                      << "s | Speedup: " << speedup << "\n";
        }
        std::cout << "---------------------------------------------\n";
    }

    return 0;
}