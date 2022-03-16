#pragma once
#include <iostream>
#include <string>

template<typename T>
T get_input_from_user(std::string display_message)
{
    T user_input;
    while (true) {
        std::cout << display_message;
        if (std::cin >> user_input) {
            break;
        }
        else {
            std::cout << "Please enter a valid input. " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return user_input;
}
