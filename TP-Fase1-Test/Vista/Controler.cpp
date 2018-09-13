//
// Created by tito on 13/09/18.
//

#include "Controler.h"

Controler::Controler(View &view, dumyModel& model) : view(view),model(model){}

void Controler::proces_event(SDL_Event e) {
    model.proces_event(e);
}

void Controler::show() {
    model.update(scene);
    view.render(scene);
}