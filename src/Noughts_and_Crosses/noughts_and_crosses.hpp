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
        : _size(size) {}
    std::optional<Noughts_and_Crosses_Player>& operator[](CellIndex index)
    {
        return _state[index._x + _size * index._y];
    }

    const std::optional<Noughts_and_Crosses_Player>& operator[](CellIndex index) const
    {
        return _state[index._x + _size * index._y];
    }

    int get_size() const { return _size; }

private:
    std::vector<std::optional<Noughts_and_Crosses_Player>> _state;
    int                                                    _size;
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
