// Use perror() to error check later in the program

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NRECORDS 100
typedef struct {
	int   integer;
	char  string[24];
} RECORD;


int main(int argc, char *argv[])
{    
    for(int arg = 0; arg < argc; ++arg) 
    {        
        if(argv[arg][0] == '-')      
        {      
            printf("option: %s\n", argv[arg]+1);        
        }
        else            
        {
            printf("argument %d: %s\n", arg, argv[arg]);  
        }  
    }    

    return 0;
}