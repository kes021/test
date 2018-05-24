#include <iostream>


void get_number (int &i)
{
    std::cout << "Input the number of seconds: " << std::endl;
    std::cin >> i;
}

void get_hours (int &input, int &h)
{
    h = input / 3600;
    input %= 3600;
}

void get_minutes (int &input, int &m)
{
    m = input / 60;
    input %= 60;
}

void get_seconds (const int &input, int &s)
{
    s = input;
}

void print_all (const int &inp, const int &h, const int &m, const int &s)
{
    std::cout << inp << " seconds are " << std::endl;
    std::cout << h << " hours," << std::endl;
    std::cout << m << " minutes," << std::endl;
    std::cout << "and " << std::endl;
    std::cout << s << " seconds" << std::endl;
}


int main (int argc, char *argv[])
{
    int input, i;
    int &pointer_to_input(input);
    int h, m, s;

    get_number (pointer_to_input);
    i = input;

    get_hours (i, h);
    get_minutes (i, m);
    get_seconds (i, s);

    print_all (input, h, m, s);

    return 0;
}
