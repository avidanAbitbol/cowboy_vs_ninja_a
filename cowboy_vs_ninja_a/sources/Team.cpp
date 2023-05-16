//
// Created by avida on 5/15/2023.
//

#include "Team.hpp"

namespace ariel {

    Team::Team(Character *leader) {
        this->leader = leader;
        team.push_back(leader);
    }

    void Team::add(Character *c) {
        team.push_back(c);

    }

    int Team::stillAlive() {
    return 0;
    }

    void Team::attack(Team *c) {
      
    }

    void Team::print() {

    }
Team::~Team(){
      for(auto &c:team){
          delete c;
      }
    }
}
