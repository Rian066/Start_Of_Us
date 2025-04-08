/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: E7.16
*/
/*
This program finds distance between two points.
*/

#include <iostream>
#include <cmath>
using namespace std;

struct Point
{
    double x, y;
};

double distance(Point a, Point b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

int main()
{
    Point p1, p2;

    cout << "Enter coordinates of point 1 (x y): ";
    cin >> p1.x >> p1.y;

    cout << "Enter coordinates of point 2 (x y): ";
    cin >> p2.x >> p2.y;

    double result = distance(p1, p2);
    cout << "Distance between the points: " << result << endl;

    return 0;
}
