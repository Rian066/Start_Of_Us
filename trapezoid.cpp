/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: LAB 4 F
*/
/*
This program prints an upside-down trapezoid of given width and height using stars(*).
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int width, height;

    cout << "Input width: ";
    cin >> width;
    cout << "Input height: ";
    cin >> height;
    cout << endl;

    if (height > ceil(width / 2.0))
    {
        cout << "Impossible shape!\n";
        return 0;
    }

    cout << "Shape:\n";

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width - i; j++)
        {
            if (j < i)
            {
                cout << " ";
            }
            else
            {
                cout << "*";
            }
        }
        cout << endl;
    }
}