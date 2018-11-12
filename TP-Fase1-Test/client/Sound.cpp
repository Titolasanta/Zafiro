//
// Created by antonella on 12/11/18.
//

#include "Sound.h"
#include "../common/Logger.h"
#include <SDL.h>
#include "../common/Exception.h"


#define MENU_MUSIC "../sounds/Menu.wav"
#define LEVEL_ONE_MUSIC "../sounds/LevelOne.wav"

#define LEVEL_TWO_MUSIC "../sounds/Menu.wav"
//#define LEVEL_TWO_MUSIC "../sounds/LevelTwo.wav"

#define LEVEL_THREE_MUSIC "../sounds/LevelOne.wav"
//#define LEVEL_THREE_MUSIC "../sounds/LevelThree.wav"

#define VICTORY_SFX "../sounds/Menu.wav"
//#define VICTORY_SFX "../sounds/Victory.wav"

#define DEATH_SFX "../sounds/Death.wav"
#define SHOOT_SFX "../sounds/Shoot.wav"

extern Logger* gplogger;

Sound::Sound() {
    if (!init()) throw Finalizo_conexion();
    if (!loadSounds()) throw Finalizo_conexion();
}

Sound::~Sound() {
    
    Mix_FreeMusic(menuMusic);
    Mix_FreeMusic(levelOneMusic);
    Mix_FreeMusic(levelTwoMusic);
    Mix_FreeMusic(levelThreeMusic);
    
    Mix_FreeChunk(victorySFX);
    Mix_FreeChunk(deathSFX);
    Mix_FreeChunk(shootSFX);
    
    menuMusic = nullptr;
    levelOneMusic = nullptr;
    levelTwoMusic = nullptr;
    levelThreeMusic = nullptr;
    
    victorySFX = nullptr;
    deathSFX = nullptr;
    shootSFX = nullptr;

    Mix_Quit();
}

bool Sound::init() {

    bool success = true;

    if(SDL_Init(SDL_INIT_AUDIO) < 0) {
        gplogger->log(1,"SDL could not initialize!");
        success = false;
    }
    if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048 < 0))  {
        gplogger->log(1,"SDL_mixer could not initialize!");
        success = false;
    }

    return success;
}

bool Sound::loadSounds() {

    bool success = true;

    //Load menu music
    if(!(menuMusic = Mix_LoadMUS(MENU_MUSIC))) {
        gplogger->log(1,"Failed to load menu music!");
        success = false;
    }

    //Load lvl1 music
    if(!(levelOneMusic = Mix_LoadMUS(LEVEL_ONE_MUSIC))) {
        gplogger->log(1,"Failed to load level 1 music!");
        success = false;
    }

    //Load lvl2 music
    if(!(levelTwoMusic = Mix_LoadMUS(LEVEL_TWO_MUSIC))) {
        gplogger->log(1,"Failed to load level 2 music!");
        success = false;
    }

    //Load lvl3 music
    if(!(levelThreeMusic = Mix_LoadMUS(LEVEL_THREE_MUSIC))) {
        gplogger->log(1,"Failed to load level 3 music!");
        success = false;
    }

    //Load death effect
    if(!(deathSFX = Mix_LoadWAV(DEATH_SFX))) {
        gplogger->log(1,"Failed to load death sound effect!");
        success = false;
    }

    //Load victory effects
    if(!(victorySFX = Mix_LoadWAV(VICTORY_SFX))) {
        gplogger->log(1,"Failed to load victory sound effect!");
        success = false;
    }

    //Load shoot effects
    if(!(shootSFX = Mix_LoadWAV(SHOOT_SFX))) {
        gplogger->log(1,"Failed to load shoot sound effect!");
        success = false;
    }

    return success;
}