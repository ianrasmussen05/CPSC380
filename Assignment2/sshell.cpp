#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
extern int errno;

#define MAX_LINE 80 /* 80 chars per line, per command */

int main(void)
{
    char *args[MAX_LINE/2 + 1];	/* max of 40 arguments */
   	int should_run = 1;
	
	int i, upper;
		
    while (should_run) 
    {   
    	printf("osh>");
		fflush(stdout);
        
    /** fork a child to execute command (using one of the exec calls)
     Break out of loop if user types ‘quit’ or ‘exit’ then exit   program **/
   	}
    
	return 0;
}
