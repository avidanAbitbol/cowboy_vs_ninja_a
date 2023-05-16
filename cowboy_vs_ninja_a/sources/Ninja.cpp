//
// Created by avida on 5/15/2023.
//

#include "Ninja.hpp"

namespace ariel {
    Ninja::Ninja(const string &name, const Point &location) : Character(name, location) {

    }
    void Ninja::move(const Character *player){

    }
    void Ninja::slash(Character *someCharacter){

    }
    string Ninja::print(){
        return "N";
    }


} // ariel