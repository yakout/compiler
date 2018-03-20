#include <iostream>

std::string CALL_ERROR = "Invalid Number of Arguments";

int main(int argc, char** argv) {
    if (argc == 1)
    {

    }
    else if (argc == 2)
    {

    }
    else
    {
        std::cout << CALL_ERROR << std::endl;
    }
    return 0;
}
