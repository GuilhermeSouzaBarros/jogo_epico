#include "../hpp/game.hpp"
#include <stdio.h>

using namespace game;

Game::Game() {
    tick = 0.0f;
    first_frame = 1;
}

void Game::update(float delta_time) {
    player.update();
    updatePlayerCol(delta_time);
    player.hitbox.deltaPosition(delta_time);
    first_frame = 0;
}

void Game::updatePlayerCol(float delta_time) {
    for (int i = 0; i < map.rows; i++) {
        for (int j = 0; j < map.columns; j++) {
            int index = i * map.columns + j; 
            if (!map.tiles[index].tipo) continue;
            if (collisionCircleRectangle(&player.hitbox, &(map.tiles[index].hitbox), delta_time)) {
                printf("Col: %d %d\n", i, j);
            }
        }
    }
}

void Game::draw() {
    BeginDrawing();

        ClearBackground(GRAY);
        map.draw();
        player.draw();

    EndDrawing();
    first_frame = 1;
}
