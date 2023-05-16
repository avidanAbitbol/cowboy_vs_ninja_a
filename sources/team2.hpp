//
// Created by avida on 5/16/2023.
//

#ifndef COWBOY_VS_NINJA_A_TEAM2_H
#define COWBOY_VS_NINJA_A_TEAM2_H


#include "Team.hpp"

namespace ariel {

    class Team2 : public Team {
    public:
        Team2(Character *leader);
        void add(Character *character) override;
    };

} // ariel




#endif //COWBOY_VS_NINJA_A_TEAM2_H
