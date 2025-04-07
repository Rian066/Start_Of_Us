/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 9 D
*/
/*
This program  allocates the memory dynamically.
*/
/**/

#include <iostream>
using namespace std;

string *createAPoemDynamically()
{
    string *p = new string;
    *p = "Roses are red, violets are blue";
    return p;
}

int main()
{
    while (true)
    {
        string *p;
        p = createAPoemDynamically();
        delete p;
    }

    return 0;
}