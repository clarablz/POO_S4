#include "Noughts_and_Crosses/noughts_and_crosses.hpp"
#include <iostream>

float cell_radius(int board_size)
{
    return 1.f / board_size;
}

glm::vec2 cell_bottom_left_corner(CellIndex index, int board_size)
{
    const auto idx = glm::vec2{index._x, index._y};
    return p6::map(idx, glm::vec2{0.f}, glm::vec2{static_cast<float>(board_size)}, glm::vec2{-1.f}, glm::vec2{1.f});
}

glm::vec2 center_cell(CellIndex index, int board_size)
{
    return cell_bottom_left_corner(index, board_size) + cell_radius(board_size);
}

CellIndex convert_position_to_cell(const glm::vec2 position, int board_size)
{
    CellIndex index;
    index._x = static_cast<int>(p6::map(position.x, -1.f, 1.f, 0.f, static_cast<float>(board_size)));
    index._y = static_cast<int>(p6::map(position.y, -1.f, 1.f, 0.f, static_cast<float>(board_size)));
    return index;
}

void draw_cell(CellIndex index, int board_size, p6::Context& ctx)
{
    ctx.square(p6::BottomLeftCorner{cell_bottom_left_corner(index, board_size)},
               p6::Radius{cell_radius(board_size)});
}

void draw_circle(CellIndex index, int board_size, p6::Context& ctx)
{
    ctx.stroke_weight = 0.1f;
    ctx.stroke        = {0.75f, 0.88f, 0.46f, 1.f};
    ctx.fill          = {0.75f, 0.88f, 0.46f, 0.f};
    ctx.circle(p6::Center{center_cell(index, board_size)},
               p6::Radius{0.9f * cell_radius(board_size)});
}

void draw_cross(CellIndex index, int board_size, p6::Context& ctx)
{
    const auto center   = p6::Center{center_cell(index, board_size)};
    const auto radii    = p6::Radii{glm::vec2{1.f, 0.2f} * cell_radius(board_size)};
    const auto rotation = p6::Rotation{0.125_turn};
    ctx.stroke_weight   = 0.f;
    ctx.fill            = {0.7f, 0.56f, 0.9f, 1.f};
    ctx.rectangle(center, radii, rotation);
    ctx.rectangle(center, radii, -rotation);
}

void draw_board(int size, p6::Context& ctx)
{
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            ctx.square(p6::BottomLeftCorner{p6::map(glm::vec2{static_cast<float>(x), static_cast<float>(y)},
                                                    glm::vec2{0.f}, glm::vec2{static_cast<float>(size)},
                                                    glm::vec2{-1.f}, glm::vec2{1.f})},
                       p6::Radius{1.f / static_cast<float>(size)});
            draw_cell({x, y}, size, ctx);
        }
    }
}

std::optional<CellIndex> cell_hovered_by(glm::vec2 position, int board_size)
{
    const auto pos   = p6::map(position,
                             glm::vec2{-1.f}, glm::vec2{1.f},
                             glm::vec2{0.f}, glm::vec2{static_cast<float>(board_size)});
    const auto index = CellIndex{
        static_cast<int>(std::floor(pos.x)),
        static_cast<int>(std::floor(pos.y))};
    if (index._x >= 0 && index._x < board_size &&
        index._y >= 0 && index._y < board_size) {
        return std::make_optional(index);
    }
    else {
        return std::nullopt;
    }
}
template<int size>
void draw_Player_shape(CellIndex index, p6::Context& ctx, const Board<size>& board)
{
    const auto cell = board[{index._x, index._y}];
    if (*cell == Noughts_and_Crosses_Player::Noughts) {
        draw_circle(index, size, ctx);
    }
    else if (*cell == Noughts_and_Crosses_Player::Crosses) {
        draw_cross(index, size, ctx);
    }
}

template<int size>
void draw_noughts_and_crosses(const Board<size>& board, p6::Context& ctx)
{
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            const auto cell = board[{x, y}];
            if (cell.has_value()) {
                draw_Player_shape({x, y}, ctx, board);
            }
        }
    }
}

void switch_player(Noughts_and_Crosses_Player& player)
{
    (player == Noughts_and_Crosses_Player::Crosses) ? player = Noughts_and_Crosses_Player::Noughts : player = Noughts_and_Crosses_Player::Crosses;
}

template<int size>
std::optional<Noughts_and_Crosses_Player> check_line_win(Board<size> board, std::optional<CellIndex> cell_1, std::optional<CellIndex> cell_2, std::optional<CellIndex> cell_3)
{
    if (!cell_1.has_value())
        return std::nullopt;

    if (board[*cell_1] != board[*cell_2])
        return std::nullopt;
    if (board[*cell_1] != board[*cell_3])
        return std::nullopt;

    return board[*cell_1];
}

template<int size>
std::optional<Noughts_and_Crosses_Player> check_winner(Board<size> board)
{
    // Horizontal lines
    for (int y = 0; y < size; y++) {
        if ((check_line_win(board, std::make_optional(CellIndex{0, y}), std::make_optional(CellIndex{1, y}), std::make_optional(CellIndex{2, y})) != std::nullopt))
            return check_line_win(board, CellIndex{0, y}, CellIndex{1, y}, CellIndex{2, y});
    }

    // Vertical lines.
    for (int x = 0; x < size; x++) {
        if ((check_line_win(board, std::make_optional(CellIndex{x, 0}), std::make_optional(CellIndex{x, 1}), std::make_optional(CellIndex{x, 2})) != std::nullopt))
            return check_line_win(board, CellIndex{x, 0}, CellIndex{x, 1}, CellIndex{x, 2});
    }

    // Diagonal lines.
    if ((check_line_win(board, CellIndex{0, 0}, CellIndex{1, 1}, CellIndex{2, 2})) != std::nullopt)
        return check_line_win(board, CellIndex{0, 0}, CellIndex{1, 1}, CellIndex{2, 2});
    if ((check_line_win(board, CellIndex{2, 0}, CellIndex{1, 1}, CellIndex{0, 2})) != std::nullopt)
        return check_line_win(board, CellIndex{2, 0}, CellIndex{1, 1}, CellIndex{0, 2});

    return std::nullopt;
}

template<int size>
bool is_game_finished(Board<size> board)
{
    if (check_winner(board) != std::nullopt || board.is_full()) {
        return true;
    }
    return false;
}

template<int size>
void display_winner_message(Board<size> board)
{
    if (check_winner(board) == Noughts_and_Crosses_Player::Noughts)
        std::cout << "Youpi! Noughts won !" << std::endl;
    else
        std::cout << "Youpi! Crosses won !" << std::endl;
}

void display_tie_message()
{
    std::cout << "Oh..no winner this time!" << std::endl;
}

template<int size>
void display_end_message(Board<size> board)
{
    if (check_winner(board) != std::nullopt) {
        display_winner_message(board);
    }
    else {
        display_tie_message();
    }
}

void window_settings(p6::Context& ctx)
{
    ctx.background({0.9f, 0.9f, 0.9});
    ctx.stroke_weight = 0.01f;
    ctx.stroke        = {1.f, 1.f, 1.f, 1.f};
    ctx.fill          = {0.f, 0.f, 0.f, 0.f};
}

template<int size>
void place_shape(Board<size>& board, CellIndex cell, Noughts_and_Crosses_Player& player)
{
    if (!board[cell].has_value() && !board.is_full()) {
        board[{cell._x, cell._y}] = player;
        switch_player(player);
        board.increment_number_of_filled_cells();
    }
}
template<int size>
void draw_hovered_cell_shape(Board<size> board, std::optional<CellIndex> hovered_cell, p6::Context& ctx, Noughts_and_Crosses_Player player)
{
    if (hovered_cell.has_value() && !board.is_full()) {
        if (player == Noughts_and_Crosses_Player::Crosses) {
            draw_cross(*hovered_cell, size, ctx);
        }
        else {
            draw_circle(*hovered_cell, size, ctx);
        }
    }
}

void play_noughts_and_crosses()
{
    const int                  board_size = 3;
    auto                       board      = Board<board_size>{};
    auto                       ctx        = p6::Context{{800, 800, "Noughts and Crosses"}};
    Noughts_and_Crosses_Player player     = Noughts_and_Crosses_Player::Noughts;

    ctx.mouse_pressed = [&](p6::MouseButton event) {
        CellIndex cell = convert_position_to_cell(event.position, board_size);
        place_shape(board, cell, player);
    };

    ctx.update = [&]() {
        window_settings(ctx);
        draw_board(board_size, ctx);
        draw_noughts_and_crosses(board, ctx);
        const auto hovered_cell = cell_hovered_by(ctx.mouse(), board_size);
        draw_hovered_cell_shape(board, hovered_cell, ctx, player);
        if (is_game_finished(board)) {
            ctx.stop();
            display_end_message(board);
        }
    };

    ctx.start();
}
