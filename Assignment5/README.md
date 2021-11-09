# Assignment 5 - Virtual Address Manager

This program will read from a file containing logical addresses and, uses a TLB as well as a page table. This will then translate each logical address to its corresponding physical address and output the value of the byte stored at the translated physical address.

* Ian Rasmussen
* 2317200
* irasmussen@chapman.edu
* CPSC 380-01
* Assignment 5

## Source Files
* vmmgr.cpp
* addresses.txt
* output.txt
* Makefile

## Code Limitations
* I am currently getting a segmentation fault in my code. When I do not set both the tbl and pageTable arrays to -1 in each cell, I do not get this error and I am able to see contents in the output.txt file.

## Resources
* I used geeksforgeeks in finding how to use fopen(), fgets(), and fputs().
* Used in class examples for the offset and getting page number.

## Build and Execute
Using Makefile:
* make
* ./vmmgr addresses.txt

Using command line:
* g++ vmmgr.cpp -o vmmgr
* ./vmmgr addresses.txt