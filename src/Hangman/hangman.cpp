#include "hangman.hpp"
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include "Commons/get_input_from_user.hpp"
#include "Commons/random.hpp"

void play_hangman()
{
    std::cout << "-----------HANGMAN-----------" << std::endl;
    Player            player(10);
    std::vector<int>  letter_positions;
    const std::string mystery_word = pick_a_random_word();
    std::string       progress_word(mystery_word.size(), '_');
    std::string       word_in_progress;

    while (player.is_alive() && !has_won(mystery_word, progress_word)) {
        player.display_life();
        display_progress_word(progress_word);
        auto input_letter = get_input_from_user<std::string>("Enter a letter : ");
        if (is_letter_in_word(input_letter, mystery_word, letter_positions)) {
            add_letter(progress_word, input_letter, letter_positions);
            letter_positions.clear();
        }
        else {
            player.decrease_life();
        }
    }
    show_end_message(mystery_word, progress_word);
}

const std::string pick_a_random_word()
{
    const std::array<std::string, 4> words = {
        "code",
        "crous",
        "imac",
        "opengl",
    };

    return words[rand<size_t>(0, words.size() - 1)];
}

int Player::get_number_of_lives() const
{
    return _number_of_lives;
}

bool Player::is_alive() const
{
    if (_number_of_lives == 0) {
        return false;
    }
    return true;
}

void Player::decrease_life()
{
    if (is_alive()) {
        _number_of_lives--;
    }
}

void Player::display_life() const
{
    std::cout << "You have " << _number_of_lives << " lives left. " << std::endl;
}

bool is_letter_in_word(std::string letter, std::string mystery_word, std::vector<int>& letter_positions)
{
    bool is_letter_found = false;
    for (unsigned int i = 0; i < mystery_word.size(); i++) {
        if (mystery_word[i] == letter[0]) {
            letter_positions.push_back(i);
            is_letter_found = true;
        }
    }
    return is_letter_found;
}

void display_progress_word(std::string word)
{
    for (unsigned int i = 0; i < word.size(); i++) {
        std::cout << word[i] << " ";
    }
    std::cout << std::endl;
}

void add_letter(std::string& progress_word, std::string input_letter, std::vector<int> letter_positions)
{
    for (auto& i : letter_positions) {
        progress_word[i] = input_letter[0];
    }
}

bool has_won(std::string word_to_find, std::string progress_word)
{
    return (word_to_find == progress_word);
}

void show_end_message(std::string mystery_word, std::string progress_word)
{
    if (has_won(mystery_word, progress_word)) {
        std::cout << "You won! The word was indeed '" << mystery_word << "'." << std::endl;
    }
    else {
        std::cout << "You failed...";
    }
}