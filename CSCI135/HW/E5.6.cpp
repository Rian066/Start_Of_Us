/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: E5.6
*/
/*
This program returns a string containing the middle character in str if the length of str is odd,
or the two middle characters if the length is even.
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string middle(string str)
{
    int length = str.length();

    if (length % 2 == 0)
    {
        return string(1, str[length / 2 - 1]) + str[length / 2];
    }
    else
    {
        return string(1, str[floor(length / 2)]);
    }
}

int main()
{
    cout << middle("middle") << endl;
    cout << middle("middles") << endl;
}