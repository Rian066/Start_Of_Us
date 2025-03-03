/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: HW E3.5
*/
/*
This program reads a set of numbers and determines it's order.
*/

#include <iostream>
using namespace std;

int main()
{
    int num1, num2, num3;
    cout << "Enter a set: ";

    cin >> num1 >> num2 >> num3;

    if (num2 > num1 and num3 > num2)
    {
        cout << "increasing\n";
    }
    else if (num2 < num1 and num3 < num2)
    {
        cout << "decreasing\n";
    }
    else
    {
        cout << "neither\n";
    }
}