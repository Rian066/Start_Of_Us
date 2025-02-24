/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: LAB 3 A
*/
/*
This program prints out the east basin storage on a given date.
*/

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string date;
    cout << "Enter date: ";
    cin >> date;

    ifstream fin("Current_Reservoir_Levels.tsv");
    if (fin.fail())
    {
        cerr << "File cannot be opened for reading." << endl;
        exit(1);
    }

    string junk, date1;
    getline(fin, junk);

    double EastS, EastE, WestS, WestE;
    while (fin >> date1 >> EastS >> EastE >> WestS >> WestE)
    {
        if (date1 == date)
        {
            cout << "East basin storage: " << EastS << "billion gallons\n";
        }
    }

    fin.close();
}