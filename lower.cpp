/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: LAB 4 D
*/
/*
This program prints the bottom-left half of a square, given the side length using stars(*).
*/

#include <iostream>
using namespace std;

int main()
{
    int side;

    cout << "Input side length: ";
    cin >> side;
    cout << endl
         << "Shape: \n";

    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            cout << "*";
        }
        cout << endl;
    }
}