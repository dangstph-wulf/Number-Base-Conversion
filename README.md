
# CS 3503 Assignment 1 - Number Base Conversion

## Author
[Stephen Dang]

## Description
My personal implementation of a number base conversion system written in C using Visual Studio Code. It converts a 32-bit unsigned integer data by passing it through either a division conversion or a subtraction conversion into binary, decimal, octal, and hexadecimal. 

## Build Instructions

### Prerequisites
- gcc (MinGW or MSYS2) on Windows
- All source files (`main.c`, `convert.c`, `convert.h`) within the same folder

### Build
Open a terminal in your project directory and run:
```bash
gcc convert.c main.c -o Assignment1
```
This will create an executable named `Assignment1.exe`.

### Run
To run the program:
```
Assignment1
```
Included in the repo is template document called `a1_test_file` which contains the tests that need to be put within a separate .txt called `A1_tests.txt`.

Make sure `A1_tests.txt` is in the same directory as the executable.

### Output
Results will be written to `output.txt` in the same directory.

## Test Results
[Summary: 100/100 tests passed]

## Notes
[This was my first major project in Visual Studio Code and also my introduction to C. Coming from coding in primarily Java, it was a challenge trying to learn all the new syntax that came with C, as well as just learning the new IDE in general.]
