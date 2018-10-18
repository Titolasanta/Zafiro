//
// Created by tito on 11/10/18.
//

#include "xmlServer.h"
#include "../common/Logger.h"

extern Logger *gplogger;

void cargar_plataformas(pugi::xml_document &doc,Scene& scene, Model &modelo, int level, int limite_vertical, int limite_horizontal){
    gplogger->log(3,"se cargan plataformas para un nivel desde el xml");
    std::string nivel = "nivel";
    nivel.append(std::to_string(level));
    pugi::xml_node config = doc.first_child().child("escenarios").child(nivel.c_str());
    for (pugi::xml_node plataforma = config.child("plataforma"); plataforma; plataforma = plataforma.next_sibling("plataforma")){
        int xi = plataforma.child("xi").first_child().text().as_int();
        int xf = plataforma.child("xf").first_child().text().as_int();
        int y = plataforma.child("y").first_child().text().as_int();
        const char* tipo = plataforma.child("tipo").first_child().text().as_string();
        if (xi >= 0 && xf >=  0 && y >= -(limite_vertical - 600) && xi < xf && xi <= limite_horizontal && xf <= limite_horizontal && y <= 600) {
            if(!strcmp(tipo,"hierro")) {
                modelo.addPlataformHard(xi, y, xf - xi);
                scene.addPlatformMetal(xi, y, xf - xi);
            }else {
                if(!strcmp(tipo,"pasto")) {
                    scene.addPlatformGrass(xi, y, xf - xi);
                    modelo.addPlataformSoft(xi, y, xf - xi);
                } else if(!strcmp(tipo,"hielo")){
                    scene.addPlatformIce(xi, y, xf - xi);
                    modelo.addPlataformSoft(xi, y, xf - xi);
                }
            }
        }
        else gplogger->log(1, "Error al cargar una plataforma, el formato no era válido");

    }
    // modelo.addPlatformMetal(0, 550, limite_horizontal);
    //scene.addPlatformMetal(0,550,limite_horizontal);

}