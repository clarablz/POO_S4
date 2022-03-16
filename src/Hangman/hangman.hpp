#pragma once
#include <string>
#include <vector>

const std::string pick_a_random_word();

class Player {
private:
    bool _isAlive;
    int  _number_of_lives;

public:
    Player(int life = 10)
        : _number_of_lives(life) {}
    bool is_alive() const;
    int  get_number_of_lives() const;
    void decrease_life();
    void display_life() const;
};

void play_hangman();
void display_progress_word(std::string word);
bool is_letter_in_word(std::string letter, std::string word, std::vector<int>& positions);
void add_letter(std::string& progress_word, std::string input_letter, std::vector<int> positions);
bool has_won(std::string word_to_find, std::string progress_word);
void show_end_message(std::string mystery_word, std::string progress_word);