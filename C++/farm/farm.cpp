#include <iostream>

int main ()
{
    int h,p,r, max[4], temp[3];

    float ch, cp, cr, sum;
    h = 0;
    p = 0;
    r = 0;
    ch = 10;
    cp = 3;
    cr = .5;
    sum = 0;
    max[0] = 0;

    for (; h <= 10; h++)
    {
        sum = h*ch;
        if ( sum == 100)
        for (; p <= 34; p++)
        {
            for (; r <= 200; r++)
            {
                sum = h*ch + p*cp + r*cr;
                if (sum == 100)
                {
                    temp[0] = h;
                    temp[1] = p;
                    temp[2] = r;
                    std::cout << "Found one :" << std::endl;
                    std::cout << "Then the farmer can buy " << std::endl;
                    std::cout << temp[0] << " horses" << std::endl;
                    std::cout << temp[1] << " pigs" << std::endl;
                    std::cout << temp[2] << " rabbits" << std::endl;
                    if (sum > max[0])
                    {
                        max[0] = sum;
                        max[1] = h;
                        max[2] = p;
                        max[3] = r;
                    }
                }
            }
            r = 0;
        }
        p = 0;
    }
    if (max[0] != 0)
    {
        std::cout << "The maximal number of animals possible is " << max[0] << std::endl;
        std::cout << "Then the farmer could buy " << std::endl;
        std::cout << max[1] << " horses" << std::endl;
        std::cout << max[2] << " pigs" << std::endl;
        std::cout << max[3] << " rabbits" << std::endl;
    }

    return 0;
}
