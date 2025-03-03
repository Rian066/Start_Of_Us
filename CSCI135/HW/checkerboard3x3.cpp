/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: LAB 4 G
*/
/*
This program asks the user to input width and height and prints a checkerboard of 3-by-3 squares.
*/
/**/
/**/
/**/

#include <iostream>
using namespace std;

int main()
{
    int width, height;
    cout << "Input width: ";
    cin >> width;
    cout << "Input height: ";
    cin >> height;
    cout << endl
         << "Shape:\n";

    int sw = 0;
    for (int i = 1; i <= height; i++)
    {
        if (sw != 0)
        {
            int Switch = 0;
            for (int j = 1; j <= width; j++)
            {

                if (Switch == 0)
                {
                    cout << " ";
                    if (j % 3 == 0)
                        Switch = 1;
                }
                else
                {
                    cout << "*";
                    if (j % 3 == 0)
                        Switch = 0;
                }
            }
            if (i % 3 == 0)
                sw = 0;
        }
        else
        {
            int Switch = 0;
            for (int j = 1; j <= width; j++)
            {

                if (Switch == 0)
                {
                    cout << "*";
                    if (j % 3 == 0)
                        Switch = 1;
                }
                else
                {
                    cout << " ";
                    if (j % 3 == 0)
                        Switch = 0;
                }
            }

            if (i % 3 == 0)
                sw = 1;
        }

        cout << endl;
    }
}