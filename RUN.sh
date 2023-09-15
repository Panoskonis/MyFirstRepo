#!/bin/bash

# Compile your C program
gcc main.c Functions.c -o Graph.exe

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."

    # Run your C program
    ./Graph.exe

else
    echo "Compilation failed."
fi
