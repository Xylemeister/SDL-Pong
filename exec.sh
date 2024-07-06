#!/bin/bash

# Function to build the project
build() {
    make
}

# Function to clean the build directory
clean() {
    make clean
}

# Function to run the program
run() {
    if [ -f bin/MyProject ]; then
        ./bin/MyProject
    else
        echo "Executable not found. Build the project first."
    fi
}

# Check the first argument and perform the corresponding action
case "$1" in
    clean)
        clean
        ;;
    *)
        clean
        build
        run
        ;;
esac