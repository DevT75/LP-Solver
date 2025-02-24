#!/bin/bash

#makeAndRun(){
#	if command -v cmake &> /dev/null; then
#		echo "CMake found!!"
#		cmake --version
#	else
#		sudo apt install cmake
#		echo "CMake installed!!"
#		cmake --version
#	fi
	
#	if command -v ninja &> /dev/null; then
#		echo "ninja found!!"
#		ninja --version
#	else
#		sudo apt install ninja-build
#		echo "ninja installed!!"
#		ninja --version
#	fi

#	cd ninja
#	cmake -G Ninja ..
#	ninja
#	./solver
#}


#if [ -d "./ninja" ]; then
#	makeAndRun
#else
#	mkdir ninja
#	makeAndRun
#fi


makeAndRun() {
    # Check for CMake
    if command -v cmake >/dev/null 2>&1; then
        echo -n "CMake found!! "
        cmake --version | head -n 1 | cut -d ' ' -f 3
    else
        echo "Installing CMake..."
        sudo apt install cmake -y || { echo "Failed to install CMake"; exit 1; }
        echo -n "CMake installed!! "
        cmake --version | head -n 1 | cut -d ' ' -f 3
    fi

    # Check for Ninja (unchanged)
    if command -v ninja >/dev/null 2>&1; then
        echo "Ninja found!!"
        ninja --version
    else
        echo "Installing Ninja..."
        sudo apt install ninja-build -y || { echo "Failed to install Ninja"; exit 1; }
        echo "Ninja installed!!"
        ninja --version
    fi

    # Build and run (unchanged)
    if ! cd ninja; then
        echo "Failed to change to ninja directory"
        exit 1
    fi
    cmake -G Ninja .. || { echo "CMake configuration failed"; exit 1; }
    ninja || { echo "Ninja build failed"; exit 1; }
    if [ -f "./solver" ]; then
        ./solver
    else
        echo "Solver executable not found!"
        exit 1
    fi
}

# Main logic (unchanged)
if [ -d "./ninja" ]; then
    makeAndRun
else
    mkdir ninja || { echo "Failed to create ninja directory"; exit 1; }
    makeAndRun
fi
