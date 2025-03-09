/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 1 G
*/
/*
This program determines the largest twin prime.
*/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/

#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
        return false;

    for (int i = 2; i < 10; i++)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}

int nextPrime(int n)
{
    int i = n + 1;
    while (!isPrime(i))
    {
        i++;
    }

    return i;
}

int countPrimes(int a, int b)
{
    int count = 0;
    int i = a;
    if (isPrime(a))
    {
        count++;
        i = nextPrime(i);
    }

    while (i <= b)
    {
        if (i != 1 and isPrime(i))
            count++;
        i = nextPrime(i);
    }

    return count;
}

bool isTwinPrime(int n)
{
    if (!isPrime(n))
        return false;
    if (isPrime(n - 2) or isPrime(n + 2))
        return true;
    return false;
}

int nextTwinPrime(int n)
{
    int i = n + 1;
    while (!isTwinPrime(i))
    {
        i++;
    }

    return i;
}

int largestTwinPrime(int a, int b)
{
    int largest = -1;

    for (int i = a; i <= b;)
    {
        if (isTwinPrime(i))
        {
            if (i > largest)
                largest = i;
        }
        int next = nextTwinPrime(i);
        i = next;
    }

    return largest;
}

bool isDivisibleBy(int n, int d)
{
    if (d == 0)
        return false;
    if (n % d == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    int one, two;
    cout << "Enter a number: ";
    cin >> one;
    cout << "Enter another number: ";
    cin >> two;

    if (isDivisibleBy(one, two))
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }

    cout << boolalpha << isPrime(one) << endl;

    cout << nextPrime(one) << endl;

    cout << countPrimes(one, two) << endl;

    cout << boolalpha << isTwinPrime(one) << endl;

    cout << largestTwinPrime(one, two) << endl;
}