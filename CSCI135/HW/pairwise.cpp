/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 12 D
*/
/*
This program returns a vector of integers whose elements are the pairwise sum of the elements from the two vectors passed as arguments.
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> sumPairWise(vector<int> &v1, vector<int> &v2)
{
    vector<int> result;
    int maxSize = max(v1.size(), v2.size());

    for (int i = 0; i < maxSize; i++)
    {
        int val1, val2;

        if (i < v1.size())
        {
            val1 = v1[i];
        }
        else
        {
            val1 = 0;
        }

        if (i < v2.size())
        {
            val2 = v2[i];
        }
        else
        {
            val2 = 0;
        }

        result.push_back(val1 + val2);
    }

    return result;
}

int main()
{

    return 0;
}
