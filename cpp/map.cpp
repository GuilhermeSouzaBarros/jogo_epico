#include "../hpp/map.hpp"

#include <stdio.h>
#include <stdlib.h>

using namespace map_local;

Map::Map(int to_rows, int to_columns) {
    rows = to_rows;
    columns = to_columns;
    int total = rows * columns;
    tile_size = {40.0f, 40.0f};
    tiles = (Tile*)malloc(sizeof(Tile) * total);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int index = i * columns + j;
            tiles[index].hitbox.pos = {(j + 0.5f)*tile_size.x, (i + 0.5f)*tile_size.y};
            tiles[index].hitbox.size = tile_size;
            tiles[index].hitbox.speed = {0.0f, 0.0f};
            tiles[index].tipo = 0;
            if (i == 0        || j == 0           ||
                i == rows - 1 || j == columns - 1 ||
                !(i % 2       || j % 2)) {
                tiles[index].tipo = 1;
            }
        }
    }
    printf("Mapa alocado\n");
}

Map::~Map() {
    free(tiles);
    printf("Mapa desalocado\n");
}

void Map::draw() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int index = i * columns + j;
            if (!tiles[index].tipo) continue;
            Vector2 pos = {tiles[index].hitbox.pos.x - 20.0f,
                           tiles[index].hitbox.pos.y - 20.0f};
            DrawRectangleV(pos, tile_size, GREEN);
            DrawCircleLinesV(tiles[index].hitbox.pos, tiles[index].hitbox.recRadios(), LIGHTGRAY);
        }
    }
}
