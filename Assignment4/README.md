# Assignment 4 - Thread Synchronization

This C program creates two threads, where the first thread is the consumer and consumes the data written to a shared memory buffer. The second thread is the producer that produces the data for the shared memory buffer. Meaning that the consumer reads from the shared memory and the producer writes to the memory. It uses a mutex semaphore and counting semaphore to prevent race conditions.

* Ian Rasmussen
* 2317200
* irasmussen@chapman.edu
* CPSC 380-01

## Source Files
* prodcon.c
* MakeFile

## Known Errors
* The error checking in this program works for the inputs.
* However, the program will not complete its calculations and seems to run forever.
* I am unsure to why it is not working as I thought I had all the checksum calculations correct.
* Also, when using the Makefile, I get a warning about the checksum not linking correctly. I do not know why.

## References
* Got some of the code from the shm zip file from class.
* To find out how to allocate memory in C: https://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm 

## Execute Program
* make
* ./prodcon (keyfile) (number of items) (number of times)

## Clean Directory
* make clean