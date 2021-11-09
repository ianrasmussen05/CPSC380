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
* 

## Resources
* This is where I found to read line-by-line: https://www.delftstack.com/howto/c/read-file-c/
* 

## Build and Execute
Using Makefile:
* make
* ./vmmgr addresses.txt

Using command line:
* g++ vmmgr.cpp -o vmmgr
* ./vmmgr addresses.txt