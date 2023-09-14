#!/bin/bash

# Compile your C program
gcc main.c Functions.c -o Graph.exe

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."

    # Run your C program
    ./Graph.exe

    # Check if the program exited successfully
    if [ $? -eq 0 ]; then
        
        dot -Tpng Test.dot -o output.png 
        dot -Tpng Test1.dot -o output1.png 
    else
        echo "Program execution failed."
    fi
else
    echo "Compilation failed."
fi
