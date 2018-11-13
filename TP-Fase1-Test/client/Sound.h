//
// Created by antonella on 12/11/18.
//

#ifndef TP_FASE1_TEST_SOUND_H
#define TP_FASE1_TEST_SOUND_H


#include <SDL_mixer.h>

class Sound {

private:

    //The music that will be played
    Mix_Music* menuMusic = nullptr;
    Mix_Music* levelOneMusic = nullptr;
    Mix_Music* levelTwoMusic = nullptr;
    Mix_Music* levelThreeMusic = nullptr;

    //The sound effects that will be used
    Mix_Chunk* victorySFX = nullptr;
    Mix_Chunk* deathSFX = nullptr;
    Mix_Chunk* shootSFX = nullptr;

public:

    Sound();
    ~Sound();
    bool init();
    bool loadSounds();

    Mix_Music* getMenuMusic() { return menuMusic; }
    Mix_Music* getLevelOneMusic() { return levelOneMusic; }
    Mix_Music* getLevelTwoMusic() { return levelTwoMusic; }
    Mix_Music* getLevelThreeMusic() { return levelThreeMusic; }

    Mix_Chunk* getVictorySFX() { return victorySFX; }
    Mix_Chunk* getDeathSFX() { return deathSFX; }
    Mix_Chunk* getShootSFX() { return shootSFX; }

};


#endif //TP_FASE1_TEST_SOUND_H
