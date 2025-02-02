/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 1 C
*/
/*
This program determines if it's a common year or leap year.
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int year;

    cout << "Enter year: ";
    cin >> year;

    if (year % 4 != 0)
    {
        cout << "Common year\n";
    }
    else if (year % 100 != 0)
    {
        cout << "Leap year\n";
    }
    else if (year % 400 != 0)
    {
        cout << "Common year\n";
    }
    else
    {
        cout << "Leap year\n";
    }
}