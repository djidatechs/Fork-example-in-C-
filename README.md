# Fork command example in C

## Problem
Compiling a c file and then link editing the object file with fork and execl commands

## Implementation
This implementation uses fork() and execl().

## What it does

- The program takes the file name as an argument, and checks if the file is a valid C file with the extension `.c`.
- If the file is valid, the program creates two child processes using `fork()`. The first process compiles the C file to an object file. The second process links the object file to create an executable file.
- Finally, the program executes the executable file.

## Requirements
- GCC compiler

## Note

This program is just a simple example, and may not be suitable for more complex C projects.

