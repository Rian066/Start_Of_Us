// Name:  Rian M Alif
// Email: rian.alif58@myhunter.cuny.edu
// Date: December 17, 2024
// This program prints happy wishes for each season

#include <iostream>
using namespace std;

int main()
{
    int month = 0;
    cout << "Enter month (as a number): ";
    cin >> month;

    if (month < 3 or month > 11)
    {
        cout << "Happy Winter" << endl;
    }
    else if (3 <= month and month < 7)
    {
        cout << "Happy Spring" << endl;
    }
    else if (7 <= month and month < 9)
    {
        cout << "Happy Summer" << endl;
    }
    else
    {
        cout << "Happy Fall" << endl;
    }

    return 0;
}