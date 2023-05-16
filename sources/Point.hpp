//
// Created by avida on 5/15/2023.
//
#include <string>
#ifndef COWBOY_VS_NINJA_A_POINT_H
#define COWBOY_VS_NINJA_A_POINT_H
using namespace std;
namespace ariel {

    class Point {
    double x;
    double y;
    public:
        Point(double x, double y);
        double getX();
        double getY();
        void setX(double x);
        void setY(double y);
        Point();
        double distance(const Point& other) const;
        string print();
        Point moveTowards(Point p, double distance);
        static Point moveTowards(Point point1, Point point2, double distance);

    };

} // ariel

#endif //COWBOY_VS_NINJA_A_POINT_H
