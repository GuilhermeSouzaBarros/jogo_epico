#ifndef GAME
#define GAME

#include "raylib.h"
#include "math.h"

#include "player.hpp"
#include "map.hpp"

namespace game{
    class Game {
        public:
            float tick;
            player::Player player;
            map_local::Map map = {15, 31};

            int first_frame;

            Game();
            void update(float delta_time);
            void draw();

            void updatePlayerCol(float delta_time);
        
    };
};

#endif