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
    Cowboy cowboy("John", Point(10, 20));
    Team team(nullptr);
    team.add(&cowboy);
    CHECK_THROWS_AS(team.add(&cowboy), std::runtime_error);
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
    Cowboy cowboy("John", Point(10, 20));
    Team teamA(nullptr);
    Team teamB(nullptr);
    teamA.add(&cowboy);
    CHECK_THROWS_AS(teamA.attack(&teamB), std::runtime_error);
}
TEST_CASE("Create a Team with a Cowboy member") {
Cowboy cowboy("John", Point(10, 20));
Team team(nullptr);
CHECK_NOTHROW(team.add(&cowboy));
TrainedNinja ninja("Hiroshi", Point(5, 15));
CHECK_NOTHROW(team.add(&ninja));
}

TEST_CASE("Create a Team with multiple members") {
Cowboy cowboy("John", Point(10, 20));
TrainedNinja ninja("Hiroshi", Point(5, 15));
Ninja ninja1("Ryu", Point(2, 3));
YoungNinja ninja2("Ryu", Point(2, 3));
OldNinja ninja3("Ryu", Point(2, 3));
Team team(nullptr);
CHECK_NOTHROW(team.add(&cowboy));
CHECK_NOTHROW(team.add(&ninja));
CHECK_NOTHROW(team.add(&ninja1));
CHECK_NOTHROW(team.add(&ninja2));
CHECK_NOTHROW(team.add(&ninja3));

}
TEST_CASE("Team attacks another Team") {
Cowboy cowboy("John", Point(10, 20));
TrainedNinja ninja("Hiroshi", Point(5, 15));
Team teamA(nullptr), teamB(nullptr);
teamA.add(&cowboy);
teamB.add(&ninja);
CHECK_NOTHROW(teamA.attack(&teamB));
CHECK_FALSE(ninja.isAlive());
}

TEST_CASE("Check Team's remaining members") {
Cowboy cowboy1("John", Point(10, 20));
Cowboy cowboy2("Tom", Point(15, 25));
Team team(nullptr);
team.add(&cowboy1);
team.add(&cowboy2);

CHECK(team.stillAlive() == 2);

cowboy1.hit(3);  // Cowboy1 is no longer alive
CHECK(team.stillAlive() == 1);

cowboy2.hit(5);  // Cowboy2 is no longer alive
CHECK(team.stillAlive() == 0);
}

TEST_CASE("Cowboy is not in two teams simultaneously") {
Cowboy cowboy("John", Point(10, 20));
Team teamA(nullptr), teamB(nullptr);
teamA.add(&cowboy);
CHECK_THROWS(teamB.add(&cowboy));
}
TEST_CASE("Complex Battle Simulation") {
    // Team A
    Cowboy cowboy1("John", Point(10, 20));
    TrainedNinja ninja1("Hiroshi", Point(5, 15));
    YoungNinja ninja2("Ryu", Point(2, 3));
    Team teamA(nullptr);
    teamA.add(&cowboy1);
    teamA.add(&ninja1);
    teamA.add(&ninja2);

    // Team B
    OldNinja ninja3("Sensei", Point(8, 6));
    TrainedNinja ninja4("Akira", Point(12, 18));
    Team teamB(nullptr);
    teamB.add(&ninja3);
    teamB.add(&ninja4);


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
    Cowboy cowboy1("John", Point(10, 20));
    TrainedNinja ninja1("Hiroshi", Point(5, 15));
    Team teamA(nullptr);
    teamA.add(&cowboy1);
    teamA.add(&ninja1);

    // Team B
    OldNinja ninja2("Sensei", Point(8, 6));
    Team teamB(nullptr);
    teamB.add(&ninja2);

    // Team C
    Cowboy cowboy2("Tom", Point(12, 18));
    TrainedNinja ninja3("Akira", Point(6, 12));
    Team teamC(nullptr);
    teamC.add(&cowboy2);
    teamC.add(&ninja3);

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
    Cowboy cowboy("John", Point(10, 20));
    TrainedNinja ninja("Hiroshi", Point(5, 15));
    Team team(nullptr);
    team.add(&cowboy);
    team.add(&ninja);

    // Coordinate attack and movement
    cowboy.shoot(&ninja);
    ninja.move(&cowboy);

    // Check updated status
    CHECK_FALSE(ninja.isAlive());
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
    Cowboy cowboy("John", Point(10, 20));
    TrainedNinja ninja("Hiroshi", Point(5, 15));
    Team team(nullptr);
    team.add(&cowboy);
    team.add(&ninja);

    // Coordinate attack and movement
    cowboy.shoot(&ninja);
    ninja.move(&cowboy);

    // Check updated status
    CHECK_FALSE(ninja.isAlive());
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

