//
// Created by tito on 04/09/18.
//

#include <iostream>
#include "Sprite.h"

SDL_Rect* Sprite::move(int direccion, int frame) {
    return &frameMoviemiento[direccion][frame];
}

SDL_Rect* Sprite::quieto() {
    return &parado;
}

SDL_Rect* Sprite::getFaceDown() {
    return &faceDown;
}

SDL_Rect* Sprite::getGrisado(){
    return &grisado;
}

SDL_Rect* Sprite::getMuerto() {
    return &muerto;
}

SDL_Rect* Sprite::getMovingEnemySprite(int direccion) {
    return &movingEnemies[direccion];
}

SDL_Rect* Sprite::getStaticEnemySprite(int direccion) {
    return &staticEnemies[direccion];
}

Sprite::Sprite()
: frameMoviemiento { {{2,86,32,70}, //Corriendo hacia adelante
                      {36,86,38,35*2}, //(segunda linea sprite sheet)
                      {38*2,47*2,20*2,31*2},
                      {59*2,44*2,16*2,34*2},
                      {76*2,44*2,18*2,34*2},
                      {95*2,47*2,20*2,31*2} },
                     {{1*2,149*2,16*2,35*2}, //apuntando hacia arriba
                      {18*2,149*2,19*2,35*2}, // (quinta linea sprite sheet)
                      {38*2,151*2,20*2,33*2},
                      {1*2,221*2,20*2,35*2}, //apuntando hacia abajo
                      {22*2,221*2,21*2,35*2}, // (septima linea sprite sheet)
                      {44*2,223*2,21*2,33*2} },

                     {{117*2,52*2,16*2,20*2},//secuencia de salto
                      {135*2,44*2,20*2,26*2},
                      {157*2,52*2,16*2,20*2},
                      {157*2,54*2,17*2,16*2},
                      {0,0,0,0},
                      {0,0,0,0}},

                     {{1*2,79*2,23*2,34*2},//secuencia de salto
                      {25*2,79*2,25*2,34*2},
                      {51*2,81*2,25*2,32*2},
                      {0*2,0*2,0*2,0*2},
                      {0,0,0,0},
                      {0,0,0,0}},

                     {{156, 188, 46, 30}, //secuencia de salto muerto
                      {208, 180, 30, 46},
                      {244, 188, 46, 30},
                      {296, 180, 30, 46},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}}
                      },
parado{0*2,8*2,23*2,34*2},
faceDown{79*2,25*2,32*2,16*2},
grisado{2, 592, 46, 68},
muerto{336, 206, 64, 20},
movingEnemies{
        {0,2,32,62}, //Corriendo hacia adelante
        {38,0,32,64}, //(segunda linea sprite sheet)
        {74,0,30,64},
        {108,2,32,64},
        {144,0,32,64},
        {180,0,32,64}
},
staticEnemies{
    {0, 152, 64, 64},
    {136, 152, 64, 64},
    {272, 152, 64, 64},
    {0, 220, 64, 64},
    {136, 220, 64, 64},
    {272, 220, 64, 64},
    {0, 288, 64, 64},
    {136, 288, 64, 64},
    {272, 288, 64, 64},
    {0, 356, 64, 64},
    {136, 356, 64, 64},
    {272, 356, 64, 64}
}

                 {}
