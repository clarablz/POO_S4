#include "menu.hpp"
#include "../Commons/get_input_from_user.hpp"
#include "../Guess_The_Number/guess_the_number.hpp"
#include "../Hangman/hangman.hpp"

void show_menu()
{
    std::cout << "-------------MENU---------------" << std::endl;
    std::cout << "Which game would you like to play?" << std::endl;
    std::cout << "1 : Guess the number" << std::endl;
    std::cout << "2 : Hangman" << std::endl;
    std::cout << "q : Quit" << std::endl;
}

void offer_to_play_again(bool& quit)
{
    char play_again;
    std::cout << std::endl;
    std::cout << "Would you like to play again? y/n" << std::endl;
    std::cin >> play_again;
    switch (play_again) {
    case 'y':
        break;
    case 'n':
        quit = true;
    }
}

void game_launcher()
{
    bool quit = false;

    while (!quit) {
        show_menu();
        char command = get_input_from_user<char>("Select your game : ");
        switch (command) {
        case '1':
            play_guess_the_number();
            offer_to_play_again(quit);
            break;
        case '2':
            play_hangman();
            offer_to_play_again(quit);
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