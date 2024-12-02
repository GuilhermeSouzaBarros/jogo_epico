#include "../hpp/game.hpp"
#include <stdio.h>

using namespace game;

Game::Game(Vector2 to_window_size) {
    window_size = to_window_size;
    
    float tile_x = window_size.x / 31, tile_y = window_size.y / 15;
    float smallest = tile_x;
    if (tile_x > tile_y) smallest = tile_y;
    
    tile_size = {smallest, smallest};
    tick = 0.0f;
    first_frame = 1;
    
    player.initialize();
    map.initialize();
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
            collisionCircleRectangle(&player.hitbox, &(map.tiles[index].hitbox), delta_time);
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
