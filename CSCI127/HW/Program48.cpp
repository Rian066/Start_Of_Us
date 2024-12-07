// Name:  Rian M Alif
// Email: rian.alif58@myhunter.cuny.edu
// Date: December 6, 2024
// This program creates a weird looking star

#include <iostream>
using namespace std;

int main()
{
    int year;

    do
    {
        cout << "Enter a numerical year: ";
        cin >> year;

        if (year > 2018)
        {
            cout << "Year must be 2018 or earlier\n";
        }
        else
        {
            cout << "You entered: " << year << endl;
        }
    } while (year > 2018);
}