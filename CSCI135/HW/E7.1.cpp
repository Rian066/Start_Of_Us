/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: HW E7.1
*/
/*
This program receives two pointers and sorts the values to which they point.
*/

#include <iostream>
using namespace std;

void sort2(double *p, double *q)
{
    if (*p > *q)
    {
        double temp = *p;
        *p = *q;
        *q = temp;
    }
}

int main()
{
    return 0;
}