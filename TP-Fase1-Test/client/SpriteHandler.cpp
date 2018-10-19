//
// Created by tito on 05/09/18.
//

#include <iostream>
#include "SpriteHandler.h"
#include "Sprite.h"
#include "../common/Logger.h"

#define SPRITE_PATH "../spirites/sprites.png"

#define characterWidth 20

extern Logger *gplogger;

SpriteHandler::SpriteHandler(Window* window) : spriteTexture(std::move(window->createImgTexture(0xFF, 0xFF, 0xFF))){
    spriteTexture.loadFromFile(SPRITE_PATH);
    gplogger->log(3,"Se crea SpriteHandler de la vista");
}

void SpriteHandler::render(Scene &scene, int cameraX, int cameraY) {

    for (int i = 0; i < scene.getCurrentPlayers(); i++) {
        if (scene.isWalking(i) || scene.isAirborne(i))
            currentFrame[i]++;
        else
            currentFrame[i] = 0;

        SDL_Rect *currentClip;
        int angle;

        if (scene.isLookingRight(i))
            angle = 0;
        else
            angle = 180;

        if (scene.getAimDirection(i) == -1)
            currentClip = spritePositionHandler.move(1, currentFrame[i] % 3);
        else if (scene.getAimDirection(i) == 1)
            currentClip = spritePositionHandler.move(1, currentFrame[i] % 3 + 3);
        else {
            if (!scene.isWalking(i))
                currentClip = spritePositionHandler.move(3, currentFrame[i] % 3);
            else
                currentClip = spritePositionHandler.move(0, currentFrame[i] % 6);
            if (scene.isShooting(i) && !scene.isCrouching(i))
                currentClip = spritePositionHandler.move(3, currentFrame[i] % 3);
        }
        if (scene.isCrouching(i))
            currentClip = spritePositionHandler.getFaceDown();

        if (scene.isAirborne(i)) {
            currentClip = spritePositionHandler.move(2, currentFrame[i] % 4);
        }

        spriteTexture.render(scene.getPositionX(i) - cameraX - characterWidth / 2, scene.getPositionY(i) - cameraY,
                             currentClip, angle);
    }
}
