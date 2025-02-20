/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 2 D
*/
/*
This program uses an array of ints to compute and print all Fibonacci numbers from F(0) to F(59).
*/

#include <iostream>
#include <array>
using namespace std;

int main()
{
    array<int, 60> fib;
    fib[0] = 0;
    fib[1] = 1;

    cout << fib[0] << endl
         << fib[1] << endl;

    for (int i = 2; i < fib.size(); i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
        cout << fib[i] << endl;
    }
}