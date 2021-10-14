/* 
 * Ian Rasmussen
 * 2317200
 * irasmussen@chapman.edu
 * CPSC 380-01
 * Assignment 3
 * msgqReceive.cpp
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
        
    // read command from message queue then call the system ( ) function to execute the system command. 
    // Break out of loop if ‘quit’ or ‘exit’ is read from the queue then exit program **/
	}

	return 0;
}
