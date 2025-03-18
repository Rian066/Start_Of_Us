/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 6 D
*/
/*
This program encrypts a vigenere and caeser cipher code and then decrypts it.
*/
/**/
/**/
/**/
/**/
/**/
/**/
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

char unShiftChar(char c, int s)
{
    int num = int(c);
    if (num >= 65 and num <= 90)
    {
        if ((num - s) < 65)
        {
            num = 90 - (64 - (num - s));
        }
        else
        {
            num -= s;
        }
        return char(num);
    }
    else if (num >= 97 and num <= 122)
    {
        if ((num - s) < 97)
        {
            num = 122 - (96 - (num - s));
        }
        else
        {
            num -= s;
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

string encryptCaesar(string plaintext, int rshift)
{
    string final;
    for (int i = 0; i < plaintext.length(); i++)
    {
        final += shiftChar(plaintext[i], rshift);
    }

    return final;
}

string decryptCaesar(string ciphertext, int rshift)
{
    string final;
    for (int i = 0; i < ciphertext.length(); i++)
    {
        final += unShiftChar(ciphertext[i], rshift);
    }

    return final;
}

string decryptVigenere(string ciphertext, string keyword)
{
    string final;
    int rshift;
    int rIndex = 0;
    for (int i = 0; i < ciphertext.length(); i++)
    {
        if (isalpha(ciphertext[i]))
        {
            rshift = int(keyword[rIndex++]) - 97;
            final += unShiftChar(ciphertext[i], rshift);
            if (rIndex == keyword.length())
                rIndex = 0;
        }
        else
        {
            final += ciphertext[i];
        }
    }

    return final;
}

int main()
{
    string text, keyword;
    int rshift;
    cout << "Enter plaintext: ";
    getline(cin, text);

    // Caeser
    cout << "= Caeser =\n";
    cout << "Enter shift: ";
    cin >> rshift;
    string cipher1 = encryptCaesar(text, rshift);
    cout << "Ciphertext : " << cipher1
         << "\nDecrypted  : " << decryptCaesar(cipher1, rshift) << endl;

    // Vigenere
    cout << "= Vigenere =\n";
    cout << "Enter keyword: ";
    cin >> keyword;
    string cipher2 = encryptVigenere(text, keyword);
    cout << "Ciphertext : " << cipher2
         << "\nDecrypted  : " << decryptVigenere(cipher2, keyword) << endl;
}