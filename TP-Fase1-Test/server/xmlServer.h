//
// Created by tito on 11/10/18.
//

#ifndef TP_FASE1_TEST_XMLSERVER_H
#define TP_FASE1_TEST_XMLSERVER_H


#include "../common/pugixml.hpp"
#include "../common/Scene.h"
#include "Model.h"

void cargar_plataformas(pugi::xml_document &doc, Scene& scene, Model &modelo, int level, int limite_vertical, int limite_horizontal);

void cargar_users(pugi::xml_document &doc, std::list<std::string>&);

int get_cant_enemigos(pugi::xml_document &doc, pugi::xml_document &doc_default, int level, pugi::xml_parse_result result);


#endif //TP_FASE1_TEST_XMLSERVER_H
