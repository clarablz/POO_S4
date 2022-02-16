#pragma once
#include <iostream>

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
