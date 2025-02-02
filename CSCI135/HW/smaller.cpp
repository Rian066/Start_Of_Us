/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 1 A
*/
/*
This program finds the smaller of two integers.
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int f1;
    int f2;
    cout << "Enter the first number: ";
    cin >> f1;
    cout << "Enter the second number: ";
    cin >> f2;

    if (f1 < f2)
    {
        cout << "The smaller of the two is " << f1 << endl;
    }
    else if (f1 > f2)
    {
        cout << "The smaller of the two is " << f2 << endl;
    }
    else
    {
        cout << "They are equal" << endl;
    }
}