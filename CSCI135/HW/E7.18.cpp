/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: E7.18
*/
/*
This program determines perimeter.
*/

#include <iostream>
#include <cmath>
using namespace std;

struct Point
{
    double x, y;
};

struct Triangle
{
    Point p1, p2, p3;
};

double distance(Point a, Point b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

double perimeter(Triangle t)
{
    double side1 = distance(t.p1, t.p2);
    double side2 = distance(t.p2, t.p3);
    double side3 = distance(t.p3, t.p1);
    return side1 + side2 + side3;
}

int main()
{
    Triangle t;

    cout << "Enter coordinates of point 1 (x y): ";
    cin >> t.p1.x >> t.p1.y;

    cout << "Enter coordinates of point 2 (x y): ";
    cin >> t.p2.x >> t.p2.y;

    cout << "Enter coordinates of point 3 (x y): ";
    cin >> t.p3.x >> t.p3.y;

    double result = perimeter(t);
    cout << "Perimeter of the triangle: " << result << endl;

    return 0;
}
