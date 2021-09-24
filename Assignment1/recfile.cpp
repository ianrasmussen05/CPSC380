// Use perror() to error check later in the program

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
typedef struct 
{
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
        //consoleInput(argv[1], argv[2]); // I was thinking about using other functions, but did not work out that way
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

        //userInput(); // Use of other function, didn't work out
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

    // Checks to see if my values are good
    printf("\nThe first value is %s \nThe second value is %s \n", value1, value2); 

    // int file;
    //file = open("records.dat", O_CREAT | O_WRONLY); // Opens the file
    FILE *file;
    file = fopen("records.dat", "w");

    if (file == NULL) // Catch any errors when opening file
    {
        printf("Error: %d\n", errno);
        perror("Program");
        return 1;
    }

    for (int num = 0; num < NRECORDS; ++num)
    {
        //fwrite()
    }

    fclose(file);
    /*
    if (close(file) < 0) // Close the file
    {
        printf("Error: %d\n", errno);
        perror("Program");
        return 1;
    }
    */

    return 0;
}