# Assignment 2: Simple Shell Interface

This program creates a simple shell to read user input in a continuous loop. It then forks a child process to handle the input. The child process will run a basic Unix command to process the user input. If the command entered included a ‘&’ at the end of the user input, then the parent should wait until the child finishes its tasks. The user can exit the program when entering ‘quit’ or ‘exit’ as a command.

* Name: Ian Rasmussen
* Student ID: 2317200
* Email: irasmussen@chapman.edu
* Course: CPSC 380-01
* Assignment: Assignment 2

## Source Files:
* sshell.cpp
* Makefile

## Resources:
* Went to office hours to get help on forking the program.

## Code Limitations:
* None

## Build Program:
* make
* or g++ sshell.cpp -o sshell

## Execute Program:
* ./sshell