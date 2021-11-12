/*
 * Ian Rasmussen
 * 2317200
 * irasmussen@chapman.edu
 * CPSC 380-01
 * Assignment 5: Virtual Address Manager
 */

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>

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

    signed char *pntr;

    // Open backing store file
    // https://www.cplusplus.com/reference/cstdio/fopen/
    backingFile = open("BACKING_STORE.bin", O_RDONLY);
    if (backingFile == -1) // Check to see if it is not empty
    {
        printf("Error opening 'BACKING_STORE.bin' file. Error number: %d", errno);
        return -1;
    }
 
    // Map Backing store file into shared memory using mmap
    pntr = (signed char*) mmap(0, PAGE_SIZE * FRAME_SIZE, PROT_READ, MAP_PRIVATE, backingFile, 0);
    
    
    addressFile = fopen(fileName, "r"); // Open file and read from it.
    if (addressFile != NULL) // There are contents within the file
    {
        // Create new variables while initializing a few of them
        int pageNum;
        off_t offset;
        int foundPage;
        int frame;
        int physicalAddress;
        int finalValue;
        int lineNum = 0;
        int tlbSize = 0;
        int currTBL = 0;


        setArrays(); // Set the contents of the arrays to -1.


        // Got fgets from https://www.cplusplus.com/reference/cstdio/fgets/ 
        // Gets each line in the file and puts it into the buffer
        while (fgets(buff, BUFFER_SIZE, addressFile) != NULL)
        {
            logicalAddress = atoi(buff); // Convert the char buffer to int
            //std::cout << "Logical Address: " << logicalAddress << std::endl;

            // These were done in class
            pageNum = logicalAddress & ADDRESS;
            pageNum = pageNum >> 8;
            offset = logicalAddress & OFFSET;
            
            int foundPage = 0;
            int i = 0;
            for (i = 0; i < TABLE_SIZE; ++i)
            {
                // The page is found
                if (tlb[i].pageNum == pageNum)
                {
                    TLBHits++;
                    foundPage = 1;
                    frame = tlb[i].frameNum;
                    break;
                }
            }

            // Page is not found in tbl array, must check in page table
            if (foundPage != 1)
            {
                // Page number in page table is found
                if (pageTable[pageNum] != -1)
                {
                    std::cout << "Hit on page: " << pageNum << std::endl;
                    physicalAddress = frame;
                }
                else 
                {
                    // Copy memory from BACKING_STORE.bin file into main memory
                    // Got it from office hours
                    memcpy(physicalMemory + (frame * PAGE_SIZE), pntr + (pageNum * PAGE_SIZE), PAGE_SIZE);
                    physicalAddress = frame;

                    // Update page table
                    pageTable[pageNum] = physicalAddress;
                    pageFaults++;
                }

                // Update tbl
                if (tlbSize < TABLE_SIZE)
                {
                    // Set values created above into tlb
                    tlb[currTBL].frameNum = frame;
                    tlb[currTBL].pageNum = pageNum;
                    tlbSize++;
                    currTBL++;
                }
                else // Table is full, do FIFO or LRU
                {
                    




                    
                }
            }

            finalValue = physicalMemory[physicalAddress * PAGE_SIZE + offset];

            std::cout << "Virtual Address: " << logicalAddress << "\nPhysical Address: " << physicalAddress <<
                         "\nValue: " << finalValue << std::endl;


            countAddresses++;        
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
    double faultRate = (pageFaults / (double) countAddresses) * 100;
    double hitRate = (TLBHits / (double) countAddresses) * 100;

    // Printing statistics
    std::string faultStr = "The fault rate is: " + std::to_string(faultRate) + "%.";
    std::string hitStr = "The hit rate is: " + std::to_string(hitRate) + "%.";
    char nextLine[2] = "\n";

    std::cout << faultStr << std::endl;
    std::cout << hitStr << std::endl;
    

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