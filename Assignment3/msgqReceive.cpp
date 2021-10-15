/* 
 * Ian Rasmussen
 * 2317200
 * irasmussen@chapman.edu
 * CPSC 380-01
 * Assignment 3
 * msgqReceive.cpp
 */

#include <sys/msg.h>
#include <iostream>
#include <string.h>

#define MAX_LINE 80 // 80 chars per line, per command

struct Msgbuf 
{
    long mtype;
    char mtext[MAX_LINE];
};

int main(int argc, char *argv[])
{
    key_t key; // message queue key
    int msgqID; // message queue ID
    int msgReceive;
    int should_run = 1;
    
    key = ftok(argv[1], 'q'); // generate key
    if (key == -1)
    {
        perror("ftok");
        return -1;
    }

    // Got 0666 from office hours
    msgqID = msgget(key, 0666 | IPC_CREAT); // generate message ID
    if (msgqID == -1)
    {
        perror("msgget");
        return -1;
    }
    
    struct Msgbuf buffer;
    std::string userInput;

    buffer.mtype = 1;

    std::cout << "Welcome to the Receiver!" << std::endl;
    
    while (should_run) 
    {
        msgReceive = msgrcv(msgqID, &buffer, MAX_LINE, 0, 0);
        if (msgReceive == -1)
        {
            perror("msgrcv");
            return -1;
        }

        if (buffer.mtext == "quit" || buffer.mtext == "exit")
        {
            std::cout << buffer.mtext << std::endl;
            std::cout << "Exiting..." << std::endl;
            return 0;
        }
        else 
        {
            std::cout << buffer.mtext << std::endl;
            system(buffer.mtext);
        }
    }
    
    return 0;
}
