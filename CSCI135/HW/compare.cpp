/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: LAB 3 C
*/
/*
This program compares elevations.
*/

#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

int main()
{
    string date1, date2;
    cout << "Enter startung date: ";
    cin >> date1;
    cout << "Enter ending date: ";
    cin >> date2;

    ifstream fin("Current_Reservoir_Levels.tsv");
    if (fin.fail())
    {
        cerr << "File cannot be opened for reading." << endl;
        exit(1);
    }

    string junk, date;
    getline(fin, junk);
    double EastS, EastE, WestS, WestE;

    while (fin >> date >> EastS >> EastE >> WestS >> WestE)
    {
        if (date >= date1 and date <= date2)
        {
            string x;
            if (EastE > WestE)
            {
                x = "East";
            }
            else if (EastE < WestE)
            {
                x = "West";
            }
            else
            {
                x = "Equal";
            }

            cout << date << " " << x << endl;
        }
    }

    fin.close();
}