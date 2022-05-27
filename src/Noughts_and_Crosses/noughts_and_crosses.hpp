#pragma once
#include <p6/p6.h>

struct CellIndex {
    int _x;
    int _y;
};

enum class Noughts_and_Crosses_Player {
    Noughts,
    Crosses,
};

template<int size>
class Board {
public:
    Board()
        : _size(size), _number_of_filled_cells(0) {}
    std::optional<Noughts_and_Crosses_Player>& operator[](CellIndex index)
    {
        return _cells[index._x][index._y];
    }

    const std::optional<Noughts_and_Crosses_Player>& operator[](CellIndex index) const
    {
        return _cells[index._x][index._y];
    }

    int  get_size() const { return _size; }
    bool is_board_full() const;
    int  get_number_of_filled_cells() const { return _number_of_filled_cells; }
    void increment_number_of_filled_cells() { _number_of_filled_cells++; }
    bool is_full() const { return (_number_of_filled_cells == 9) ? true : false; }

private:
    std::array<std::array<std::optional<Noughts_and_Crosses_Player>, size>, size> _cells;
    int                                                                           _size;
    int                                                                           _number_of_filled_cells;
};

void play_noughts_and_crosses();
