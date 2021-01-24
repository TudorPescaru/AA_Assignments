// Copyright 2021 Pescaru Tudor-Mihai 321CA

#ifndef TASK2_H_
#define TASK2_H_

#include "task.h"

/*
 * Task2
 * read_problem_data         - read the problem input and store it however you see fit
 * formulate_oracle_question - transform the current problem instance into a SAT instance and write the oracle input
 * decipher_oracle_answer    - transform the SAT answer back to the current problem's answer
 * write_answer              - write the current problem's answer
 */
class Task2 : public Task {
 private:
    int N;                  // Number of mafia families
    int M;                  // Number of family realtions
    int K;                  // Size of extended family to be found
    int **uv;               // Family relation matrix
    int num_vars;           // Number of variables in CNF form
    int *vars;              // Array of families based on SAT solver answer
    std::string has_sol;    // True/False if problem has solution

 public:
    // O(N^2 * K^2 + M) time complexity O(N^2 * K^2) space complexity
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

    // O(N^2 * K^2) space-time complexity
    void formulate_oracle_question() {
        std::ofstream oracle_in (oracle_in_filename);
        // Store number of variables and initialise counter for clauses
        int variables = N * K;
        int clauses = 0;
        // Store output
        std::string output = "";
        // Write clauses for exactly one family for every position in extended family
        for (int i = 1; i <= K; i++) {
            for (int v = 1; v <= N; v++) {
                int varid = (v - 1) * K + i;
                output += std::to_string(varid);
                output += " ";
            }
            output += "0\n";
            clauses++;
        }
        // Write clauses for each two not connected family cannot be in same extended family
        for (int v = 1; v <= N; v++) {
            for (int w = 1; w <= N; w++) {
                if (uv[v - 1][w - 1] == 0 && v != w) {
                    for (int i = 1; i <= K; i++) {
                        for (int j = i + 1; j <= K; j++) {
                            int varid1 = (v - 1) * K + i;
                            int varid2 = (w - 1) * K + j;
                            output += std::to_string(-varid1);
                            output += " ";
                            output += std::to_string(-varid2);
                            output += " 0\n";
                            clauses++;
                        }
                    }
                }
            }
        }
        // Write clauses for every two positions in the extended family, the families are different
        for (int i = 1; i <= K; i++) {
            for (int j = i + 1; j <= K; j++) {
                for (int v = 1; v <= N; v++) {
                    int varid1 = (v - 1) * K + i;
                    int varid2 = (v - 1) * K + j;
                    output += std::to_string(-varid1);
                    output += " ";
                    output += std::to_string(-varid2);
                    output += " 0\n";
                    clauses++;
                }
            }
        }
        // Write clauses for two different families cannot have same position in same extended family
        for (int i = 1; i <= K; i++) {
            for (int v = 1; v <= N; v++) {
                for (int w = v + 1; w <= N; w++) {
                    int varid1 = (v - 1) * K + i;
                    int varid2 = (w - 1) * K + i;
                    output += std::to_string(-varid1);
                    output += " ";
                    output += std::to_string(-varid2);
                    output += " 0\n";
                    clauses++;
                }
            }
        }
        // Write entire output
        oracle_in << "p cnf " << variables << ' ' << clauses << std::endl;
        oracle_in << output;
        oracle_in.close();
    }

    // O(N * K) space-time complexity
    void decipher_oracle_answer() {
        std::ifstream oracle_out (oracle_out_filename);
        // Read if encoding has solution
        oracle_out >> has_sol;
        if (has_sol == "True") {
            // Read number of vars and allocate space to store family numbers
            oracle_out >> num_vars;
            vars = new int[num_vars];
            // Read truth value of each var an get family number based on var number
            for (int i = 0; i < num_vars; i++) {
                int var;
                oracle_out >> var;
                if (var < 0) {
                    vars[i] = 0;
                } else {
                    int spy = (var - 1) / K + 1;
                    vars[i] = spy;
                }
            }
        }
        oracle_out.close();
    }

    // O(N * K) time complexity O(1) space complexity
    void write_answer() override {
        std::ofstream out (out_filename);
        // Write True or False if we have a solution
        out << has_sol << std::endl;
        // If we have a solution write all family numbers
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

#endif  // TASK2_H_
