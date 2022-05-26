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

float                    cell_radius(int board_size);
glm::vec2                cell_bottom_left_corner(CellIndex index, int board_size);
void                     draw_cell(CellIndex index, int board_size, p6::Context& ctx);
void                     draw_board(int size, p6::Context& ctx);
glm::vec2                center_cell(CellIndex index, int board_size);
std::optional<CellIndex> cell_hovered_by(glm::vec2 position, int board_size);
void                     create_window();
void                     play_noughts_and_crosses();
void                     draw_cross(CellIndex index, int board_size, p6::Context& ctx);
void                     draw_circle(CellIndex index, int board_size, p6::Context& ctx);
