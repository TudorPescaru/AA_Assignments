// Copyright 2021 Pescaru Tudor-Mihai 321CA

#ifndef BONUS_H_
#define BONUS_H_

#include "task.h"

/*
 * Bonus Task
 * read_problem_data         - read the problem input and store it however you see fit
 * formulate_oracle_question - transform the current problem instance into a SAT instance and write the oracle input
 * decipher_oracle_answer    - transform the SAT answer back to the current problem's answer
 * write_answer              - write the current problem's answer
 */
class Bonus : public Task {
 private:
    int N;          // Number of mafia families
    int M;          // Number of family realtions
    int **uv;       // Family relation matrix
    int *arrests;   // Array of families to be arrested

 public:
    // O(N^2 + M) time complexity O(N^2) space complexity
    void solve() override {
        read_problem_data();
        formulate_oracle_question();
        ask_oracle();
        decipher_oracle_answer();
        write_answer();
    }

    // O(N^2 + M) time complexity O(N^2) space complexity
    void read_problem_data() override {
        std::ifstream input (in_filename);
        // Read N, M
        input >> N >> M;
        // Allocate space for adjacency matrix and arrests array
        uv = new int*[N];
        arrests = new int[N];
        for (int i = 0; i < N; i++) {
            uv[i] = new int[N];
            // Initialise arrests array
            arrests[i] = 0;
        }
        // Read relations and update adjacency matrix
        for (int i = 0; i < M; i++) {
            int u, v;
            input >> u >> v;
            uv[u - 1][v - 1] = 1;
            uv[v - 1][u - 1] = 1;
        }
        input.close();
    }

    // O(N^2) time complexity O(1) space complexity
    void formulate_oracle_question() {
        std::ofstream oracle_in (oracle_in_filename);
        // Calculate number of clauses and max weight of soft clauses
        int clauses = N + M;
        int sum_weights = N + 1;
        // Write number of variables and clauses and max weight
        oracle_in << "p wcnf " << N << ' ' << clauses << ' ' << sum_weights << std::endl;
        // Write hard clauses for connected families with max weight
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (uv[i][j] == 1) {
                    oracle_in << N + 1 << ' ' << i + 1 << ' ' << j + 1 << " 0\n";
                }
            }
        }
        // Write soft clauses with weight 1 to minimise number of arrests
        for (int i = 0; i < N; i++) {
            oracle_in << 1 << ' ' << -(i + 1) << " 0\n";
        }
        oracle_in.close();
    }

    // O(N) time complexity O(1) space complexity
    void decipher_oracle_answer() {
        std::ifstream oracle_out (oracle_out_filename);
        int vars, soft_sum;
        // Get number of vars and sum of unsatisfied soft clause weights
        oracle_out >> vars >> soft_sum;
        // Read truth value for each var and record families to be arrested
        for (int i = 0; i < vars; i++) {
            int x;
            oracle_out >> x;
            if (x > 0) {
                arrests[x - 1] = 1;
            }
        }
        oracle_out.close();
    }

    // O(N) time complexity O(1) space complexity
    void write_answer() override {
        std::ofstream out (out_filename);
        // Write numbers of families to be arrested
        for (int i = 0; i < N; i++) {
            if (arrests[i] == 1) {
                out << i + 1 << ' ';
            }
        }
        out.close();
        for (int i = 0; i < N; i++) {
            delete [] uv[i];
        }
        delete [] uv;
        delete [] arrests;
    }
};

#endif  // BONUS_H_
