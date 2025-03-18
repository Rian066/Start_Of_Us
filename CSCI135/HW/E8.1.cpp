/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: E8.1
*/
/*
This program writes and reads from a file.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ofstream fon("hello.txt");
    if (fon)
    {
        fon << "Hello, World!";
        fon.close();
    }

    ifstream fin("hello.txt");
    string stuff;
    if (getline(fin, stuff))
    {
        cout << stuff << endl;
    }

    fin.close();
}