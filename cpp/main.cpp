#include "raylib.h"
#include "stdlib.h"
#include "stdio.h"

#define SCREEN_X 1600
#define SCREEN_Y 900
#define TICK 0.008f

#include "../hpp/game.hpp"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    printf("%d\n", GetMonitorWidth(GetCurrentMonitor()));
    InitWindow(SCREEN_X, SCREEN_Y, "Jogo épico");
    SetExitKey(KEY_DELETE);
    SetTargetFPS(100);

    game::Game env;
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