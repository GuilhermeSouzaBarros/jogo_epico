#include "../hpp/retas.hpp"
#include "../hpp/aux.hpp"

#include <stdio.h>

char inDom(Dominio dom, Vector2 point) {
    //printf("Dom: %.2f <= %.2f <= %.2f e ", dom.Dx.x, point.x, dom.Dx.y);
    //printf("%.2f <= %.2f <= %.2f\n", dom.Dy.x, point.y, dom.Dy.y);
    return (dom.Dx.x <= point.x && point.x <= dom.Dx.y) &&
           (dom.Dy.x <= point.y && point.y <= dom.Dy.y);
}

Dominio retaDominio (Reta reta) {
    Dominio dom= {{reta.point.x + reta.limit_t.x * reta.dir.x,
                   reta.point.x + reta.limit_t.y * reta.dir.x},
                  {reta.point.y + reta.limit_t.x * reta.dir.y,
                   reta.point.y + reta.limit_t.y * reta.dir.y}};
    if (dom.Dx.x > dom.Dx.y) {
        float aux = dom.Dx.x;
        dom.Dx.x = dom.Dx.y;
        dom.Dx.y = aux;
    }
    if (dom.Dy.x > dom.Dy.y) {
        float aux = dom.Dy.x;
        dom.Dy.x = dom.Dy.y;
        dom.Dy.y = aux;
    }
    return dom;
}

colRetaInfo checkIntRetas(Reta reta_1, Reta reta_2) {
    colRetaInfo info = {{0.0f, 0.0f}, 0.0f, 0.0f, 0, 0};

    float den = reta_1.dir.y * reta_2.dir.x -
                reta_1.dir.x * reta_2.dir.y;

    Vector2 vec_points = {reta_1.point.x - reta_2.point.x,
                          reta_1.point.y - reta_2.point.y};
    char is_parallel = reta_1.dir.x * vec_points.y == reta_1.dir.y * vec_points.y; 

    if (eq_z(den)) {
        info.parallel = 1;
        info.coll = is_parallel;
        return info;
    }

    Dominio dom_1 = retaDominio(reta_1), dom_2 = retaDominio(reta_2);
    
    float h = reta_1.dir.y * (reta_1.point.x - reta_2.point.x) -
              reta_1.dir.x * (reta_1.point.y - reta_2.point.y);
    h /= den;

    info.point.x = reta_2.dir.x * h + reta_2.point.x;
    info.point.y = reta_2.dir.y * h + reta_2.point.y;
    info.t_reta_2 = h;

    float t = 0.0f;
    if (reta_1.dir.x) t = (info.point.x - reta_1.point.x) / reta_1.dir.x;
    else t = (info.point.y - reta_1.point.y) / reta_1.dir.y;
    info.t_reta_1 = t;

    info.coll = inDom(dom_1, info.point) && inDom(dom_2, info.point);
    return info;
}
