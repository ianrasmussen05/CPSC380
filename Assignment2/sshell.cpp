#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
extern int errno;

#define MAX_LINE 80     /* 80 chars per line, per command */

int main(void)
{
	char *args[MAX_LINE/2 + 1];	/* max of 40 arguments */
	char quitStr[8] = "quit";
	char exitStr[8] = "exit";
	char userInput[8];
	char* ptr1 = quitStr;
	char* ptr2 = exitStr;
	char* ptr3 = userInput;

	printf("Type '%s' or '%s' to leave the program.\n", quitStr, exitStr);
	
	bool firstLoop = true;
	
	printf("osh> ");
	scanf("%s", userInput);
		
    while (true)
	{
		if(strcmp(ptr3, ptr1) == 0) // Checks to see if the user inputted "quit"
		{
			printf("Exiting...\n");
			return 1;
		}
		else if (strcmp(ptr3, ptr2) == 0) // Checks to see if the user inputted "exit"
		{
			printf("Exiting...\n");
			return 1;
		}
		else // User enters a command
		{
			fflush(stdout);

			/** fork a child to execute command (using one of the exec calls)
			Break out of loop if user types ‘quit’ or ‘exit’ then exit   program **/
			pid_t fk = fork();

			if (fk < 0) // Did not work correctly
			{
				perror("Fork\n");
				return 1;
			}
			else if (fk == 0) // This is the child
			{
				printf("4\n");
			}
			else // This is the parent
			{
				printf("10\n");

				// If the input has a '&' in it, then we wait for the child
				wait(nullptr);
			}

			printf("osh> ");
			scanf("%s", userInput);
		}
	}
    
	return 0;
}
