#include "raylib.h"
#include "stdlib.h"
#include "stdio.h"

#define TICK 0.008f

#include "../hpp/game.hpp"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(0, 0, "Jogo épico");
    Vector2 full_size = {(float)GetMonitorWidth(0), (float)GetMonitorHeight(0)};
    Vector2 window_size = {full_size.x * 0.8f, full_size.y * 0.8f};
    Vector2 window_pos  = {full_size.x * 0.1f, full_size.y * 0.1f};

    SetWindowSize(window_size.x, window_size.y);
    SetWindowPosition(window_pos.x, window_pos.y);
    SetExitKey(KEY_DELETE);
    SetTargetFPS(100);

    game::Game env(window_size);
    while(!WindowShouldClose()) {
        env.tick += GetFrameTime();
        while(env.tick >= TICK) {
            env.update(TICK);
            env.tick -= TICK;
        }
        env.draw();
    }

    CloseWindow();
    return 0;
}