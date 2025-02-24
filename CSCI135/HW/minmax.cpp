/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: LAB 3 B
*/
/*
This program prints out the minimum and maximum storage in 2018.
*/
/**/

#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

int main()
{
    double min, max, EastS = 0;

    ifstream fin("Current_Reservoir_Levels.tsv");
    if (fin.fail())
    {
        cerr << "File cannot be opened for reading." << endl;
        exit(1);
    }

    string junk, date;
    getline(fin, junk);

    while (fin >> date >> EastS)
    {
        fin.ignore(INT_MAX, '\n');
        if (min == 0)
        {
            min = EastS;
        }
        if (min > EastS)
        {
            min = EastS;
        }

        if (max < EastS)
        {
            max = EastS;
        }
    }

    cout << "Minimum storage in East basin: " << min << " billion gallons\n"
         << "MAXimum storage in East basin: " << max << " bilion gallons\n";

    fin.close();
}