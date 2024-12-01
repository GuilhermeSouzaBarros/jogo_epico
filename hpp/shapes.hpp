#ifndef SHAPES
#define SHAPES

#include "raylib.h"
#include "../hpp/retas.hpp"

namespace shapes {
    
    class Rectangle {
        public:
            Vector2 pos;
            Vector2 size;
            Vector2 speed;

            Rectangle(Vector2 to_pos, Vector2 to_size);
            void deltaPosition(float delta_time);
            Vector2 nextPosition(float delta_time);
            float recRadios();
    };

    class Circle {
        public:
            float radio;
            Vector2 pos;
            Vector2 speed;

            Circle(float to_radio, Vector2 to_pos);
            void deltaPosition(float delta_time);
            Vector2 nextPosition(float delta_time);
    };

    colRetaInfo checkColRetaRectangle(Reta reta, Rectangle rec);
    char collisionCircleRectangle(Circle *p_cir, Rectangle *p_rec, float delta_time);
}

#endif