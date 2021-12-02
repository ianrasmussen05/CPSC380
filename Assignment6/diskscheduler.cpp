#include <iostream>
#include <string>

#define MAX_CYLINDER 5000
#define CYLINDERS 1000

int FCFS(int initialPosition, int cylinders[CYLINDERS]);
int SSTF(int initialPosition, int cylinders[CYLINDERS]);
int SCAN(int initialPosition, int cylinders[CYLINDERS]);
int CSCAN(int initialPosition, int cylinders[CYLINDERS]);

int main (int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Error: must enter 2 arguments." << std::endl;
        return -1;
    }

    int startPosition = atoi(argv[1]);
    if (startPosition < 0 || startPosition >= MAX_CYLINDER)
    {
        std::cout << "Error: the initial position must be between 0-4999." << std::endl;
        return -1;
    }

    return 0;
}