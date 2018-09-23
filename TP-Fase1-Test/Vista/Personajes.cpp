//
// Created by tito on 05/09/18.
//

#include <iostream>
#include "Personajes.h"
#include "Sprite.h"
#include "Logger.h"

#define SPIRIT_PATH "sprites/NES - Contra - Bill Rizer & Lance Bean.png"

extern Logger *gplogger;

Personajes::Personajes(Window* window)
: rojo ( std::move(window->createImgTexture(0xFF, 0xFF, 0xFF) ) ),
  frameActualRojo(0)
{
    rojo.loadFromFile(SPIRIT_PATH);
    gplogger->log(1,"Se crea Personajes\n");
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
        currentClip = rojoFrames.move(0, frameActualRojo % ROJO_DER_FRAMES);

    if (scene.isP1Crouching()) {
        currentClip = rojoFrames.move(1, frameActualRojo % 3 + 3); //PLACEHOLDER
    }

    if (scene.isP1Airborne()){
        currentClip = rojoFrames.move(2, frameActualRojo % 3 + 3);
    }
    rojo.render(scene.getP1PositionX() - cameraX, scene.getP1PositionY() - cameraY, currentClip, angle);
}
       /* switch ( scene.rojoState() )
        {
            case MOVING_RIGHT: {
                //if(!scene.rojoInAir())
                    frameActualRojo++;
                SDL_Rect *currentClip = rojoFrames.mover(DER, frameActualRojo % ROJO_DER_FRAMES);
                rojo.render(scene.rojox(), scene.rojoy(), currentClip);
                break;
            }case MOVING_LEFT: {
                frameActualRojo++;
                SDL_Rect *currentClip = rojoFrames.mover(DER, frameActualRojo % ROJO_DER_FRAMES);
                rojo.render(scene.rojox(), scene.rojoy(), currentClip, 180);
                break;
            }case STANDING_LEFT: {
                SDL_Rect *currentClip = rojoFrames.quieto();
                rojo.render(scene.rojox(), scene.rojoy(), currentClip,180);
                break;
            }case STANDING_RIGHT: {
                SDL_Rect *currentClip = rojoFrames.quieto();
                rojo.render(scene.rojox(), scene.rojoy(), currentClip);
                break;
            }case IN_AIR_RIGHT:{
                SDL_Rect *currentClip = rojoFrames.quieto();
                rojo.render(scene.rojox(), scene.rojoy(), currentClip);
                break;
            }case IN_AIR_LEFT: {
                SDL_Rect *currentClip = rojoFrames.quieto();
                rojo.render(scene.rojox(), scene.rojoy(), currentClip, 180);
                break;
            }case AIM_UP_R: {
                frameActualRojo++;
                SDL_Rect *currentClip = rojoFrames.mover(1,frameActualRojo % 3);
                rojo.render(scene.rojox(), scene.rojoy(), currentClip);
                break;
            }case AIM_DOWN_R: {
                frameActualRojo++;
                SDL_Rect *currentClip = rojoFrames.mover(1,frameActualRojo % 3 + 3);
                rojo.render(scene.rojox(), scene.rojoy(), currentClip);
                break;
            }case AIM_UP_L: {
                frameActualRojo++;
                SDL_Rect *currentClip = rojoFrames.mover(1,frameActualRojo % 3);
                rojo.render(scene.rojox(), scene.rojoy(), currentClip,180);
                break;
            }case AIM_DOWN_L: {
                frameActualRojo++;
                SDL_Rect *currentClip = rojoFrames.move(1,frameActualRojo % 3 + 3);
                rojo.render(scene.rojox(), scene.rojoy(), currentClip,180);
                break;
            }default:
                break;

            //error
        }
*/