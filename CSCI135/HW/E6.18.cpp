/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: E6.18
*/
/*
This program appends one vector after another.
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> append(vector<int> a, vector<int> b)
{
    vector<int> final = a;

    for (int i = 0; i < b.size(); i++)
    {
        final.push_back(b[i]);
    }

    return final;
}

int main()
{
    return 0;
}