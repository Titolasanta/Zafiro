//
// Created by tito on 05/09/18.
//

#ifndef TP_FASE1_TEST_SCENE_H
#define TP_FASE1_TEST_SCENE_H
enum PJSTATE{MOVING,AIR,GROUND};

class Scene {
public:
    Scene();

    //geter
    int rojox();

    int rojoy();

    int rojoState();

    //seter
    void rojoNotMove();

    void rojoMove(int i);
private:
    int rojoX = 0;
    int state = GROUND;

};


#endif //TP_FASE1_TEST_SCENE_H
