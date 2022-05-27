#pragma once
#include <iostream>
#include "../Commons/get_input_from_user.hpp"
#include "../Guess_The_Number/guess_the_number.hpp"
#include "../Hangman/hangman.hpp"
#include "../Noughts_and_Crosses/noughts_and_crosses.hpp"
void show_menu();
void offer_to_play_again(bool& quit);
void game_launcher();