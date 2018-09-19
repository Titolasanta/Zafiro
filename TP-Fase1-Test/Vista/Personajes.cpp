//
// Created by tito on 05/09/18.
//

#include <iostream>
#include "Personajes.h"
#include "SpriteRojo.h"
#include "Logger.h"

#define SPIRIT_PATH "sprites/NES - Contra - Bill Rizer & Lance Bean.png"

extern Logger *gplogger;

Personajes::Personajes(Window* window)
: rojo ( std::move(window->createImgTexture(0xFF, 0xFF, 0xFF) ) ),
  frameActualRojo(0)
{
    rojo.loadFromFile(SPIRIT_PATH);
    gplogger->log(1,"se crea Personajes\n");
}

void Personajes::render(Scene scene)
{
    if (scene.isP1Walking())
        frameActualRojo++;
    else
        frameActualRojo = 0;

    SDL_Rect *currentClip;
    int angulo;

    if(scene.isP1LookingRight())
        angulo = 0;
    else
        angulo = 180;



        if (scene.getP1AimDirection() == -1)
            currentClip = rojoFrames.mover(1, frameActualRojo % 3);
        else if (scene.getP1AimDirection() == 1)
            currentClip = rojoFrames.mover(1, frameActualRojo % 3 + 3);
        else
            currentClip = rojoFrames.mover(0, frameActualRojo % ROJO_DER_FRAMES);
    rojo.render(scene.getP1PositionX(), scene.getP1PositionY(), currentClip,angulo);



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
                SDL_Rect *currentClip = rojoFrames.mover(1,frameActualRojo % 3 + 3);
                rojo.render(scene.rojox(), scene.rojoy(), currentClip,180);
                break;
            }default:
                break;

            //error
        }
*/

    }