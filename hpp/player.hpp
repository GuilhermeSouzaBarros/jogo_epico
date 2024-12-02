#ifndef PLAYER
#define PLAYER

#include "shapes.hpp"
#include "math.h"

namespace player {
    class Player {
        public:
            Vector2 *p_tile_size;
            shapes::Circle hitbox = {0.0f, {0.0f, 0.0f}};

            Player(Vector2 *p_to_tile_size);
            void initialize();
            void update();
            void draw();
    };
};

#endif