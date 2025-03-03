/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: LAB 4 C
*/
/*
This program prints out a cross using stars(*).
*/

#include <iostream>
using namespace std;

int main()
{
    int size;
    cout << "Input size: ";
    cin >> size;
    cout << endl;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (j == i || j == size - i - 1)
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }
}