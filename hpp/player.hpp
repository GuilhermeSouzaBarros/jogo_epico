#ifndef PLAYER
#define PLAYER

#include "shapes.hpp"
#include "math.h"

namespace player {
    class Player {
        public:
            shapes::Circle hitbox = {0.0f, {0.0f, 0.0f}};
            Player();
            void update();
            void draw();
    };
};

#endif