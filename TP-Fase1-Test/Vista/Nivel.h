//
// Created by fede on 21/09/18.
//

#ifndef TP_FASE1_TEST_NIVEL_H
#define TP_FASE1_TEST_NIVEL_H


class Nivel {
private:
    int level;
    int height;
    int width;
public:
    Nivel(int n, int alto, int ancho);
    int getHeight();
    int getWidth();
};


#endif //TP_FASE1_TEST_NIVEL_H
