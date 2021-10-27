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
#include <semaphore.h>

#define BUFFER_SIZE 32
#define RAND_DATA 256

int memSize, numItems, numTimes;
unsigned short cksum1, cksum2;
char *fileName = "nothing.txt";
char *memory;
pthread_t tid[2];
sem_t sem[2]; // 2 semaphores for 2 threads
pthread_mutex_t m_mutex;

void *producer(void *arg)
{
    // Number of times to write from the shared buffer
    for (int i = 0; i < numTimes; ++i)
    {
        // Got how to use sem_wait and sem_post here: https://stackoverflow.com/questions/15182328/semaphore-implementation
        sem_wait(&sem[0]); // Uses the first semaphore for writing

        // Number of buffers within memory
        for (int j = 0; j < numItems; ++j)
        {
            // How to use mutex locks: https://www.man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html
            pthread_mutex_lock(&m_mutex);

            cksum1 = 0;

            // This is where we write the data
            // Go to specific spot in memory minus the last two spots within the buffer for checksum
            for (int k = j * BUFFER_SIZE; k < ((j + 1) * BUFFER_SIZE) - 2; ++k)
            {
                memory[k] = rand() % RAND_DATA;
                cksum1 += memory[k]; // This calculates the first checksum
            }

            // Got the next lines from the shmwrite.c file used in class
            cksum1 = checksum(&memory[0], BUFFER_SIZE - 2); 
            memcpy(&memory[BUFFER_SIZE-2], &cksum1, 2);

            // Unlocks the mutex to go to the next semaphore
            pthread_mutex_unlock(&m_mutex);
        }
        
        sem_post(&sem[1]); // Switch to second semaphore
    }

    return NULL;
}

void *consumer(void *arg)
{
    // Number of times to write from the shared buffer
    for (int i = 0; i < numTimes; ++i)
    {
        // Got how to use sem_wait and sem_post here: https://stackoverflow.com/questions/15182328/semaphore-implementation
        sem_wait(&sem[1]); // Have this go for the second semaphore, reads data

        // Number of buffers within memory
        for (int j = 0; j < numItems; ++j)
        {
            pthread_mutex_lock(&m_mutex); // Locks the thread in the data space

            cksum2 = 0;

            // This is where it reads from memory
            // Go to specific spot in memory minus the last two spots within the buffer for checksum
            for (int k = j * BUFFER_SIZE; k < ((j + 1) * BUFFER_SIZE) - 2; ++k)
            {
                cksum2 += memory[k]; // This calculates the next checksum
            }

            // Got these next few lines from the shm.zip folder in the shmread.c file
            if (cksum1 != cksum2)
            {
                printf("Checksum mismatch: expected %02x, received %02x \n", cksum2, cksum1);
                exit(0);
            }

            pthread_mutex_unlock(&m_mutex);
        }

        sem_post(&sem[0]); // Switch back to first semaphore
    }

    printf("The checksums match!\n");

    return NULL;
}


int main(int argc, char *argv[])
{
    int threadCheck;

    if (argc < 4)
    {
        printf("3 arguments as input is required.\n");
        printf("Needed: ./prodCon <Filename> <numItems> <numTimes>\n");
        return -1;
    }

    fileName = argv[1];

    // Checking if the second argument is an integer > 0
    if (atoi(argv[2]) > 0) 
    {
        memSize = atoi(argv[2]);

        // Checking to see if the value inputted is divisible by 32 and no more than 1024 buffers
        if (memSize % 32 == 0 && memSize <= 32768) 
        {
            numItems = memSize / 32; // The number of buffers that is inputted from memory

            // Used this link for allocating memory: https://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm
            memory = malloc(memSize); // The actual size of memory that was inputted
        }
        else 
        {
            printf("The second argument must be divisible by 32.\n");
            return -1;
        }
    }
    else 
    {
        printf("The second argument is not an integer value or inputted a 0.\n");
        return -1;
    }

    // Checking if third argument is an integer > 0
    if (atoi(argv[3]) > 0) 
    {
        numTimes = atoi(argv[3]);
    }
    else
    {
        printf("The third argument is not an integer value or inputted a 0.\n");
        return -1;
    }

    // This initializes both semaphores
    for (int i = 0; i <= 1; ++i)
    {
        if (sem_init(&sem[i], 0, 0) < 0)
        {
            printf("Error initializing semaphore %d: %d", i, errno);
            return -1;
        }
    }

    /* Create the mutex semaphore to protect the critical section */
    if (pthread_mutex_init(&m_mutex, NULL) < 0) 
    {
        printf("Error creating mutex\n");
        return -1;
    }

    // Creating and checking the threads 
    threadCheck = pthread_create(&tid[0], NULL, &producer, NULL);
    if (threadCheck < 0) 
    {
        printf("Can't create thread 1 :[%s]\n", strerror(threadCheck));
        return -1;
    }

    threadCheck = pthread_create(&tid[1], NULL, &consumer, NULL);
    if (threadCheck < 0) 
    {
        printf("Can't create thread 2 :[%s]\n", strerror(threadCheck));
        return -1;
    }

    // Join the threads
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    // Destroy semaphores
    sem_destroy(&sem[0]);
    sem_destroy(&sem[1]);

    // Reference: https://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm
    free(memory); // Frees up the allocated memory

    // Destroy mutex pthread
    pthread_mutex_destroy(&m_mutex);


    return 0;
}