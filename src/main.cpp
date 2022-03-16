#include <iostream>
#include "./Commons/get_input_from_user.hpp"
#include "Guess_The_Number/guess_the_number.hpp"
#include "Hangman/hangman.hpp"
#include "Noughts_and_Crosses/noughts_and_crosses.hpp"

void show_menu()
{
    std::cout << "Which game would you like to play?" << std::endl;
    std::cout << "1 : Guess the number" << std::endl;
    std::cout << "2 : Hangman" << std::endl;
    std::cout << "q : Quit" << std::endl;
}

int main()
{
    bool quit = false;

    while (!quit) {
        show_menu();
        char command = get_input_from_user<char>("Select your game : ");
        switch (command) {
        case '1':
            play_guess_the_number();
            quit = true;
            break;
        case '2':
            play_hangman();
            quit = true;
            break;
        case 'q':
            quit = true;
            break;
        default:
            std::cout << "Oops your command is not valid. Please try again." << std::endl;
            break;
        }
    }
}