//
// Created by avida on 5/15/2023.
//
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

#include "Point.hpp"

namespace ariel {

    Point::Point(double x, double y) {

        this->x = x;
        this->y = y;

    }

    double Point::getX() {
        return 0;
    }
    double Point::getY() {
        return 0;
    }
    void Point::setX(double x) {

    }
    void Point::setY(double y) {

    }
    Point::Point() {

    }
    double Point::distance(const Point &other) const {
        return 0;
    }
    string Point::print() {
        return " ";
    }
    Point Point::moveTowards(Point p, double distance) {
        return Point();
    }
    Point Point::moveTowards(Point point1, Point point2, double distance) {
        return Point();
    }


} // ariel