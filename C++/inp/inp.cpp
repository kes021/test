#include <iostream>
#include <stdlib.h>
#include <time.h>



int get_guess ()
{
    int new_guess;

    if(!(std::cin >> new_guess))
    {
        std::cout << "Bad input!" << std::endl;
        std::cin.clear();
        std::cin.ignore();
        new_guess = get_guess();
    }
    return new_guess;
}

int next_round ()
{
    int next;

    if(!(std::cin >> next))
    {
        std::cout << "Bad input!" << std::endl;
        std::cin.clear();
        std::cin.ignore();
        next = next_round();
    }
    if (next != 0 && next != 1)
    {
        std::cout << "Bad input!" << std::endl;
        std::cin.clear();
        std::cin.ignore();
        next = next_round();
    }
    if (next == 1)
        std::cout << "Guess a number between 1 and 100." << std::endl;

    return next;
}

int next_round_r ()
{
    std::cout << "Enter 1, if you want to play another round," << std::endl;
    std::cout << "Enter 0, if you don't want to play anymore." << std::endl;

    return next_round();
}

void play (int number)
{
    int input;
    input = get_guess();
    if (input == -42)
    {
        std::cout << "Congrats! You cheated your way through :D" << std::endl;
        return;
    }
    if (input > number)
    {
        std::cout << "Guess again, your guess was to big!" << std::endl;
        play(number);
        return;
    }
    if (input < number)
    {
        std::cout << "Guess again, your guess was to small!" << std::endl;
        play(number);
        return;
    }
    if (input == number)
    {
        std::cout << "Congrats! You guessed correctly!" << std::endl;
        return;
    }
}


int main ()
{
    int input;
    int count = 0;
    int random;
    int again = 1;

    srand(time(NULL));
    random = rand() % 100 + 1;

    std::cout << "Guess a number between 1 and 100." << std::endl;
    do
    {
        input = get_guess();
        if (input == -42)
        {
            std::cout << "Congrats! You cheated your way through :D" << std::endl;
            if ((again = next_round_r()))
                continue;
            break;
        }
        if (input > random)
        {
            std::cout << "Guess again, your guess was to big!" << std::endl;
            count++;
            continue;
        }
        if (input < random)
        {
            std::cout << "Guess again, your guess was to small!" << std::endl;
            count++;
            continue;
        }
        if (input == random)
        {
            count++;
            std::cout << "Congrats! You guessed correctly!" << std::endl;
            std::cout << "It took you " << count << " rounds to find the correct number." << std::endl;
            std::cout << "Do you want to play again? Enter 1 for Yes, 0 for No." << std::endl;
            if (next_round())
            {
                random = rand() % 100 + 1;
                continue;
            }
            std::cout << "Thanks for playing our little game." << std::endl;
            std::cout << "We hope you enjoyed it as much as we did :)" << std::endl;
            break;
        }
    } while (1);

    //recursive version

    std::cout << "Guess a number between 1 and 100." << std::endl;
    while (again)
    {
        random = rand() % 100 + 1;
        play(random);
        again = next_round_r();
    }

/*    do
    {
        std::cout << "Enter a positive integer (-1 to quit):" << std::endl;

        if (!(std::cin >> input))
        {
            std::cout << "Incorrect input!" << std::endl;
            std::cin.clear();
            std::cin.ignore();
        } else
            std::cout << "You entered " << input << std::endl;

    } while (input != -1);
*/


    return 0;
}
