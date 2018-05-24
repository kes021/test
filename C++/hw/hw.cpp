#include <iostream>
#include <iomanip>


int main (int argc, char *argv[])
{
    std::cout << std::endl;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << std::setw(17) << std::right << "Hello World!";
        }
        std::cout << std::endl;
    }
    return 0;
}
