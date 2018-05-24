#include <iostream>

int main (int argc, char *argv[])
{
    int sppw;
    int price = 225;
    int mark23 = 0, mark2 = 0, mark3 = 0;
    double win1, win2, win3; // win1 = 600 per week, win2 = 8*7*5 + sppw * price * 0.1
                        // win3 = sppw * (price * 0.2 + 20)
    win1 = 600;

    for (sppw = 0; sppw < 100; sppw++)
    {
        win2 = double(8*7*7) + double(sppw) * double(price) * 0.1;
        win3 = double(sppw) * (double(price) * 0.2 + 20.0);
        if (win2 < win1)
            mark2 = sppw;
        if (win3 < win1)
            mark3 = sppw;
        if (win2 < win3)
            mark23 = sppw;
    }

    std::cout << mark2;
    std::cout << std::endl;
    std::cout << mark3;
    std::cout << std::endl;
    std::cout << mark23;
    std::cout << std::endl;

    return 0;
}
