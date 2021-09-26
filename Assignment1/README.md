# Assignment 1: System Calls - File I/O

In this program, the user can either input the two needed numbers in the terminal, or they can be prompted within the 
program itself. It will be printing to 'records.dat' all the Records with the corresponding ID. If the file does not 
exist, it will create it and from there, the program will make a system call to search for the specific location in 
memory to change a record. Again, printing that to a file.

In my previous commits to github, I have older versions of what I did to open/close the file.

* Name: Ian Rasmussen
* Student ID: 2317200
* Email: irasmussen@chapman.edu
* Course: CPSC 380-01
* Assignment: Assignment 1

## Source Files:
* records.dat
* recfile.cpp

## Resources:
* Cited many of the links I used in my 'recfile.cpp' file.

## Code Limitations:
The code does compile but:
* I do not have the output correct on the file. I get these symbols in the 'records.dat' file that I could not figure out how to get rid of. 
* Had many troubles with the fseek() and fput() functions at the bottom of the file. Again, printing the unexpected results.

## Build Program:
* make

## Execute Program:
* ./recfile
* or ./recfile (num1) (num2)