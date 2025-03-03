/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: LAB 4 B
*/
/*
This program prints out a checkerboard using stars (*).
*/
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

    cout << endl;

    int order = 0;

    for (int i = 0; i < height; i++)
    {
        if (width % 2 == 0)
        {
            if (order == 0)
            {
                for (int j = 0; j < width / 2; j++)
                {
                    cout << "* ";
                }
                order = 1;
            }
            else
            {
                for (int j = 0; j < width / 2; j++)
                {
                    cout << " *";
                }
                order = 0;
            }
        }
        else
        {
            if (order == 0)
            {
                for (int j = 0; j < (width + 1) / 2; j++)
                {
                    cout << "* ";
                }
                order = 1;
            }
            else
            {
                for (int j = 0; j < (width - 1) / 2; j++)
                {
                    cout << " *";
                }
                order = 0;
            }
        }

        cout << endl;
    }
}