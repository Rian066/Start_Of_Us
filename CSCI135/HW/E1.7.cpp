/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: E1.7

This program prints the given names in different lines.
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string n1, n2, n3;

    cout << "Enter first name: ";
    cin >> n1;
    cout << "Enter second name: ";
    cin >> n2;
    cout << "Enter third name: ";
    cin >> n3;

    cout << n1 << "\n"
         << n2 << "\n"
         << n3 << "\n";
}