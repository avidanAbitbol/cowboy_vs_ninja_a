#include "sources/Cowboy.hpp"
#include "sources/TrainedNinja.hpp"
#include "sources/YoungNinja.hpp"
#include "sources/OldNinja.hpp"
#include "sources/Team.hpp"
#include "doctest.h"
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;
using namespace ariel;


TEST_CASE("Invalid Character Name") {
    CHECK_THROWS_AS(Cowboy("", Point(10, 20)), std::invalid_argument);
    CHECK_THROWS_AS(TrainedNinja(" ", Point(5, 15)), std::invalid_argument);
    CHECK_THROWS_AS(YoungNinja("Ninja", Point(2, 3)), std::invalid_argument);
    CHECK_THROWS_AS(OldNinja("$ensei", Point(8, 6)), std::invalid_argument);
}

TEST_CASE("Invalid Character Location") {
    CHECK_THROWS_AS(Cowboy("John", Point(-10, 20)), std::invalid_argument);
    CHECK_THROWS_AS(TrainedNinja("Hiroshi", Point(5, -15)), std::invalid_argument);
    CHECK_THROWS_AS(YoungNinja("Ryu", Point(-2, -3)), std::invalid_argument);
    CHECK_THROWS_AS(OldNinja("Sensei", Point(-8, 6)), std::invalid_argument);
}
TEST_CASE("Adding Duplicate Character to a Team") {
    Team team(new Cowboy("Tom", Point(10, 20)));
    CHECK_THROWS_AS(team.add(new Cowboy("Tom", Point(10, 20))), std::runtime_error);
}

TEST_CASE("Reload Cowboy's bullets") {
    Cowboy cowboy("John", Point(10, 20));
    Cowboy cowboy1("John", Point(10, 20));
    cowboy.shoot(&cowboy1);  // Consume a bullet
    cowboy.reload();
    CHECK(cowboy.hasboolets());
}

TEST_CASE("TrainedNinja slashes YoungNinja") {
    TrainedNinja ninja("Hiroshi", Point(5, 15));
    YoungNinja youngNinja("Ryu", Point(2, 3));
    ninja.slash(&youngNinja);
    CHECK_FALSE(youngNinja.isAlive());
}

TEST_CASE("Calculate distance between two points") {
    Point a(5, 5);
    Point b(10, 10);
    double distance = a.distance(b);
    CHECK(doctest::Approx(distance) == 7.07107);
}

TEST_CASE("Invalid Shoot Command") {
    Cowboy cowboy("John", Point(10, 20));
    CHECK_THROWS_AS(cowboy.shoot(&cowboy), std::runtime_error);
}

TEST_CASE("Team Attack with No Members") {
    Team teamA(nullptr);
    Team teamB(nullptr);
    CHECK_THROWS_AS(teamA.attack(&teamB), std::runtime_error);
}

TEST_CASE("Team Attack with One Member") {
    Cowboy *cow = new Cowboy("John", Point(10, 20));
    Team teamA(cow);
    Team teamB(nullptr);
    CHECK_THROWS_AS(teamA.attack(&teamB), std::runtime_error);
}

TEST_CASE("Create a Team with a Cowboy member") {
    Cowboy *cowb = new Cowboy("John", Point(10, 20));
    Cowboy *cowb1 = new Cowboy("John", Point(9, 19));
    Team team(cowb);
    CHECK_NOTHROW(team.add(cowb1));
    CHECK_NOTHROW(team.add(new Ninja("Hiroshi", Point(5, 15))));
}

TEST_CASE("Create a Team with multiple members") {
    TrainedNinja *ninja=new TrainedNinja("Hiroshi", Point(5, 15));
    Ninja *ninja1=new Ninja("Ryu", Point(2, 3));
    YoungNinja *ninja2=new YoungNinja("Ryu", Point(2, 3));
    OldNinja *ninja3=new OldNinja("Ryu", Point(2, 3));
    Cowboy *cowb = new Cowboy("John", Point(10, 20));
    Team team(cowb);
    CHECK_NOTHROW(team.add(ninja));
    CHECK_NOTHROW(team.add(ninja1));
    CHECK_NOTHROW(team.add(ninja2));
    CHECK_NOTHROW(team.add(ninja3));

}

TEST_CASE("Team attacks another Team") {
    Cowboy *cowboy1 = new Cowboy("John", Point(10, 20));
    Team teamA(cowboy1);
    TrainedNinja ninja("Hiroshi", Point(5, 15));
    Team teamB(new Ninja("Hiroshi", Point(5, 15)));
    CHECK_NOTHROW(teamA.attack(&teamB));
    CHECK_FALSE(ninja.isAlive());
}

TEST_CASE("Check Team's remaining members") {
    Cowboy *cowboy2 = new Cowboy("Tom", Point(15, 25));
    Cowboy *cowboy1 = new Cowboy("John", Point(10, 20));
    Team team(cowboy1);
    team.add(cowboy2);

    CHECK(team.stillAlive() == 2);

    cowboy1->hit(3);  // Cowboy1 is no longer alive
    CHECK(team.stillAlive() == 1);

    cowboy2->hit(5);  // Cowboy2 is no longer alive
    CHECK(team.stillAlive() == 0);
}

TEST_CASE("Cowboy is not in two teams simultaneously") {
    Cowboy *cowboy1 = new Cowboy("John", Point(10, 20));
    Team teamA(cowboy1);
    Cowboy *cowboy2 = new Cowboy("Tom", Point(15, 25));
    Team teamB(cowboy2);
}

TEST_CASE("Complex Battle Simulation") {
    // Team A
    TrainedNinja *ninja1=new TrainedNinja("Hiroshi", Point(5, 15));
    YoungNinja *ninja2=new YoungNinja("Ryu", Point(2, 3));
    Team teamA(new Cowboy("John", Point(10, 20)));
    teamA.add(ninja1);
    teamA.add(ninja2);

    // Team B
    TrainedNinja *ninja4=new TrainedNinja("Akira", Point(12, 18));
    OldNinja *ninja3 = new OldNinja("Sensei", Point(8, 6));
    Team teamB(ninja3);
    teamB.add(ninja4);


    // Battle simulation
    while (teamA.stillAlive() > 0 && teamB.stillAlive() > 0) {
        teamA.attack(&teamB);
        teamB.attack(&teamA);
    }

    // Check remaining members and winner
    CHECK(teamA.stillAlive() == 0);
    CHECK(teamB.stillAlive() > 0);
    if (teamB.stillAlive() > 0) {
        INFO("Winner is Team B");
    } else {
        INFO("Winner is Team A");
    }
}

TEST_CASE("Multi-Team Battle Simulation") {
    // Team A
    TrainedNinja *ninja1=new TrainedNinja("Hiroshi", Point(5, 15));
    Cowboy *cowboy1 = new Cowboy("John", Point(10, 20));
    Team teamA(cowboy1);
    teamA.add(ninja1);

    // Team B
    OldNinja *ninja2 = new OldNinja("Sensei", Point(8, 6));
    Team teamB(ninja2);

    // Team C
    TrainedNinja *ninja3=new TrainedNinja("Akira", Point(6, 12));
    Cowboy *cowboy2 = new Cowboy("Tom", Point(12, 18));
    Team teamC(cowboy2);
    teamC.add(ninja3);

    // Battle simulation
    while (teamA.stillAlive() > 0 && teamB.stillAlive() > 0 && teamC.stillAlive() > 0) {
        teamA.attack(&teamB);
        teamB.attack(&teamC);
        teamC.attack(&teamA);
    }

    // Check remaining members and winner
    CHECK(teamA.stillAlive() == 0);
    CHECK(teamB.stillAlive() == 0);
    CHECK(teamC.stillAlive() > 0);
    if (teamC.stillAlive() > 0) {
        INFO("Winner is Team C");
    }
}

TEST_CASE("Survival Test with Healing") {
    Cowboy cowboy("John", Point(10, 20));
    OldNinja ninja("Sensei", Point(8, 6));

    // Initial status
    CHECK(cowboy.isAlive());
    CHECK(ninja.isAlive());

    while (cowboy.isAlive() && ninja.isAlive()) {
        cowboy.shoot(&ninja);
    }

    // Check final status and winner
    CHECK_FALSE(cowboy.isAlive());
    CHECK(ninja.isAlive());
    INFO("Winner is Ninja");
}

TEST_CASE("Team Collaboration Test") {
    TrainedNinja *ninja=new TrainedNinja("Hiroshi", Point(5, 15));
    Cowboy *cowboy1 = new Cowboy("john", Point(10, 20));
    Team team(cowboy1);
    team.add(ninja);

    // Coordinate attack and movement
    cowboy1->shoot(ninja);
    ninja->move(cowboy1);

    // Check updated status
    CHECK_FALSE(ninja->isAlive());
}

TEST_CASE("Multiple Attacks and Hits") {
    Cowboy cowboy("John", Point(10, 20));
    TrainedNinja ninja("Hiroshi", Point(5, 15));

    // Initial status
    CHECK(cowboy.isAlive());
    CHECK(ninja.isAlive());

    // Multiple attacks and hits
    cowboy.shoot(&ninja);
    ninja.hit(3);
    cowboy.shoot(&ninja);
    ninja.hit(2);
    cowboy.shoot(&ninja);
    ninja.hit(1);

    // Check final status and winner
    CHECK_FALSE(cowboy.isAlive());
    CHECK_FALSE(ninja.isAlive());
    INFO("It's a tie!");
}

TEST_CASE("Team Collaboration Test") {
    TrainedNinja *ninja=new TrainedNinja("Hiroshi", Point(5, 15));
    Cowboy *cowboy1 = new Cowboy("john", Point(10, 20));
    Team team(cowboy1);
    team.add(ninja);

    // Coordinate attack and movement
    cowboy1->shoot(ninja);
    ninja->move(cowboy1);

    // Check updated status
    CHECK_FALSE(ninja->isAlive());
}

TEST_CASE("Multiple Attacks and Hits") {
    Cowboy cowboy("John", Point(10, 20));
    TrainedNinja ninja("Hiroshi", Point(5, 15));

    // Initial status
    CHECK(cowboy.isAlive());
    CHECK(ninja.isAlive());

    // Multiple attacks and hits
    cowboy.shoot(&ninja);
    ninja.hit(3);
    cowboy.shoot(&ninja);
    ninja.hit(2);
    cowboy.shoot(&ninja);
    ninja.hit(1);

    // Check final status and winner
    CHECK_FALSE(cowboy.isAlive());
    CHECK_FALSE(ninja.isAlive());
    INFO("It's a tie!");
}

