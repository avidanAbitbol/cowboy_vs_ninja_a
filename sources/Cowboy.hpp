//
// Created by avida on 5/15/2023.
//
#include "Character.hpp"

#ifndef COWBOY_VS_NINJA_A_COWBOY_H
#define COWBOY_VS_NINJA_A_COWBOY_H

namespace ariel {

    class Cowboy: public Character {
        int bullets;
    public:
        Cowboy(const string &name, const Point &location);
        string print()override;
        bool hasboolets();
        void reload();
        void shoot(Character *wasShot);
        ~Cowboy()override = default;
    };

} // ariel

#endif //COWBOY_VS_NINJA_A_COWBOY_H
