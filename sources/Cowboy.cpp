//
// Created by avida on 5/15/2023.
//

#include "Cowboy.hpp"

namespace ariel {
    Cowboy::Cowboy(const string &name, const Point &location) : Character(name, location) {

    }
    string Cowboy::print(){
        return "C";
    }
    bool Cowboy::hasboolets(){
        return bullets > 0;
    }
    void Cowboy::shoot(Character *wasShot){
        if (hasboolets()) {
            bullets--;
        }
    }

    void Cowboy::reload(){
        bullets = 6;
    }


} // ariel