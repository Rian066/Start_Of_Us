/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: LAB 3 D
*/
/*
This program finds reverse chronological order.
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    string date1, date2;
    cout << "Enter startung date: ";
    cin >> date1;
    cout << "Enter ending date: ";
    cin >> date2;

    vector<double> arr;
    vector<string> dates;

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
            arr.push_back(WestE);
            dates.push_back(date);
        }
    }

    fin.close();

    for (int i = arr.size() - 1; i >= 0; i--)
    {
        cout << dates[i] << " " << arr[i] << " ft\n";
    }
}