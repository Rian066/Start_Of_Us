/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: E6.20
*/
/*
This program appends one vector after another and then merge sort.
*/

#include <iostream>
#include <vector>
#include <algorithm>
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

vector<int> merge_sorted(vector<int> a, vector<int> b)
{
    vector<int> final = append(a, b);

    sort(final.begin(), final.end());

    return final;
}

int main()
{
    return 0;
}