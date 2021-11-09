#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <alloca.h>
#include <sys/stat.h>
#include <sys/mman.h>
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
int pageTableNumbers[PAGE_SIZE];
int pageTableFrames[PAGE_SIZE];   
int TLBPageNumber[TABLE_SIZE];  
int TLBFrameNumber[TABLE_SIZE]; 
int physicalMemory[FRAME_SIZE][FRAMES];

// Statistic values
int pageFault = 0;
int TLBHits = 0;

// Files
FILE *backingFile;
FILE *addressFile;

// Values to input from reading from a file
char buff[BUFFER_SIZE];
int logicalAddress;

int main (int argc, char* argv[])
{
    // Checks to see if there are the correct number of inputs
    if (argc < 2)
    {
        std::cout << "Enter a file to read from in the command line." << std::endl;
        return -1;
    }
    char *fileName = argv[1];

    // https://www.cplusplus.com/reference/cstdio/fopen/
    backingFile = fopen("BACKING_STORE.bin", "rb");

    if (backingFile == NULL)
    {
        std::cout << "There was a problem with the BACKING_STORE.bin file." << std::endl;
        return -1;
    }

    addressFile = fopen(fileName, "r"); // Open file and read from it.

    if (addressFile != NULL) // There are contents within the file
    {
        // Now we must read each line
        char buffer[256];
        int readResult;
        size_t len = 0;
        ssize_t read;

        // Seek to the beginning of the file
        if(fseek(addressFile, 0, SEEK_SET) < 0)
        {
            printf("Error seeking file: %d\n", errno);
            return -1;
        }

        // The next lines are from: https://www.delftstack.com/howto/c/read-file-c/ 
        struct stat statObject;
        if (stat(fileName, &statObject) < 0)
        {
            printf("Error when creating file contents: %d\n", errno);
            return -1;
        }

        char *fileContents = (char*) malloc(statObject.st_size);
        readResult = fread(fileContents, statObject.st_size, 1, addressFile);

        if (readResult < 0)
        {
            printf("Error reading the file: %d\n", errno);
            return -1;
        }

        std::cout << fileContents << std::endl;



        free(fileContents); // Free the memory of this variable
    }
    else 
    {
        std::cout << "The file inputted is empty. Enter the correct file." << std::endl;
        return -1;
    }


    fclose(addressFile);
    fclose(backingFile);

    return 0;
}