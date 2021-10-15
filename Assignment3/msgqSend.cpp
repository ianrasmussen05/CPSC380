/* 
 * Ian Rasmussen
 * 2317200
 * irasmussen@chapman.edu
 * CPSC 380-01
 * Assignment 3
 * msgqSend.cpp
 */

#include <sys/msg.h>
#include <iostream>
#include <string.h>

#define MAX_LINE 80 // 80 chars per line, per command

#ifndef _MSGBUF
#define _MSGBUF
struct Msgbuf
{
    long mtype;
    char mtext[MAX_LINE];
};
#endif

int main(int argc, char *argv[])
{
    key_t key;  	// message queue key
    int msgqID;   // message queue ID
    int msgSend;
    int should_run = 1;
    
    key = ftok(argv[1], 'q'); // generate key
    if (key == -1)
    {
        perror("ftok");
        return -1;
    }

    // Got msgget from: https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-msgget-get-message-queue
    // Got 0666 from office hours
    msgqID = msgget(key, 0666 | IPC_CREAT); // generate message ID
    if (msgqID == -1)
    {
        perror("msgget");
        return -1;
    }

    struct Msgbuf buffer; // create buffer object
    std::string userInput; // string input

    buffer.mtype = 1; // Not sure of the purpose of the long type

    std::cout << "Enter 'exit' or 'quit' to exit the program." << std::endl;

    while (should_run) 
    {   
        printf("msgq> ");
        fflush(stdout);

        std::cin >> userInput;
        strcpy(buffer.mtext, userInput.c_str());

        if (userInput == "quit" || userInput == "exit") // Exits the program
        {
            // I found how to delete a message queue by this resource: https://stackoverflow.com/questions/31671016/removing-a-message-queue
            msgctl(msgqID, IPC_RMID, NULL); // Delete the message queue
            std::cout << "Exiting..." << std::endl;
            return 0;
        }
        else 
        {
            // Got msgsnd function from: https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-msgsnd-message-send-operations
            msgSend = msgsnd(msgqID, &buffer, sizeof(buffer.mtext), 0);
            if (msgSend == -1)
            {
                perror("msgsnd");
                return -1;
            }
        }
    }
    
    return 0;
}
