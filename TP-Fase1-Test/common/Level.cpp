//
// Created by fede on 21/09/18.
//

#include "Level.h"
#include "pugixml.hpp"
#include "xml.h"
#include "Logger.h"

extern pugi::xml_document* gXML_doc[2];
extern pugi::xml_parse_result* gXML_parse_result;
extern Logger *gplogger;

Level::Level(int n){

    level = n;
    height = get_level_height(*gXML_doc[0], *gXML_doc[1], n, *gXML_parse_result);
    width = get_level_width(*gXML_doc[0], *gXML_doc[1], n, *gXML_parse_result);
    gplogger->log(3,"Se crea clase Level");

}

int Level::getHeight(){
    return height;
}
int Level::getWidth(){
    return width;
}

int Level::getLevel() {
    return level;
}

Level Level::next() const {
    if(level == 3)
        throw "fin del juego\n";
    return std::move(Level(level+1));
}
