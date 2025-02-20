/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 2 B
*/
/*
This program print all integers from the requested interval.
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int L, U;

    cout << "Please enter L: ";
    cin >> L;
    cout << "Please enter U: ";
    cin >> U;

    while (L > U)
    {
        cout << "Please enter L greater than U: ";
        cin >> L;
        cout << "Please enter U less than L: ";
        cin >> U;
    }

    for (int i = L; i < U; i++)
    {
        cout << i << " ";
    }
}