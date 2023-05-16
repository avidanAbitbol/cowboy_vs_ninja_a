//
// Created by avida on 5/15/2023.
//
#include "Character.hpp"

#ifndef COWBOY_VS_NINJA_A_NINJA_H
#define COWBOY_VS_NINJA_A_NINJA_H

namespace ariel {

    class Ninja : public Character {
        int speed;
    public:
        Ninja(const string &name, const Point &location);
        void move(const Character *player);
        void slash(Character *other);
        string print()override;
        ~Ninja()override = default;
    };

} // ariel

#endif //COWBOY_VS_NINJA_A_NINJA_H
