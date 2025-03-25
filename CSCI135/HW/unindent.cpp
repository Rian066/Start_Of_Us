/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 7 A
*/
/*
This program unindents.
*/

#include <iostream>
#include <cctype>
#include <string>

using namespace std;

string removeLeadingSpaces(string line)
{
    size_t i = 0;
    while (i < line.length() && isspace(line[i]))
    {
        i++;
    }
    return line.substr(i);
}

int main()
{
    string line;
    while (getline(cin, line))
    {
        cout << removeLeadingSpaces(line) << endl;
    }
    return 0;
}
