//
// Created by tito on 04/09/18.
//

#include <iostream>
#include "SpriteRojo.h"

SDL_Rect* SpriteRojo::mover(int dirreccion, int frame){

    return &frameMoviemiento[dirreccion][frame];

    }
    SDL_Rect* SpriteRojo::quieto(){

        return &parado;
}

    
SpriteRojo::SpriteRojo()
: frameMoviemiento { {{1,43,16,35}, //Corriendo hacia adelante
                      {18,43,19,35}, //(segunda linea sprite sheet)
                      {38,47,20,31},
                      {59,44,16,34},
                      {76,44,18,34},
                      {95,47,20,31} },
                     {{1,149,16,35}, //apuntando hacia arriba
                      {18,149,19,35}, // (quinta linea sprite sheet)
                      {38,151,20,33},
                      {1,221,20,35}, //apuntando hacia abajo
                      {22,221,21,35}, // (septima linea sprite sheet)
                      {44,223,21,33} }

                      },
parado{0,8,23,34}
                 {}
