/*
 * Ian Rasmussen
 * 2317200
 * irasmussen@chapman.edu
 * CPSC 380-01
 * Assignment 4 - Thread Synchronization
 */

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#define BUFFER_SIZE 256
#define MEM_SIZE 262144
#define FTOK_FILE "ftok.file"
#define FTOK_ID 1

struct Buffer
{
    long exec;
    char buff[BUFFER_SIZE];
};

pthread_t tid[2];
pthread_mutex_t mutex1;

void *producer(void *arg)
{


    return NULL;
}

void *consumer(void *arg)
{


    return NULL;
}


int main(int argc, char *argv[])
{
    int runLoop = 1;

    if (argc < 4)
    {
        printf("3 arguments as input is required.\n");
        printf("Needed: ./prodCon <Filename> <numItems> <numTimes>\n");
        return -1;
    }

    char *fileName = argv[1];
    int numItems, numTimes; 

    if (atoi(argv[2]) > 0) // Checking if the second argument is an integer > 0
    {
        numItems = atoi(argv[2]);
    }
    else 
    {
        printf("The second argument is not an integer value or inputted a 0.\n");
        return -1;
    }

    if (atoi(argv[3]) > 0) // Checking if third argument is an integer > 0
    {
        numTimes = atoi(argv[3]);
    }
    else
    {
        printf("The third argument is not an integer value or inputted a 0.\n");
        return -1;
    }

    printf("%s\n", fileName);
    printf("%d\n", numItems);
    printf("%d\n", numTimes);


    while (runLoop)
    {

        return 1;
    }

    return 0;
}