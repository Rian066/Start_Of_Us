/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: E5.15
*/
/*
This program does sorting in order.
*/

#include <iostream>
using namespace std;

void sort3(int &a, int &b, int &c)
{
    int x = a;
    int y = b;

    while (a > b or a > c or b > c)
    {
        if (a > b)
        {
            a = b;
            b = x;
            x = a;
            y = b;
        }
        else if (b > c)
        {
            b = c;
            c = y;
            y = b;
        }
    }
}

int main()
{
    int v = 5;
    int w = 3;
    int z = 1;
    sort3(v, w, z);
    cout << v << w << z;

    return 0;
}