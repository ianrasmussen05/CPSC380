#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <iostream>
#include <string>

#define PAGE_SIZE 256
#define FRAMES 256
#define FRAME_SIZE 256
#define TABLE_SIZE 16

int main (int argc, char* argv[])
{
    // Checks to see if there are the correct number of inputs
    if (argc < 2)
    {
        std::cout << "Enter a file to read from in the command line." << std::endl;
        return -1;
    }

    std::string fileName = argv[1];

    FILE *file;
    file = fopen(fileName, "r"); // Open file and read from it.

    if (file != NULL) // There are contents within the file
    {
        // Now we must read each line
        char *line = NULL;
        int readResult;

        readResult = fread(line, sizeof(char), PAGE_SIZE, file);



        free(line); // Free the memory of this variable
    }
    else 
    {
        std::cout << "The file inputted is empty. Enter the correct file." << std::endl;
        return -1;
    }


    fclose(file);

    return 0;
}