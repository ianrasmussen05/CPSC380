/*
 * Ian Rasmussen
 * 2317200
 * irasmussen@chapman.edu
 * CPSC 380-01
 * Assignment 1
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string>
extern int errno;

#define NRECORDS 100
typedef struct {
	int   integer;
	char  string[24];
} RECORD;


int main(int argc, char *argv[])
{    
    // These will be the two numbers/inputs the user will put in by the console or input
    char* value1;
    char* value2;

    if (argc == 3)
    {
        value1 = argv[1];
        value2 = argv[2];

        if (atoi(value1) >= 0 && atoi(value1) < 100) {} // Checks to see if first input is between 0 and 99
        else 
        {
            printf("You must enter a value between 0 and 99 for the first argument.\n");
            return 1;
        }
    }
    else if (argc == 2 || argc > 3) // If the user only puts one number in the terminal
    {
        printf("Invalid Input:\nMust have two values inputed in the terminal.\n");
        return 1;
    }
    else // If the user chooses to be prompted within the program
    {
        // These are temporary values so the inputted values are correct
        char tempValue1[24];
        char tempValue2[24];

        printf("Enter the first number: ");

        // Used this link to use scanf: 
        // https://stackoverflow.com/questions/37921081/scanf-a-string-in-a-char-pointer
        scanf("%s", tempValue1);

        // Checking to see if the user inputted valid numbers
        while (atoi(tempValue1) < 0 || atoi(tempValue1) >= 100)
        {
            printf("\nPlease enter the correct value (0-99): ");
            scanf("%s", tempValue1);
        }

        printf("Enter the second number: ");
        scanf("%s", tempValue2);

        value1 = tempValue1;
        value2 = tempValue2;
    }

    FILE *file = NULL;
    file = fopen("records.dat", "wb");

    if (file == NULL) // Catch any errors when opening file
    {
        printf("Error: %d\n", errno);
        perror("Program");
        return 1;
    }

    //RECORD allRecords[NRECORDS]; // I tried to use the struct at first, did not do this
    
    for (int num = 0; num < NRECORDS; ++num)
    {
        std::string strNum;
        if (num < 10)
        {
            strNum = std::to_string(num) + " ";
        }
        else 
        {
            strNum = std::to_string(num);
        }

        // The string size will be a maximum of 10 characters
        std::string str = "RECORD-" + strNum + "\n";
        int output = fwrite(&str, sizeof(str), 1, file);

        if (output != 1)
        {
            printf("Error: %d\n", errno);
            perror("Program");
            return 1;
        }        
    }

    fclose(file); // Close file

    // Open the same file again, this time to change it
    file = fopen("records.dat", "w+");

    if (file == NULL) // Catch any errors when opening file
    {
        printf("Error: %d\n", errno);
        perror("Program");
        return 1;
    }

    // Used this reference for fseek and fputs: https://www.cplusplus.com/reference/cstdio/fseek/
    fseek(file, 10 * sizeof(value1), SEEK_SET); // Try to get size of each line (10) and multiply that by first value inputed
    fputs(value2, file); // Both of these functions fail to do what I want it to do

    fclose(file); // Close it one last time

    printf("Completed!\n");

    return 0;
}