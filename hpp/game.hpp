#ifndef GAME
#define GAME

#include "raylib.h"
#include "math.h"

#include "player.hpp"
#include "map.hpp"

namespace game{
    class Game {
        public:
            Vector2 window_size;
            Vector2 tile_size;
            float tick;
            player::Player player = {&tile_size};
            map_local::Map map = {15, 31, &tile_size};

            int first_frame;

            Game(Vector2 to_window_size);
            void update(float delta_time);
            void draw();

            void updatePlayerCol(float delta_time);
        
    };
};

#endif