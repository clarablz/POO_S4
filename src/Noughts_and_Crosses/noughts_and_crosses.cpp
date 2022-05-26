#include "Noughts_and_Crosses/noughts_and_crosses.hpp"

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

void draw_cell(CellIndex index, int board_size, p6::Context& ctx)
{
    ctx.square(p6::BottomLeftCorner{cell_bottom_left_corner(index, board_size)},
               p6::Radius{cell_radius(board_size)});
}

void draw_circle(CellIndex index, int board_size, p6::Context& ctx)
{
    ctx.circle(p6::Center{center_cell(index, board_size)},
               p6::Radius{0.9f * cell_radius(board_size)});
}

void draw_cross(CellIndex index, int board_size, p6::Context& ctx)
{
    const auto center   = p6::Center{center_cell(index, board_size)};
    const auto radii    = p6::Radii{glm::vec2{1.f, 0.2f} * cell_radius(board_size)};
    const auto rotation = p6::Rotation{0.125_turn};
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

void create_window()
{
    auto                 ctx        = p6::Context{{800, 800, "Hello p6"}};
    static constexpr int board_size = 3;
    ctx.update                      = [&]() {
        ctx.background({0.9f, 0.9f, 0.9});
        ctx.stroke_weight = 0.01f;
        ctx.stroke        = {1.f, 1.f, 1.f, 1.f};
        ctx.fill          = {0.f, 0.f, 0.f, 0.f};
        draw_board(board_size, ctx);
        const auto hovered_cell = cell_hovered_by(ctx.mouse(), board_size);
        if (hovered_cell.has_value()) {
            ctx.stroke_weight = 0.f;
            ctx.fill          = {0.3f, 0.3f, 0.3f, 1.f};
            draw_cross(*hovered_cell, board_size, ctx);
        }
    };
    ctx.start();
}

void play_noughts_and_crosses()
{
    create_window();
}
