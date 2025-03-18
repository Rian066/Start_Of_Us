/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 6 A
*/
/*
This program asks the user to input a line of text and reports all characters from the input line together with their ASCII codes.
*/

#include <iostream>
using namespace std;

int main()
{
    string input;
    getline(cin, input);

    for (int i = 0; i < input.length(); i++)
    {
        cout << input[i] << " " << int(input[i]) << endl;
    }
}