#ifndef RETAS
#define RETAS

#include "raylib.h"

typedef struct reta_Dominio {
    Vector2 Dx;
    Vector2 Dy;
} Dominio;

typedef struct Reta {
    Vector2 dir;
    Vector2 point;
    Vector2 limit_t; // {t e R | x <= t <= y}
} Reta;

typedef struct colRetaInfo {
    Vector2 point;
    float t_reta_1;
    float t_reta_2;
    char parallel;
    char coll;
} colRetaInfo;

char        inDom         (Dominio dom, Vector2 point);
Dominio     retaDominio   (Reta reta);
colRetaInfo checkIntRetas (Reta reta_1, Reta reta_2);

#endif