/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: HW E3.1
*/
/*
This program reads an integer and prints whether it is negative, zero, or positive.
*/

#include <iostream>
using namespace std;

int main()
{
    int num;
    cout << "Enter an integer: ";
    cin >> num;

    if (num == 0)
    {
        cout << "zero\n";
    }
    else if (num > 0)
    {
        cout << "positive\n";
    }
    else
    {
        cout << "negative\n";
    }
}