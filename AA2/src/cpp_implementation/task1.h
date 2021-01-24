// Copyright 2021 Pescaru Tudor-Mihai 321CA

#ifndef TASK1_H_
#define TASK1_H_

#include "task.h"

/*
 * Task1
 * read_problem_data         - read the problem input and store it however you see fit
 * formulate_oracle_question - transform the current problem instance into a SAT instance and write the oracle input
 * decipher_oracle_answer    - transform the SAT answer back to the current problem's answer
 * write_answer              - write the current problem's answer
 */
class Task1 : public Task {
 private:
    int N;                  // Number of mafia families
    int M;                  // Number of family realtions
    int K;                  // Number of available spies
    int **uv;               // Family relation matrix
    int num_vars;           // Number of variables in CNF form
    int *vars;              // Array of spies based on SAT solver answer
    std::string has_sol;    // True/False if problem has solution

 public:
    // O(N^2 + N * K^2 + M) time complexity O(N^2 + N * K) space complexity
    void solve() override {
        read_problem_data();
        formulate_oracle_question();
        ask_oracle();
        decipher_oracle_answer();
        write_answer();
    }

    // O(N^2 + M) time complexity O(N^2) space complexity
    void read_problem_data() override {
        std::ifstream in (in_filename);
        // Read N, M, K
        in >> N >> M >> K;
        // Alocate space for adjacency matrix
        uv = new int*[N];
        for (int i = 0; i < N; i++) {
            uv[i] = new int[N];
        }
        // Initialise adjacency matrix
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                uv[i][j] = 0;
            }
        }
        // Read relations and update adjacency matrix
        for (int i = 0; i < M; i++) {
            int u, v;
            in >> u >> v;
            uv[u - 1][v - 1] = 1;
            uv[v - 1][u - 1] = 1;
        }
        in.close();
    }

    // O(N^2 + N * K^2) time complexity O(1) space complexity
    void formulate_oracle_question() {
        std::ofstream oracle_in (oracle_in_filename);
        // Calculate and write number of variables and clauses
        int variables = N * K;
        int clauses = N + N * (K * (K - 1)) / 2 + K * M;
        oracle_in << "p cnf " << variables << ' ' << clauses << std::endl;
        // Write clauses for at least one spy for every family
        for (int i = 1; i <= N; i++) {
            for (int c = 1; c <= K; c++) {
                int varid = (i - 1) * K + c;
                oracle_in << varid << ' ';
            }
            oracle_in << "0\n";
        }
        // Write cluases for at most one spy for each family
        for (int i = 1; i <= N; i++) {
            for (int c = 1; c <= K; c++) {
                for (int d = c + 1; d <= K; d++) {
                    int varid1 = (i - 1) * K + c;
                    int varid2 = (i - 1) * K + d;
                    oracle_in << -varid1 << ' ' << -varid2 << " 0\n";
                }
            }
        }
        // Write clauses for different spies for connected families
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (uv[i - 1][j - 1] == 1) {
                    for (int c = 1; c <= K; c++) {
                        int varid1 = (i - 1) * K + c;
                        int varid2 = (j - 1) * K + c;
                        oracle_in << -varid1 << ' ' << -varid2 << " 0\n";
                    }
                    uv[i - 1][j - 1] = 0;
                    uv[j - 1][i - 1] = 0;
                }
            }
        }
        oracle_in.close();
    }

    // O(N * K) space-time complexity
    void decipher_oracle_answer() {
        std::ifstream oracle_out (oracle_out_filename);
        // Read if encoding has solution
        oracle_out >> has_sol;
        if (has_sol == "True") {
            // Read number of vars and allocate vetor to store spy numbers
            oracle_out >> num_vars;
            vars = new int[num_vars];
            // Read truth value of each var and get spy number based on var number
            for (int i = 0; i < num_vars; i++) {
                int var;
                oracle_out >> var;
                if (var < 0) {
                    vars[i] = 0;
                } else {
                    int spy = var % K + 1;
                    vars[i] = spy;
                }
            }
        }
        oracle_out.close();
    }

    // O(N * K) time complexity O(1 space complexity)
    void write_answer() override {
        std::ofstream out (out_filename);
        // Write True or False if we have a solution
        out << has_sol << std::endl;
        // If we have a solution write all spy numbers
        if (has_sol == "True") {
            for (int i = 0; i < num_vars; i++) {
                if (vars[i] != 0) {
                    out << vars[i] << ' ';
                }
            }
            delete [] vars;
        }
        out.close();
        for (int i = 0; i < N; i++) {
            delete [] uv[i];
        }
        delete [] uv;
    }
};

#endif  // TASK1_H_
