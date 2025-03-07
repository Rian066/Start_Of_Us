/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 1 A
*/
/*
This program writes a function.
*/

#include <iostream>
using namespace std;

bool isDivisibleBy(int n, int d)
{
    if (d == 0)
        return false;
    if (n % d == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    int one, two;
    cout << "Enter a number: ";
    cin >> one;
    cout << "Enter another number: ";
    cin >> two;

    if (isDivisibleBy(one, two))
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
}