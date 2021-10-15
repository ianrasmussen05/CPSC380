# Assignment 3: IPC Message Queues

In this message queue program, the sender (msgqSend.cpp) takes input from the user and sends the input to the receiver (msgqReceive.cpp). When each input or command is sent to the receiver, the receiver then uses the system() command to carry out the instructions (like in a shell terminal) the sender client sent.

* Name: Ian Rasmussen
* Student ID: 2317200
* Email: irasmussen@chapman.edu
* Course: CPSC 380-01
* Assignment: Assignment 3

## Source Files:
* msgqSend.cpp
* msgqReceive.cpp

## Resources:
* Went to office hours for help on '0666' when creating the key.
* Referenced link on deleting queue in 'msgqSend.cpp'.

## Code Limitations:
* None

## Build Program:
* g++ msgqSend.cpp -o send
* g++ msgqSend.cpp -o receive

## Execute Program:
* ./send (filename)
* ./receive (filename)