/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 1 D
*/
/*
This program determines the number of days in a given month.
*/
/**/
/**/
/**/
/**/
/**/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    bool leap;
    int year, month;

    cout << "Enter year: ";
    cin >> year;
    cout << "Enter month: ";
    cin >> month;

    if (year % 4 != 0)
    {
        leap = false;
    }
    else if (year % 100 != 0)
    {
        leap = true;
    }
    else if (year % 400 != 0)
    {
        leap = false;
    }
    else
    {
        leap = true;
    }

    if (month <= 7)
    {
        if (month % 2 == 0)
        {
            if (month == 2)
            {
                if (leap == true)
                {
                    cout << "29 days\n";
                }
                else
                {
                    cout << "28 days\n";
                }
            }
            else
            {
                cout << "30 days\n";
            }
        }
        else
        {
            cout << "31 days\n";
        }
    }
    else
    {
        if (month % 2 == 0)
        {
            if (month == 2)
            {
                if (leap == true)
                {
                    cout << "29 days\n";
                }
                else
                {
                    cout << "28 days\n";
                }
            }
            else
            {
                cout << "31 days\n";
            }
        }
        else
        {
            cout << "30 days\n";
        }
    }
}