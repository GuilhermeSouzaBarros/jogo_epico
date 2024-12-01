#include "../hpp/shapes.hpp"
#include "../hpp/aux.hpp"

#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

using namespace shapes;

shapes::Rectangle::Rectangle(Vector2 to_pos, Vector2 to_size) {
    pos = to_pos;
    size = to_size;
}

void shapes::Rectangle::deltaPosition(float delta_time) {
    pos.x += speed.x * delta_time;
    pos.y += speed.y * delta_time;
}

Vector2 shapes::Rectangle::nextPosition(float delta_time) {
    Vector2 next = pos;
    next.x += speed.x * delta_time;
    next.y += speed.y * delta_time;
    return next;
}

float shapes::Rectangle::recRadios() {
    return sqrt(pow(size.x, 2) + pow(size.y, 2)) / 2.0f;
}

Circle::Circle(float to_radio, Vector2 to_pos) {
    radio = to_radio;
    pos = to_pos;
    speed = {0.0f, 0.0f};
}

void Circle::deltaPosition(float delta_time) {
    printf("spd: %.2f / %.2f\n", speed.x, speed.y);
    pos.x += speed.x * delta_time;
    pos.y += speed.y * delta_time;
}

Vector2 Circle::nextPosition(float delta_time) {
    Vector2 next = pos;
    next.x += speed.x * delta_time;
    next.y += speed.y * delta_time;
    return next;
}

Reta* recToRetas(shapes::Rectangle rec) {
    Reta* p_retas = (Reta*)malloc(sizeof(Reta) * 4);

    p_retas[0] = {{rec.size.x, 0.0f}, {rec.pos.x - 20.0f, rec.pos.y - 20.0f}, {0.0f, 1.0f}};
    p_retas[1] = {{0.0f, rec.size.y}, {rec.pos.x - 20.0f, rec.pos.y - 20.0f}, {0.0f, 1.0f}};
    p_retas[2] = {{rec.size.x, 0.0f}, {rec.pos.x - 20.0f, rec.pos.y + 20.0f}, {0.0f, 1.0f}};
    p_retas[3] = {{0.0f, rec.size.y}, {rec.pos.x + 20.0f, rec.pos.y - 20.0f}, {0.0f, 1.0f}};

    return p_retas;
}

colRetaInfo shapes::checkColRetaRectangle(Reta reta, shapes::Rectangle rec) {
    Reta *p_retas = recToRetas(rec);
    colRetaInfo colls[4] = {checkIntRetas(reta, p_retas[0]),
                            checkIntRetas(reta, p_retas[1]),
                            checkIntRetas(reta, p_retas[2]),
                            checkIntRetas(reta, p_retas[3])};
    free(p_retas);
    colRetaInfo *p_menor = NULL;
    for (int i = 0; i < 4; i++) {
        if (!p_menor || (colls[i].coll && colls[i].t_reta_1 < p_menor->t_reta_1)) p_menor = &colls[i];
    }
    if (!p_menor) return (colRetaInfo){{0.0f, 0.0f}, 0.0f, 0.0f, 0, 0};
    if (p_menor->coll) printf("Coll: %.2f / %.2f, %.2f, %.2f, %d, %d\n", p_menor->point.x, p_menor->point.y, p_menor->t_reta_1, p_menor->t_reta_2, p_menor->parallel, p_menor->coll);
    return *p_menor;
}

char intercectionRetaCircle(Reta reta, Circle circle, float delta_time) {
    Vector2 next_pos_circle = {circle.pos.x + circle.speed.x * delta_time,
                               circle.pos.y + circle.speed.y * delta_time};

    // equação de segundo grau para achar t em P = A + tV
    float a = pow(reta.dir.x, 2) + pow(reta.dir.y, 2);
    float b = 2 * (reta.dir.x * (reta.point.x - next_pos_circle.x) +
                   reta.dir.y * (reta.point.y - next_pos_circle.y));
    float c = pow(reta.point.x - next_pos_circle.x, 2) +
              pow(reta.point.y - next_pos_circle.y, 2) -
              pow(circle.radio, 2);

    printf("(%.2f)x² + (%.2f)x + (%.2f)\n", a, b, c);

    float delta = pow(b, 2) - 4*a*c;
    printf("Delta = %.2f\n", delta);
    if (delta < 0.0f) return 0;

    float t_1 = -c/b, t_2 = -c/b; // solução primeiro grau
    if (a != 0.0f) t_1 = (-b + sqrt(delta)) / (2*a), t_2 = (-b - sqrt(delta)) / (2*a);

    Vector2 root_1 = {reta.point.x + t_1 * reta.dir.x,
                      reta.point.y + t_1 * reta.dir.y},
            root_2 = {reta.point.x + t_2 * reta.dir.x,
                      reta.point.y + t_2 * reta.dir.y};

    if (inDom(retaDominio(reta), root_1)) printf("root_1: %.2f / %.2f\n", root_1.x, root_1.y);
    if (inDom(retaDominio(reta), root_2)) printf("root_2: %.2f / %.2f\n", root_2.x, root_2.y);
        
    return ((inDom(retaDominio(reta), root_1) || inDom(retaDominio(reta), root_2)));
}

char simpleCollisionCircleRectangle(Circle *p_cir, shapes::Rectangle* p_rec, float delta_time) {
    Vector2 next_pos_rec = p_rec->nextPosition(delta_time),
            next_pos_cir = p_cir->nextPosition(delta_time);

    float total_dist = sqrt(pow(next_pos_rec.x - next_pos_cir.x, 2) +
                            pow(next_pos_rec.y - next_pos_cir.y, 2));

    return total_dist <= p_rec->recRadios() + p_cir->radio;
}

char preciseCollisionCircleRectangle(Circle *p_cir, shapes::Rectangle *p_rec, float delta_time) {
    Reta *p_retas = recToRetas(*p_rec);
    int col = 0;
    for (int i = 0; i < 4; i++) {
        col += intercectionRetaCircle(p_retas[i], *p_cir, delta_time);
    }
    free(p_retas);
    return col;
}

char shapes::collisionCircleRectangle(Circle *p_cir, shapes::Rectangle *p_rec, float delta_time) {
    //if (!Vector2Module(p_cir->speed) && !Vector2Module(p_rec->speed)) return 0;
    if (!simpleCollisionCircleRectangle(p_cir, p_rec, delta_time)) return 0;
    printf("precise check\n");
    if (!preciseCollisionCircleRectangle(p_cir, p_rec, delta_time)) return 0;
    printf("precise check pass\n");

    p_cir->speed.x = 0.0f;
    p_cir->speed.y = 0.0f;

    return 1;
}
