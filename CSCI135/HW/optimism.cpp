/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 12 B
*/
/*
This program determines the largest twin prime.
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> goodVibes(vector<int> v)
{
    vector<int> positives;
    for (int num : v)
    {
        if (num > 0)
        {
            positives.push_back(num);
        }
    }
    return positives;
}

int main()
{

    return 0;
}
