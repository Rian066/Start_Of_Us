/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 2 A
*/
/*
This program finds the cost per 100 miles.
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int num;

    cout << "Enter an integer: \n";
    cin >> num;

    while (num <= 0 or num >= 100)
    {
        cout << "Please re-enter: \n";
        cin >> num;
    }

    cout << "Number squared is: " << (num * num) << endl;
}