/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 6 B
*/
/*
This program
*/
/**/
/**/

#include <iostream>
using namespace std;

char shiftChar(char c, int s)
{
    int num = int(c);
    if (num >= 65 and num <= 90)
    {
        if ((num + s) > 90)
        {
            num = ((num + s) - 91) + 65;
        }
        else
        {
            num += s;
        }
        return char(num);
    }
    else if (num >= 97 and num <= 122)
    {
        if ((num + s) > 122)
        {
            num = ((num + s) - 123) + 97;
        }
        else
        {
            num += s;
        }
        return char(num);
    }
    else
    {
        return c;
    }
}
string encryptCaesar(string plaintext, int rshift)
{
    string final;
    for (int i = 0; i < plaintext.length(); i++)
    {
        final += shiftChar(plaintext[i], rshift);
    }

    return final;
}

int main()
{
    string text;
    int rshift;
    cout << "Enter plaintext: ";
    getline(cin, text);
    cout << "Enter shift: ";
    cin >> rshift;

    cout << encryptCaesar(text, rshift) << endl;
}