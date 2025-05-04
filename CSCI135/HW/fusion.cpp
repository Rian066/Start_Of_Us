/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 12 C
*/
/*
This program appends two vectors into one.
*/

#include <iostream>
#include <vector>
using namespace std;

void gogeta(vector<int> &goku, vector<int> &vegeta)
{
    for (int i = 0; i < vegeta.size(); i++)
    {
        goku.push_back(vegeta[i]);
    }
    vegeta.clear();
}

int main()
{

    return 0;
}
