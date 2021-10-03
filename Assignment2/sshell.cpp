/*
 * Ian Rasmussen
 * 2317200
 * irasmussen@chapman.edu
 * CPSC 380-01
 * Assignment 2
 */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	std::string currLine;

	std::cout <<"Type 'quit' or 'exit' to leave the program." << std::endl;
	
	while (true)
	{
		printf("osh> ");
		fflush(stdout);

		std::cin >> currLine; // Gets user input

		if((currLine == "exit") || (currLine == "quit")) // Checks to see if the user inputted "quit"
		{
			std::cout << "Exiting..." << std::endl;
			return -1; // This returns -1 because any other input (0 or 1) does not work
		}
		else // User enters a valid command
		{
			pid_t fk = fork(); // Fork the program

			if (fk < 0) // Did not work correctly
			{
				perror("Fork Error\n");
				return 1;
			}
			else if (fk == 0) // This is the child
			{
				// I got this from Office hours on Saturday
				execlp(currLine.c_str(), currLine.c_str(), NULL);
			}
			else // This is the parent
			{
				sleep(1);
				// If the input has a '&' in it, then we wait for the child
				// Always found at the end of the user input
				if (currLine[currLine.length() - 1] == '&')
				{
					wait(NULL);
				}
			}
		}
	}
    
	return 0;
}
