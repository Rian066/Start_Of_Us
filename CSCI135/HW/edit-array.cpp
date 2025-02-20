/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 2 C
*/
/*
This program uses arrays to store, update, and retrieve numbers.
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int array[10], index, value;

    for (int i = 0; i < 10; i++)
    {
        array[i] = 1;
        cout << array[i] << " ";
    }

    cout << "Input index: ";
    cin >> index;
    cout << "Input value: ";
    cin >> value;
    cout << endl;

    while (index >= 0 and index < 10)
    {
        array[index] = value;
        for (int i = 0; i < 10; i++)
        {
            cout << array[i] << " ";
        }
        cout << "Input index: ";
        cin >> index;
        cout << "Input value: ";
        cin >> value;
        cout << endl;
    }

    cout << "Index out of range. Exit.\n";
}