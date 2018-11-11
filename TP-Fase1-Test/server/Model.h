//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_MODEL_H
#define TP_FASE1_TEST_MODEL_H


#include <SDL_events.h>
#include <mutex>
#include "Character.h"
#include "../common/Projectile.h"
#include "../common/Level.h"
#include "../common/Scene.h"

class Model {
    
private:
    Level level;
    Character *players[4];
    std::list<Projectile> lBullets;
    Character player1;
    Character player2;
    Character player3;
    Character player4;
    int currentPlayers = 0;
    int maxPlayers;
    std::mutex mutex;
    bool jugadorGrisado[4] = {true,true,true,true};
    bool jugadorReconectado[4] = {false, false, false, false};
    bool maxPlayersReached = false;
    
public:
    explicit Model(int initialLevel);
    ~Model() = default;
    void createCharacter(int);
    int getMaxPlayers();
    int getCurrentPlayers();
    void update(Scene&);
    void moveRight(int);
    void moveLeft(int);
    void aimDown(int);
    void aimStraight(int);
    void aimUp(int);
    void stop(int);
    void jump(int);
    void time();
    bool endOfLevel(Scene&);
    std::list<std::tuple<int,int,int>> lPlataformsSoft;
    std::list<std::tuple<int,int,int>> lPlataformsHard;
    void addPlataformSoft(int x, int y, int w);
    void addPlataformHard(int x, int y, int w);
    void changeLevel(Level,Scene&);
    void crouch(int);
    void stand(int);
    int getLevelWidth();
    int getLevelHeight();
    void shoot(int);
    void stopShooting(int);
    void bajaJugador(int currentPlayers);
    bool getMaxPlayersReached();
    void rejoinCharacter(int id);
    void placeCamera(Scene&);
    int XMasChico(Scene&);
    int YMasGrande(Scene&);
    void setEnemies(Scene&);
    void moveEnemies(Scene&);
    void enemyCollision(Enemy&,Scene&);
    //const Level &getLevel() const;
    void respawn(int,SDL_Rect*);
    const bool *getJugadorGrisado() const;
};


#endif //TP_FASE1_TEST_MODEL_H
