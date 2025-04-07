/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 9 E
*/
/*
This program creates and deletes objects dynamically.
*/
/**/
/**/

#include <iostream>
#include <cmath>
using namespace std;

class Coord3D
{
public:
    double x;
    double y;
    double z;
};

Coord3D *createCoord3D(double x, double y, double z)
{
    Coord3D *p = new Coord3D;
    (*p).x = x;
    (*p).y = y;
    (*p).z = z;
    return p;
}

void deleteCoord3D(Coord3D *p)
{
    delete p;
}

double length(Coord3D *p)
{
    return sqrt(((*p).x * (*p).x) + ((*p).y * (*p).y) + ((*p).z * (*p).z));
}

Coord3D *fartherFromOrigin(Coord3D *p1, Coord3D *p2)
{
    double x = length(p1);
    double y = length(p2);

    if (x > y)
    {
        return p1;
    }
    else
    {
        return p2;
    }
}

void move(Coord3D *ppos, Coord3D *pvel, double dt)
{
    (*ppos).x += (*pvel).x * dt;
    (*ppos).y += (*pvel).y * dt;
    (*ppos).z += (*pvel).z * dt;
}

int main()
{
    double x, y, z;
    cout << "Enter position: ";
    cin >> x >> y >> z;
    Coord3D *ppos = createCoord3D(x, y, z);

    cout << "Enter velocity: ";
    cin >> x >> y >> z;
    Coord3D *pvel = createCoord3D(x, y, z);

    move(ppos, pvel, 10.0);

    cout << "Coordinates after 10 seconds: "
         << (*ppos).x << " " << (*ppos).y << " " << (*ppos).z << endl;

    deleteCoord3D(ppos); // release memory
    deleteCoord3D(pvel);
}
