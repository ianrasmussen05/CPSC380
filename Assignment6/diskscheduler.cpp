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
void resetVisited(visitedCylinders cylinders[CYLINDERS]);
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

    resetVisited(cylinders);

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
        int diff;
        if (i == CYLINDERS-1)
        {
            cylinders[CYLINDERS-1].visited = 1;
            break;
        }

        if (cylinders[i].value > cylinders[i+1].value)
        {
            diff = cylinders[i].value - cylinders[i+1].value;
            totalMovement += diff;
        }
        else if (cylinders[i].value < cylinders[i+1].value)
        {
            diff = cylinders[i+1].value - cylinders[i].value;
            totalMovement += diff;
        }
        else 
        {
            totalMovement += 0;
        }

        cylinders[i].visited = 1;
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
    int currPosition = 0;
    int newPosition = 0;
    int smallIterator = 0;
    int bigIterator = 0;
    int smallDiff = 0;
    int bigDiff = 0;
    int n = 0;

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


    // Find the closest starting position from initial position
    for (int i = 0; i < CYLINDERS; ++i)
    {
        if (initialPosition > cylinders[i].value)
        {
            currPosition = i;
        }
    }

    // Assign the positions of the values
    newPosition = currPosition;
    smallIterator = currPosition - 1;
    bigIterator = currPosition + 1;

    while (n <= CYLINDERS - 2)
    {
        // Find the difference in values between the current position and the position to the left of it
        if (cylinders[newPosition].value > cylinders[smallIterator].value)
        {
            smallDiff = cylinders[newPosition].value - cylinders[smallIterator].value;
        }
        else 
        {
            smallDiff = cylinders[smallIterator].value - cylinders[newPosition].value;
        }

        // Find the difference in values between the current position and the position to the right of it
        if (cylinders[bigIterator].value > cylinders[newPosition].value)
        {
            bigDiff = cylinders[bigIterator].value - cylinders[newPosition].value;
        }
        else 
        {
            bigDiff = cylinders[newPosition].value - cylinders[bigIterator].value;
        }


		if(smallDiff < bigDiff) 
        {
			totalMovement += smallDiff;
			newPosition = smallIterator;
			smallIterator--;
			
		} 
        else 
        {
			totalMovement += bigDiff;
			newPosition = bigIterator;
			bigIterator++;
		}

		n++;
    }


    return totalMovement;
}

int SCAN(int initialPosition, visitedCylinders cylinders[CYLINDERS])
{
    int totalMovement = 0;
    int cyl[CYLINDERS];

    resetVisited(cylinders);

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

    resetVisited(cylinders);

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

void resetVisited(visitedCylinders cylinders[CYLINDERS])
{
    for (int i = 0; i < CYLINDERS; ++i)
    {
        cylinders[i].visited = 0;
    }
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