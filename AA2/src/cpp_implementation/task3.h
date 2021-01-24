// Copyright 2021 Pescaru Tudor-Mihai 321CA

#ifndef TASK3_H_
#define TASK3_H_

#include "task.h"
#include "task2.h"

/*
 * Task3
 * This being an optimization problem, the solve method's logic has to work differently.
 * You have to search for the minimum number of arrests by successively querying the oracle.
 * Hint: it might be easier to reduce the current task to a previously solved task
 */
class Task3 : public Task {
 private:
    std::string task2_in_filename;
    std::string task2_out_filename;
    int N;                  // Number of mafia families
    int M;                  // Number of family realtions
    int K;                  // Size of extended family
    int **uv;               // Family relation matrix
    int **complement_uv;    // Complement family relation matrix 
    int *arrests;           // Array of families to be arrested
    std::string has_sol;    // True/False if problem has solution

 public:
    // O(N^3 * K^2 + N * M) time complexity O(N^2 * K^2) space complexity
    void solve() override {
        task2_in_filename = in_filename + "_t2";
        task2_out_filename = out_filename + "_t2";
        Task2 task2_solver = Task2();
        task2_solver.add_files(task2_in_filename, oracle_in_filename, oracle_out_filename, task2_out_filename);
        read_problem_data();

        // Check for extended family from largest possible to smallest
        for (int i = 0; i < N; i++) {
            K = N - i;
            reduce_to_task2();
            task2_solver.solve();
            extract_answer_from_task2();
            // First solution found is min one
            if (has_sol == "True") {
                break;
            }
        }

        write_answer();
    }

    // O(N^2 + M) time complexity O(N^2) space complexity
    void read_problem_data() override {
        std::ifstream in (in_filename);
        // Read N, M, K
        in >> N >> M;
        // Alocate space for adjacency matrix for normal and complement family graph
        uv = new int*[N];
        complement_uv = new int*[N];
        // Allocate space for array of families to be arrested
        arrests = new int[N];
        for (int i = 0; i < N; i++) {
            uv[i] = new int[N];
            complement_uv[i] = new int[N];
        }
        // Initialise matrices and array
        for (int i = 0; i < N; i++) {
            arrests[i] = 0;
            for (int j = 0; j < N; j++) {
                uv[i][j] = 0;
                // Keep the diagonal 0 for the complement graph
                if (i != j) {
                    complement_uv[i][j] = 1;
                } else {
                    complement_uv[i][j] = 0;
                }
            }
        }
        // Read relations and update adjacency matrices
        for (int i = 0; i < M; i++) {
            int u, v;
            in >> u >> v;
            uv[u - 1][v - 1] = 1;
            uv[v - 1][u - 1] = 1;
            complement_uv[u - 1][v - 1] = 0;
            complement_uv[v - 1][u - 1] = 0;
        }
        in.close();
    }

    // O(N^2) time-complexity O(1) space complexity
    void reduce_to_task2() {
        std::ofstream task2_in (task2_in_filename);
        // Calculate number of edges in complement graph
        int remaining = (N * (N - 1)) / 2 - M;
        // Write number of families, number of edges and size of extended family
        task2_in << N << ' ' << remaining << ' ' << K << std::endl;
        // Write edges from complement graph
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (complement_uv[i][j] == 1) {
                    task2_in << i + 1 << ' ' << j + 1 << std::endl;
                }
            }
        }
        task2_in.close();
    }

    // O(N) time complexity O(1) space complexity
    void extract_answer_from_task2() {
        std::ifstream task2_out (task2_out_filename);
        // Read if input has solution
        task2_out >> has_sol;
        // If it has solution get families that won't be arrested
        if (has_sol == "True") {
            int i;
            while (task2_out >> i) {
                arrests[i - 1] = 1;
            }
        }
        task2_out.close();
    }

    // O(N) time complexity O(1) space complexity
    void write_answer() override {
        std::ofstream out (out_filename);
        // Write numbers of families to be arrested
        for (int i = 0; i < N; i++) {
            if (arrests[i] == 0) {
                out << i + 1 << ' ';
            }
        }
        out.close();
        for (int i = 0; i < N; i++) {
            delete [] uv[i];
            delete [] complement_uv[i];
        }
        delete [] uv;
        delete [] complement_uv;
        delete [] arrests;
    };
};

#endif  // TASK3_H_
