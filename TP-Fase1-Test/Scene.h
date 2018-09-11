//
// Created by tito on 05/09/18.
//

#ifndef TP_FASE1_TEST_SCENE_H
#define TP_FASE1_TEST_SCENE_H


class Scene {
public:
    Scene();

    explicit Scene(int i);

    int rojox();

    void rojox(int i);
    int rojoy();

    bool rojoMove();

    void rojoNotMove();
    void rojoMove(int i);
private:
    int rojoX = 0;
    bool rojoM = 0;

};


#endif //TP_FASE1_TEST_SCENE_H
