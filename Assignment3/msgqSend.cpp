/* 
 * Ian Rasmussen
 * 2317200
 * irasmussen@chapman.edu
 * CPSC 380-01
 * Assignment 3
 * msgqSend.cpp
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <string>

#define MAX_LINE 80 // 80 chars per line, per command

struct msgbuf {
    long mtype;
    char mtext[MAX_LINE];
};

int main(int argc, char *argv[])
{
    key_t  key;  	// message queue key
   	int should_run = 1;
	
	key = ftok(argv[1], ‘q’);

	// Create/attach message queue using key
		
    while (should_run) 
    {   
        printf("msgq>");
        fflush(stdout);
        
        // read command from stdin then send command to message queue 
        // Break out of loop if user types ‘quit’ or ‘exit’ then delete the message queue and exit program
	}

	return 0;
}
