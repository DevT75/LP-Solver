# LP-Solver

A command-line tool for solving linear optimization problems using techniques like the Simplex method. Built in C++ as a learning project to explore optimization algorithms and class-based design.

## Description

LP-Solver is designed to take user input for linear programming problems (e.g., objective functions and constraints) and solve them interactively. Currently, it supports the Simplex method for maximization problems with `<=` constraints, with plans to add Transportation problems and Network Models support in the future.

## Features

- Interactive menu to choose solvers (Simplex, (TP, NM placeholder)).
- Take coefficient as input, (Parsing equations like `max 3x1 + 4x2` and constraints like `x1 + x2 <= 5` is pending).
- Displays the Simplex tableau and results for simplex.
- Modular C++ design with CMake and Ninja build system.

## Prerequisites

- **C++ Compiler**: g++ or clang++ (C++17 support required).
- **CMake**: Version 3.10 or higher.
- **Ninja**: Version 1.10.1 or higher
- **Operating System**: Tested on Linux (e.g., Ubuntu); should work on macOS/Windows with minor adjustments.

## Installation

1. **Clone or Download**:
    - If on GitHub: `git clone https://github.com/DevT75/LP-Solver.git`
    - Or copy the project folder to your machine.


2. **Setting Up the Project**:
   - Give permission to `run.sh` by `chomod +x run.sh`
   - Run the script