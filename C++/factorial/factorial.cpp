//factorial

#include <iostream>

int factorial_rec (int x)
{
    if (x == 0)
        return 1;
    return x * factorial_rec(x - 1);
}

int factorial (int x)
{
    int fact = 1;
    while (x > 0)
    {
        fact *= x--;
    }
    return fact;
}


int main ()
{
    int x;

    if(!(std::cin >> x))
    {
        std::cout << "Bad Input" << std::endl;
        return 0;
    }
    std::cout << x << "! = " << factorial(x) << std::endl;
    std::cout << x << "! = " << factorial_rec(x) << std::endl;


    return 0;
}
