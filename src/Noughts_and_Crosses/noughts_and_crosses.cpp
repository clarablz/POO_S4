#include "Noughts_and_Crosses/noughts_and_crosses.hpp"

void draw_board(int size, p6::Context& ctx)
{
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            ctx.square(p6::BottomLeftCorner{p6::map(glm::vec2(float(x), float(y)),
                                                    glm::vec2(0.f, 0.f), glm::vec2(float(size), float(size)),
                                                    glm::vec2(-1.f, -1.f), glm::vec2(1.f, 1.f))},
                       p6::Radius{1.f / size});
        }
    }
}

void create_window()
{
    auto ctx   = p6::Context{{800, 800, "Hello p6"}};
    ctx.update = [&]() {
        ctx.background({1.f, 0.70f, 0.91});
        ctx.stroke_weight = 0.01f;
        ctx.stroke        = {1.f, 1.f, 1.f, 1.f};
        ctx.fill          = {0.f, 0.f, 0.f, 0.f};
        draw_board(3, ctx);
    };
    ctx.start();
}