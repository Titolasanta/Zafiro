//
// Created by tito on 05/09/18.
//

#include <iostream>
#include "Personajes.h"
#include "Sprite.h"
#include "Logger.h"

#define SPIRIT_PATH "../spirites/NES-Contra-BillRizerLanceBeanmod.png"

#define characterWidth 20

extern Logger *gplogger;

Personajes::Personajes(Window* window)
: rojo ( std::move(window->createImgTexture(0xFF, 0xFF, 0xFF) ) ),
  frameActualRojo(0)
{
    rojo.loadFromFile(SPIRIT_PATH);
    gplogger->log(3,"Se crea Personajes de la vista");
}

void Personajes::render(Scene scene, int cameraX, int cameraY) {

    if (scene.isP1Walking() || scene.isP1Airborne())
        frameActualRojo++;
    else
        frameActualRojo = 0;

    SDL_Rect *currentClip;
    int angle;

    if (scene.isP1LookingRight())
        angle = 0;
    else
        angle = 180;


    if (scene.getP1AimDirection() == -1)
        currentClip = rojoFrames.move(1, frameActualRojo % 3);
    else if (scene.getP1AimDirection() == 1)
        currentClip = rojoFrames.move(1, frameActualRojo % 3 + 3);
    else
        if(!scene.isP1Walking())
            currentClip = rojoFrames.quieto();
        else
            currentClip = rojoFrames.move(0, frameActualRojo % 6);
    if (scene.isP1Crouching()) {
        currentClip = rojoFrames.getFaceDown();
    }

    if (scene.isP1Shooting()&&!scene.isP1Crouching()){
        currentClip = rojoFrames.move(3,   frameActualRojo % 3  );
    }

    if (scene.isP1Airborne()){
        currentClip = rojoFrames.move(2,   frameActualRojo % 4  );
    }

    rojo.render(scene.getP1PositionX() - cameraX -characterWidth/2, scene.getP1PositionY() - cameraY, currentClip, angle);
}
