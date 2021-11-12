/*
 * Ian Rasmussen
 * 2317200
 * irasmussen@chapman.edu
 * CPSC 380-01
 * Assignment 5: Virtual Address Manager
 */

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <iostream>
#include <string>

#define PAGE_SIZE 256
#define FRAME_SIZE 256
#define TABLE_SIZE 16
#define ADDRESS 0xFFFF
#define OFFSET 0xFF
#define BUFFER_SIZE 10

// Done in office hours
typedef struct {
    short pageNum; 
    short frameNum;
} TLB;


// Arrays for the program
int pageTable[PAGE_SIZE]; // set table to -1
TLB tlb[TABLE_SIZE]; // Set page table to -1
char physicalMemory[PAGE_SIZE * FRAME_SIZE];

// Statistical values
int pageFaults = 0;
int TLBHits = 0;
int countAddresses = 0;

// Files
int backingFile;
FILE *addressFile;
FILE *printFile;

// Values to input from reading from a file
char buff[BUFFER_SIZE];
int logicalAddress;

void setArrays();

int main (int argc, char* argv[])
{
    // Checks to see if there are the correct number of inputs
    if (argc < 2)
    {
        std::cout << "Enter a file to read from in the command line." << std::endl;
        return -1;
    }
    char *fileName = argv[1];

    int pntr;

    // Open backing store file
    // https://www.cplusplus.com/reference/cstdio/fopen/
    backingFile = open("BACKING_STORE.bin", O_RDONLY);
    if (backingFile == -1) // Check to see if it is not empty
    {
        //errno later
        std::cout << "Error opening/reading the BACKING_STORE.bin file." << std::endl;
        return -1;
    }

    // Map Backing store file into shared memory using mmap
    pntr= mmap(0, PAGE_SIZE * FRAME_SIZE, PROT_READ, MAP_PRIVATE, backingFile, 0);

    printFile = fopen("output.txt", "w+");
    if (printFile == NULL)
    {
        std::cout << "Error opening the output.txt file." << std::endl;
        return -1;
    }
    
    
    addressFile = fopen(fileName, "r"); // Open file and read from it.
    if (addressFile != NULL) // There are contents within the file
    {
        // Create new variables while initializing a few of them
        int pageNum;
        off_t offset;
        int foundPage;
        int frame;
        int physicalAddress;
        int lineNum = 0;


        setArrays(); // Set the contents of the arrays to -1.


        // Got fgets from https://www.cplusplus.com/reference/cstdio/fgets/ 
        // Gets each line in the file and puts it into the buffer
        while (fgets(buff, BUFFER_SIZE, addressFile) != NULL)
        {
            logicalAddress = atoi(buff); // Convert the char buffer to int

            // These were done in class
            pageNum = logicalAddress & ADDRESS;
            pageNum = pageNum >> 8;
            offset = logicalAddress & OFFSET;

            //Substitute other code below
            /*
                //Loop on read address file, one at a time
                //get logical address from file
                //Calculate offsets (like above)
                //get page number

                search tlb if page number exists
                (if page number exists, then increment page hit
                    else check to see if page table has it, if not pageFault++, get free page.

                    copy from backing file into main memory
                    (memcpy(physicalMemory+frameNum*pageSize, pntr+pageNum*pageSize, pageSize))
                    update page table

                    update/add tlb)


                Get actual values
                (value = physicalMemory[frameNum*pageSize+offset])
                print out main memory value

                Outside loop: statistics

            */



            // Initialize more variables within the while loop
            foundPage = 0;
            frame = 0;
            physicalAddress = 0;



            // Create an function to insert something into frame table (FIFO/LRU)
            // Create function to search TLB
            // Check for page number in TLB array
            for (int i = 0; i < TABLE_SIZE; ++i)
            {
                
                if (tlb[i].pageNum == pageNum) // Page is found
                {
                    foundPage = 1; // True
                    TLBHits++;
                    frame = tlb[i].frameNum; // The second column in the tlb 2D array
                    break;;
                }
            }

            /*
            if (foundPage != 1)
            {
                int temp = 0;
                int i;
                
                // Check for page number in page table array
                for (i = 0; i < PAGE_SIZE; ++i)
                {
                    // Page is found
                    if (pageTable[i] == pageNum)
                    {
                        frame = i;
                        pageFaults++;
                        break;
                    }

                    // Page is not found and is not previously inputted a page number
                    if (pageTable[i] == -1)
                    {
                        pageTable[i] = pageNum;
                        frame = i;
                        break;
                    }
                }

                tlb[lineNum][0] = pageNum;
                tlb[lineNum][1] = i;
                lineNum++;
            }

            // Current frame * the page size in bytes (256) + the offset of the local address (0xFF)
            physicalAddress = frame * PAGE_SIZE + offset;

            // Printing the lines to the output.txt file and command line
            std::string str = std::to_string(physicalAddress); // Convert integer to string
            fputs(str.c_str(), printFile); // Print physical address to the output file

            char nextLine[2] = "\n";
            fputs(nextLine, printFile);
            std::cout << str << std::endl;

            countAddresses++; // Counts the address each while loop iteration
            */
        }
    }
    else 
    {
        std::cout << "The file inputted is not correct. Use 'addresses.txt'." << std::endl;
        return -1;
    }


    // Close reading files
    fclose(addressFile);
    close(backingFile);


    // Statistics
    double faultRate = 0;
    double hitRate = 0;

    faultRate = (pageFaults / (double) countAddresses) * 100;
    hitRate = (TLBHits / (double) countAddresses) * 100;

    // Printing statistics
    std::string faultStr = "The fault rate is: " + std::to_string(faultRate) + "%.";
    std::string hitStr = "The hit rate is: " + std::to_string(hitRate) + "%.";
    char nextLine[2] = "\n";

    fputs(faultStr.c_str(), printFile);
    fputs(nextLine, printFile);
    fputs(hitStr.c_str(), printFile);

    std::cout << faultStr << std::endl;
    std::cout << hitStr << std::endl;

    // Close print file
    fclose(printFile);

    return 0;
}

void setArrays()
{
    for (int i = 0; i < PAGE_SIZE; ++i)
    {
        pageTable[i] = -1;
    }

    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        tlb[i].frameNum = -1;
        tlb[i].pageNum = -1;
    }

    return;
}