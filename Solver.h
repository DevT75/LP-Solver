//
// Created by devt75 on 25/2/25.
//

#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <string>
#include <map>

using std::vector;
using std::string;
using std::map;

namespace SolverLib{ // namespace for solver
    class Solver { // main class containing the optimization technique classes
        public:
            Solver() = default;
            void init();
        private:
            class Simplex{
                public:
                    Simplex() = default;
                    void solve();
                    void initialize();
                private:
                    int n,m;
                    bool solved_ = false;
                    vector<string> variables;
                    vector<vector<double>> tableau;
                    vector<double> solution;
                    map<int, string> basic_variables, mp, slack;
                    void printResult();
                    void printTableau();
                    int getEnteringIndex();
                    int getLeavingIndex(int enteringIndex);
                    void GaussJordanRowOperation(int enteringIndex, int leavingIndex);

            };
        // Add more in future
        Simplex simplex_;
    };
}



#endif //SOLVER_H
