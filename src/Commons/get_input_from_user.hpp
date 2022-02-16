#pragma once
#include <iostream>

template<typename T>
T get_input_from_user()
{
    T user_input;
    std::cout << "Enter your input: ";
    std::cin >> user_input;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.sync();
        std::cout << "Please enter a valid input. " << std::endl;
    }
    return user_input;
}
