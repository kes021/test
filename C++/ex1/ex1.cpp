#include <iostream>

int main (int argc, char *argv[])
{
    int x;

    std::cout << "Input chirps per minute:" << std::endl;
    if (!(std::cin >> x))
    {
        throw std::runtime_error ("Bad input!");
        return 0;
    }

    std::cout << "The temperature is " << ((double) (40 + x)) / 4. << " degrees Celsius." << std::endl;

    return 0;
}
