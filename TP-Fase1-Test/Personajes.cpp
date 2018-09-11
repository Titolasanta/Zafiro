//
// Created by tito on 05/09/18.
//

#include <iostream>
#include "Personajes.h"
#include "SpriteRojo.h"

#define SPIRIT_PATH "sprites/NES - Contra - Bill Rizer & Lance Bean.png"


Personajes::Personajes(Window* window)
: rojo ( std::move(window->createImgTexture(0xFF, 0xFF, 0xFF) ) ),
  frameActualRojo(0)
{
rojo.loadFromFile(SPIRIT_PATH);
}

void Personajes::render(Scene scene) {
    if( scene.rojoMove() != 0) {
        frameActualRojo++;
    }
    SDL_Rect *currentClip = rojoFrames.mover( DER, frameActualRojo%ROJO_DER_FRAMES);
    rojo.render(scene.rojox(), scene.rojoy(), currentClip);

}