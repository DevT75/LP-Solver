//
// Created by devt75 on 25/2/25.
//

#include "Solver.h"
#include <limits>
#include <iostream>
#include <sstream>
#include <ios>
#include <iomanip>

namespace SolverLib{

    void Solver::init(){
        while(1){
            std::cout << "\n=== Linear Optimization Tool ===\n";
            std::cout << "1) Simplex\n";
            std::cout << "2) TSP (not implemented yet)\n";
            std::cout << "3) Exit\n";
            std::cout << "Choose an option: ";

            int choice;
            std::cin >> choice;
            switch(choice){
                case 1:
                    simplex_.initialize();
                    simplex_.solve();
                    break;
                case 2:
                    std::cout << "TSP has'nt been implemented yet!\n";
                    break;
                case 3:
                    std::cout << "Exiting...\n";
                    return;
                default:
                    std::cout << "Invalid Choice, please try again!!\n";
            }

            char op;
            std::cout << "Return to menu?(y/n) : ";
            std::cin >> op;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(op != 'y' && op != 'Y'){
                 std::cout << "Thanks for using me, Bye!!\n";
                 return;
            }
        }
    }

    void Solver::Simplex::initialize(){
        // cout << n << " " << m << endl;
        std::cout << "Enter number of variables (n) : ";
        std::cin >> n;
        std::cout << "Enter number of constraints (m) : ";
        std::cin >> m;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        variables.resize(n + m + 1);
        tableau.resize(m + 1, vector<double>(n + m + 1));
        solution.resize(m + 1);
        int j = 0;
        tableau[0][j] = 1;
        for (j = 1;j <= n;j++) {
            int t;std::cin >> t;
            tableau[0][j] = -t;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        for (int i = 1;i < m + 1;i++) {
            // cout << i + 1 << "\n";
            string s, t;
            getline(std::cin, s);
            std::stringstream ss(s);
            int j = 1;
            while (getline(ss, t, ' ')) {
                if (j > n) {
                    solution[i] = stoi(t);
                    break;
                }
                tableau[i][j++] = stoi(t);
            }
        }

        for (int i = n + 1;i < n + m + 1;i++) {
            tableau[i - n][i] = 1;
        }


        for (int i = 0;i <= n;i++) {
            if (i == 0) {
                mp[i] = "Z";
                continue;
            }
            string t = "X" + std::to_string(i);
            mp[i] = t;
        }

        for (int i = 0;i <= m;i++) {
            if (i == 0) {
                basic_variables[i] = "Z";
                continue;
            }
            string t = "S" + std::to_string(i);
            slack[i] = t;
            mp[n + i] = t;
            basic_variables[i] = t;
        }
    }

    int Solver::Simplex::getEnteringIndex(){
        int index = -1;
        double mini = std::numeric_limits<double>::max();
        for (int i = 1;i < n + m + 1;i++) {
            if (tableau[0][i] < mini) {
                mini = tableau[0][i];
                index = i;
            }
        }
        if (mini >= 0) return -1;
        return index;
    }

    int Solver::Simplex::getLeavingIndex(int enteringIndex){
        double mini = std::numeric_limits<double>::max(), index = -1, dd;
        for (int i = 1;i < m + 1;i++) {
            if (tableau[i][enteringIndex] <= 0) continue;
            if (double ratio = solution[i] / tableau[i][enteringIndex]; ratio < mini) {
                mini = ratio;
                dd = ratio;
                index = i;
            }
        }
//        cout << dd << endl;
        return index;
    }

    void Solver::Simplex::GaussJordanRowOperation(int entering, int leaving) {
        double divisor = tableau[leaving][entering];
        for (int j = 0;j < n + m + 1;j++) {
            tableau[leaving][j] /= divisor;
        }
        solution[leaving] /= divisor;
        for (int i = 0;i < m + 1;i++) {
            if (i == leaving) continue;
            double localCoefficient = tableau[i][entering];
            for (int j = 0;j < n + m + 1;j++) {
                tableau[i][j] = tableau[i][j] - localCoefficient * tableau[leaving][j];
            }
            solution[i] = solution[i] - localCoefficient * solution[leaving];
        }
        basic_variables[leaving] = mp[entering];
    }

    void Solver::Simplex::solve(){
        while(true){
            // find entering variable
            int entering_i = getEnteringIndex();
//            std::cout << entering_i << std::endl;
            if (entering_i == -1) {
                break;
            }
            // find leaving variable
            int leaving_i = getLeavingIndex(entering_i);
            // cout << mp[entering_i] << "\t" << basic_variables[leaving_i] << "\n";

            // swap leaving variable with entering variable
            // and apply Gauss-Jordan Row Operations
            GaussJordanRowOperation(entering_i, leaving_i);
        }

        printTableau();
    }

    void Solver::Simplex::printTableau() {
        for(int i = 0; i < m + 1; i++) {
            if (i == 0) {
                std::cout << "\t";
                for (int j = 0;j <= n + m;j++) std::cout << mp[j] << "\t";
                // for (int j = 1;j <= m;j++) cout << slack[j] << "\t";
                std::cout << "SOLn" << std::endl;
            }
            std::cout << basic_variables[i] << "\t";
            for(const double j : tableau[i]) {
                std::cout << std::setprecision(2) << j << "\t";
            }
            std::cout << solution[i] << std::endl;
        }
    }

}
