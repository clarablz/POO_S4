#include "guess_the_number.hpp"
#include <iostream>
#include "Commons/get_input_from_user.hpp"
#include "Commons/random.hpp"

void play_guess_the_number()
{
    int  mystery_number = rand<int>(0, 100);
    bool found          = false;
    while (!found) {
        int user_number = get_input_from_user<int>();
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