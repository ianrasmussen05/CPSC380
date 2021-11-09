/*
 * Ian Rasmussen
 * 2317200
 * irasmussen@chapman.edu
 * CPSC 380-01
 * Assignment 5: Virtual Address Manager
 */

#include <stdio.h>
#include <iostream>
#include <string>

#define PAGE_SIZE 256
#define FRAMES 256
#define FRAME_SIZE 256
#define TABLE_SIZE 16
#define ADDRESS 0xFFFF
#define OFFSET 0xFF
#define BUFFER_SIZE 10

// Arrays for the program
int pageTable[PAGE_SIZE];  
int tlb[TABLE_SIZE][2];

// Statistic values
int pageFaults = 0;
int TLBHits = 0;
int countAddresses = 0;

// Files
FILE *backingFile;
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

    // Open backing store file
    // https://www.cplusplus.com/reference/cstdio/fopen/
    backingFile = fopen("BACKING_STORE.bin", "rb");
    if (backingFile == NULL) // Check to see if it is not empty
    {
        std::cout << "There was a problem with the BACKING_STORE.bin file." << std::endl;
        return -1;
    }


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
        int offset;
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

            foundPage = 0;
            frame = 0;
            physicalAddress = 0;

            // Check for page number in TLB array
            for (int i = 0; i < TABLE_SIZE; ++i)
            {
                if (tlb[i][0] == pageNum) // Page is found
                {
                    foundPage = 1; // True
                    TLBHits++;
                    frame = tlb[i][1]; // The second column in the tlb 2D array
                    break;;
                }
            }

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

            physicalAddress = frame * PAGE_SIZE + offset;

            std::string str = std::to_string(physicalAddress); // Convert integer to string
            fputs(str.c_str(), printFile); // Print physical address to the output file

            char nextLine[2] = "\n";
            fputs(nextLine, printFile);
            std::cout << str << std::endl;

            countAddresses++; // Counts the address
        }
    }
    else 
    {
        std::cout << "The file inputted is not correct. Use 'addresses.txt'." << std::endl;
        return -1;
    }


    // Close reading files
    fclose(addressFile);
    fclose(backingFile);


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
        for (int j = 0; j < 2; ++j)
        {
            tlb[i][j] = -1;
        }
    }

    return;
}