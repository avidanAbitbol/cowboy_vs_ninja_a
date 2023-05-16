//
// Created by avida on 5/15/2023.
//
#include "Point.hpp"

#ifndef COWBOY_VS_NINJA_A_CHARACTER_H
#define COWBOY_VS_NINJA_A_CHARACTER_H

namespace ariel {

    class Character {
        Point location ;
    bool islive;
    string name;
    public:
        Character(const string &name, const Point &location);
        string getName();
        void setLocation(Point location);
        Point getLocation();
        bool isAlive()const;
        double distance(Point p);
        void hit(int damage);
        virtual string print()=0;
        virtual ~Character()=default;
    };

} // ariel

#endif //COWBOY_VS_NINJA_A_CHARACTER_H
