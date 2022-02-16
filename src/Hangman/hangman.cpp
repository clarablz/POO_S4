#include "hangman.hpp"
#include <array>
#include <iostream>
#include "../Commons/random.hpp"

const char* pick_a_random_word()
{
    static constexpr std::array words = {
        "code",
        "crous",
        "imac",
        "opengl",
    };

    return words[rand<size_t>(0, words.size() - 1)];
}