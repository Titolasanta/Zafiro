//
// Created by fede on 21/09/18.
//

#include "Nivel.h"

Nivel::Nivel(int n, int alto, int ancho){
    level = n;
    height = alto;
    width = ancho;
}
int Nivel::getHeight(){
    return height;
}
int Nivel::getWidth(){
    return width;
}