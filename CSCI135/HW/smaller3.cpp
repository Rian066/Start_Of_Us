/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 1 B
*/
/*
This program finds the smaller of three integers.
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int f1, f2, f3;
    cout << "Enter the first number: ";
    cin >> f1;
    cout << "Enter the second number: ";
    cin >> f2;
    cout << "Enter the third number: ";
    cin >> f3;

    if (f1 < f2)
    {
        if (f1 < f3)
        {
            cout << "The smaller of the three is " << f1 << endl;
        }
        else
        {
            cout << "The smaller of the three is " << f3 << endl;
        }
    }
    else if (f2 < f3)
    {
        cout << "The smaller of the three is " << f2 << endl;
    }
    else
    {
        cout << "The smaller of the three is " << f3 << endl;
    }
}