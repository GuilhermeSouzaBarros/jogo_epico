#ifndef MAP
#define MAP

#include "raylib.h"
#include "shapes.hpp"

namespace map_local {
    typedef struct Tile {
        shapes::Rectangle hitbox;
        char tipo;
    } Tile;

    class Map {
        public:
            Tile *tiles;
            Vector2 tile_size;
            int rows, columns;

            Map(int to_rows, int to_columns);
            ~Map();

            void draw();
    };
}

#endif