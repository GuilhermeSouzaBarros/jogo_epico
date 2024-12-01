#include "../hpp/player.hpp"

using namespace player;

Player::Player() {
    hitbox.radio = 10.0f;
    hitbox.pos = {65.0f, 65.0f};
    hitbox.speed = {0.0f, 0.0f};
}

void Player::update() {
    float speed = 150.0f;
    Vector2 vector = {0.0f, 0.0f};
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    vector.y -= 1.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  vector.x -= 1.0f;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  vector.y += 1.0f;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) vector.x += 1.0f;
    float module = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    if (module) {
        vector.x *= speed / module;
        vector.y *= speed / module;
    }
    hitbox.speed = vector;
}

void Player::draw() {
    DrawCircle(hitbox.pos.x, hitbox.pos.y, hitbox.radio, GOLD);
}