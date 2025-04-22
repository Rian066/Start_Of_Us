/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: E9.5
*/
/*
This program creates a constructor to construct a rectangle with a given width and height.
*/

#include <iostream>
using namespace std;

class Rectangle
{
public:
    Rectangle(double w, double h)
    {
        height = h;
        width = w;
    }
    double get_perimeter();
    double get_area();
    void resize(double factor);

private:
    double height;
    double width;
};

double Rectangle::get_perimeter()
{
    return 2 * width + 2 * height;
}

double Rectangle::get_area()
{
    return width * height;
}

void Rectangle::resize(double factor)
{
    width *= factor;
    height *= factor;
}