#include <iostream>
#include <string>

int main (int argc, char* argv[])
{
    std::string userInput = "";

    std::cout << "Enter an input: ";
    std::cin >> userInput;

    while (userInput.empty())
    {
        std::cout << "Must enter a value." << std::endl;
        std::cin >> userInput;
        std::cout << std::endl;
    }

    std::cout << "You entered: " + userInput << std::endl;

    return 0;
}