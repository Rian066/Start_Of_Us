/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 6 C
*/
/*
This program makes a vugenere cipher code;
*/
/**/
/**/
/**/
/**/

#include <iostream>
#include <cctype>
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

string encryptVigenere(string plaintext, string keyword)
{
    string final;
    int rshift;
    int rIndex = 0;
    for (int i = 0; i < plaintext.length(); i++)
    {
        if (isalpha(plaintext[i]))
        {
            rshift = int(keyword[rIndex++]) - 97;
            final += shiftChar(plaintext[i], rshift);
            if (rIndex == keyword.length())
                rIndex = 0;
        }
        else
        {
            final += plaintext[i];
        }
    }

    return final;
}

int main()
{
    string text, rshift;
    cout << "Enter plaintext: ";
    getline(cin, text);
    cout << "Enter keyword: ";
    cin >> rshift;

    cout << encryptVigenere(text, rshift) << endl;
}