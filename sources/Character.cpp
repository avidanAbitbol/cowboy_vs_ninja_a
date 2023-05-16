//
// Created by avida on 5/15/2023.
//
#include "Point.hpp"
#include "Character.hpp"

namespace ariel {
    Character::Character(const string &name, const Point &location) : name(name), location(location) {
        this->name = name;
        this->location = location;
    }
    string Character::getName(){
        return name;
    }
    void Character::setLocation(Point location){

    }
    Point Character::getLocation(){
        return location;
    }
    bool Character::isAlive()const {
        return islive;
    }
    double Character::distance(Point p){
        return 0.0;
    }
    void Character::hit(int damage){

    }


} // ariel