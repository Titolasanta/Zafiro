//
// Created by tito on 04/09/18.
//

#include <iostream>
#include "SpriteRojo.h"

SDL_Rect* SpriteRojo::mover(int dirreccion, int frame){

    return &posiciones[dirreccion][frame];

    }

    
SpriteRojo::SpriteRojo()
: posiciones { { {1,43,26,35},
                 {18,43,19,35},
                 {38,47,20,31},
                 {59,44,19,35},
                 {76,44,18,34},
                 {95,47,20,31} } }
                 {}
