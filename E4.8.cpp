/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: HW E4.8
*/
/*
This program prints each character in each line.
*/

#include <iostream>
using namespace std;

int main()
{
    string word;
    cout << "Enter a word: ";
    cin >> word;

    for (char c : word)
    {
        cout << c << endl;
    }
}