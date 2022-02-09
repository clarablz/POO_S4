#include "guess_the_number.hpp"
#include <iostream>
#include <random>

int rand(int min, int max)
{
    static std::default_random_engine  generator{std::random_device{}()};
    std::uniform_int_distribution<int> distribution{min, max};
    return distribution(generator);
}

int get_int_from_user()
{
    int user_int;
    while (std::cout << "Enter a number: " && !(std::cin >> user_int)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid number" << std::endl;
    }
    return user_int;
}

void play_guess_the_number()
{
    int  mystery_number = rand(0, 100);
    bool found          = false;
    while (!found) {
        int user_number = get_int_from_user();
        if (user_number == mystery_number) {
            found = true;
        }
        if (user_number < mystery_number) {
            std::cout << "Greater" << std::endl;
        }
        if (user_number > mystery_number) {
            std::cout << "Smaller" << std::endl;
        }
    }
    std::cout << "Congrats, you won! The mystery number was " << mystery_number << "." << std::endl;
}