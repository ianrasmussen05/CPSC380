#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
//#include <bits/stdc++.h>

#define MAX_CYLINDER 5000
#define CYLINDERS 1000

typedef struct {
    int value;
    int visited = 0;
} visitedCylinders;

FILE *file; // File to be opened

// Functions to be used at the end of the file
int FCFS(int initialPosition, visitedCylinders cylinders[CYLINDERS]);
int SSTF(int initialPosition, visitedCylinders cylinders[CYLINDERS]);
int SCAN(int initialPosition, visitedCylinders cylinders[CYLINDERS]);
int CSCAN(int initialPosition, visitedCylinders cylinders[CYLINDERS]);
int findClosestValueSSTF(int initialPosition, visitedCylinders cylinders[CYLINDERS]);
int findClosestValueSCAN(int initialPosition, visitedCylinders cylinders[CYLINDERS]);
bool checkVisited(visitedCylinders cylinders[CYLINDERS]);

int main (int argc, char* argv[])
{
    // Check the integrity of user input from command line
    if (argc < 3)
    {
        std::cout << "Error: must enter 2 arguments." << std::endl;
        return -1;
    }

    int startPosition;
    std::string fileName = argv[2];
    
    startPosition = atoi(argv[1]);
    if (startPosition < 0 || startPosition >= MAX_CYLINDER)
    {
        std::cout << "Error: the initial position must be between 0-4999." << std::endl;
        return -1;
    }

    visitedCylinders cylinders[CYLINDERS];
    char line[8];

    // Open the file
    file = fopen(fileName.c_str(), "r");
    if (file != NULL)
    {
        int currVal = 0;

        while (fgets(line, sizeof(line), file))
        {
            cylinders[currVal].value = atoi(line);
            currVal++;
        }
    }
    else 
    {
        std::cout << "Error: the file inputted does not exist." << std::endl;
        return -1;
    }

    // Close the file
    fclose(file);

    int fcfs;
    int sstf;
    int scan;
    int cscan;

    fcfs = FCFS(startPosition, cylinders);
    sstf = SSTF(startPosition, cylinders);
    scan = SCAN(startPosition, cylinders);
    cscan = CSCAN(startPosition, cylinders);

    std::cout << "FCFS: " << fcfs << "\nSSTF: " << sstf << "\nSCAN: " << scan << "\nCSCAN: " << cscan << std::endl;

    return 0;
}

int FCFS(int initialPosition, visitedCylinders cylinders[CYLINDERS])
{
    int totalMovement = 0;

    // The first case, finding difference between initial position and first cylinder
    // This if statement makes sure of no negative numbers
    if (initialPosition > cylinders[0].value) 
    {
        int diff;
        diff = initialPosition - cylinders[0].value;
        totalMovement += diff;
    }
    else if (initialPosition < cylinders[0].value)
    {
        int diff;
        diff = cylinders[0].value - initialPosition;
        totalMovement += diff;
    }
    else 
    {
        totalMovement = 0;
    }


    // Now we iterate through the cylinders struct to get the total movement
    for (int i = 0; i < CYLINDERS; ++i)
    {
        if (i == CYLINDERS-1)
        {
            cylinders[CYLINDERS-1].visited = 1;
        }

        if (cylinders[i].value > cylinders[i+1].value)
        {
            cylinders[i].visited = 1;
            totalMovement += cylinders[i].value - cylinders[i+1].value;
        }
        else if (cylinders[i].value < cylinders[i+1].value)
        {
            cylinders[i].visited = 1;
            totalMovement += cylinders[i+1].value - cylinders[i].value;
        }
        else 
        {
            cylinders[i].visited = 1;
            totalMovement += 0;
        }
    }

    // Checks to see if every cylinder in the file has been visited
    if (!checkVisited(cylinders))
    {
        std::cout << "Not all cylinders have been visited." << std::endl;
        return -1;
    }


    return totalMovement;
}

int SSTF(int initialPosition, visitedCylinders cylinders[CYLINDERS])
{
    int totalMovement = 0;
    int curr = 0;
    int i = 0;

    /*
    while (curr != CYLINDERS)
    {
        int minValue = CYLINDERS;
        int diff;
        int n; 

        for (i = 0; i < CYLINDERS; ++i)
        {
            if (cylinders[i].visited == 1)
            {
                continue;
            }


            if (cylinders[i].value > initialPosition)
            {
                diff = cylinders[i].value - initialPosition;
            }
            else 
            {
                diff = initialPosition - cylinders[i].value;
                
            }


            if (diff < minValue)
            {
                minValue = diff;
                n = i;
            }
        }
        std::cout << "n: " << n << "\n";

        cylinders[n].visited = 1;
        initialPosition = cylinders[n].value;
        totalMovement += minValue;

        curr++;
    }
    */

    

    /*
    int cyl[CYLINDERS];

    // Copy the struct to an array of the values in the struct to sort for later
    for (int i = 0; i < CYLINDERS; ++i)
    {
        cyl[i] = cylinders[i].value;
    }

    // I found how to sort the array values of cylinders using this link: 
    // https://www.educba.com/c-plus-plus-sort/
    std::sort(cyl, cyl+CYLINDERS);

    // Copy the sorted values from cyl back into the cylinders struct
    for (int i = 0; i < CYLINDERS; ++i)
    {
        cylinders[i].value = cyl[i];
    }


    int startPoint = findClosestValueSSTF(initialPosition, cylinders);
    std::cout << startPoint << std::endl;

    totalMovement += initialPosition - cylinders[startPoint].value;

    int n = 0;
    int currStart = startPoint;
    while (n < CYLINDERS)
    {
        int temp;
        temp = findClosestValueSSTF(currStart, cylinders);
        cylinders[currStart].visited = 1;

        totalMovement += currStart - cylinders[temp].value;
        //std::cout << totalMovement << "\t";

        n++;
    }
    //std::cout << std::endl;
    */


    // Checks to see if every cylinder in the file has been visited
    if (!checkVisited(cylinders))
    {
        std::cout << "Not all cylinders have been visited." << std::endl;
        return -1;
    }


    return totalMovement;
}

int SCAN(int initialPosition, visitedCylinders cylinders[CYLINDERS])
{
    int totalMovement = 0;
    int cyl[CYLINDERS];

    // Copy the struct to an array of the values in the struct to sort for later
    for (int i = 0; i < CYLINDERS; ++i)
    {
        cyl[i] = cylinders[i].value;
    }

    // I found how to sort the array values of cylinders using this link: 
    // https://www.educba.com/c-plus-plus-sort/
    std::sort(cyl, cyl+CYLINDERS);
    
    // Copy the sorted values from cyl back into the cylinders struct
    for (int i = 0; i < CYLINDERS; ++i)
    {
        cylinders[i].value = cyl[i];
    }

    // Find the start point. The value directly less than the initial position
    int startPoint = findClosestValueSCAN(initialPosition, cylinders);


    // Must subtract the initial position from the next value in the array first
    totalMovement += initialPosition - cylinders[startPoint].value;

    // This for loop goes to one end of the disk (left side)
    for (int i = startPoint; i >= 0; --i)
    {
        // Case where the array is in the very first spot
        if (i == 0)
        {
            cylinders[i].visited = 1;
            break;
        }

        cylinders[i].visited = 1;
        totalMovement += cylinders[i].value - cylinders[i-1].value;
    }

    // This for loop goes to the other end of the disk (right side)
    for (int i = startPoint+1; i < CYLINDERS; ++i)
    {
        // Entered the last spot in the array
        if (i == CYLINDERS-1)
        {
            cylinders[i].visited = 1;
            break;
        }

        cylinders[i].visited = 1;
        totalMovement += cylinders[i+1].value - cylinders[i].value;
    }

    // Checks to see if every cylinder in the file has been visited
    if (!checkVisited(cylinders))
    {
        std::cout << "Not all cylinders have been visited." << std::endl;
        return -1;
    }


    return totalMovement;
}

int CSCAN(int initialPosition, visitedCylinders cylinders[CYLINDERS])
{
    int totalMovement = 0;
    int cyl[CYLINDERS];

    // Copy the struct to an array of the values in the struct to sort for later
    for (int i = 0; i < CYLINDERS; ++i)
    {
        cyl[i] = cylinders[i].value;
    }

    // I found how to sort the array values of cylinders using this link: 
    // https://www.educba.com/c-plus-plus-sort/
    std::sort(cyl, cyl+CYLINDERS);
    
    // Copy the sorted values from cyl back into the cylinders struct
    for (int i = 0; i < CYLINDERS; ++i)
    {
        cylinders[i].value = cyl[i];
    }

    // Find the start point. The value directly less than the initial position
    int startPoint = findClosestValueSCAN(initialPosition, cylinders);


    // Must subtract the initial position from the next value in the array first
    totalMovement += initialPosition - cylinders[startPoint].value;

    for (int i = startPoint; i < CYLINDERS; ++i)
    {
        if (i == CYLINDERS - 1)
        {
            cylinders[i].visited = 1;
            break;
        }

        cylinders[i].visited = 1;
        totalMovement += cylinders[i+1].value - cylinders[i].value;
    }

    for (int i = 0; i < startPoint; ++i)
    {
        cylinders[i].visited = 1;
        totalMovement += cylinders[i+1].value - cylinders[i].value;
    }



    // Checks to see if every cylinder in the file has been visited
    if (!checkVisited(cylinders))
    {
        std::cout << "Not all cylinders have been visited." << std::endl;
        return -1;
    }


    return totalMovement;
}

int findClosestValueSSTF(int initialPosition, visitedCylinders cylinders[CYLINDERS])
{
    int closeMin;
    int closeMax;
    int i;

    for (i = 0; i < CYLINDERS; ++i)
    {
        if (cylinders[i].visited == 1)
        {
            continue;
        }

        if (cylinders[i].value < initialPosition || cylinders[i].value == initialPosition)
        {
            closeMin = cylinders[i].value;
        }
        else 
        {
            closeMax = cylinders[i].value;
            break;
        }
    }


    if ((initialPosition - closeMin) > (closeMax - initialPosition))
    {
        return i;
    }
    else 
    {
        return i-1;
    }
}

int findClosestValueSCAN(int initialPosition, visitedCylinders cylinders[CYLINDERS])
{
    int i;

    for (i = 0; i < CYLINDERS; ++i)
    {
        if (cylinders[i].value < initialPosition)
        {
            continue;
        }
        else 
        {
            break;
        }
    }


    return i-1;
}

bool checkVisited(visitedCylinders cylinders[CYLINDERS])
{
    for (int i = 0; i < CYLINDERS; ++i)
    {
        if (cylinders[i].visited == 0)
        {
            return false;
        }
    }

    return true;
}