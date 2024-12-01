#include "../hpp/aux.hpp"

int eq_z(float num) {
    return (-F_ZERO < num && num < F_ZERO);
}

float Vector2Module (Vector2 vector) {
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}