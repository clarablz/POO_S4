#include "guess_the_number.hpp"
#include <iostream>
#include "Commons/get_input_from_user.hpp"
#include "Commons/random.hpp"

void play_guess_the_number()
{
    std::cout << "-----------GUESS THE NUMBER-----------" << std::endl;
    int  mystery_number = rand<int>(0, 100);
    bool is_found       = false;
    while (!is_found) {
        auto user_number = get_input_from_user<int>("Enter a number : ");
        if (user_number == mystery_number) {
            is_found = true;
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