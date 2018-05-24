#include <iostream>


int get_gcd (int x, int y)
{
    int temp;
    while (y != 0)
    {
        temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}
// assume x, y positive here
int rec_gcd (int x, int y)
{
    if (x == 0)
        return y;
    if (y == 0)
        return x;
    if (x > y)
        return rec_gcd (y, x % y);
    return rec_gcd (y, x);
}

int main ()
{
    int a, b;

    if (!(std::cin >> a))
    {
        std::cout << "Bad input." << std::endl;
        return 0;
    }
    if (!(std::cin >> b))
    {
        std::cout << "Bad input." << std::endl;
        return 0;
    }

    std::cout << "The gcd of " << a << " and " << b << " is ";
    std::cout << get_gcd(a,b);
    std::cout << std::endl << std::endl;

    std::cout << "The gcd of " << a << " and " << b << " is ";
    std::cout << rec_gcd(a,b);
    std::cout << std::endl;

    return 0;
}
