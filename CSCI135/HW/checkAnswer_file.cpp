/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Project 1 C
*/
/*
This program grades a test.
*/

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string filename;
    cout << "Enter a file name: ";
    cin >> filename;

    string question[200], answer[200], explanation[200];
    string line;

    ifstream fin(filename);
    if (!fin)
    {
        cout << "Error: File not found." << endl;
        return 1;
    }
    int i = 0, Switch = -1;
    while (getline(fin, line) && i < 200)
    {
        if (line.find("question:") != string::npos)
            Switch = 0;
        else if (line.find("answer:") != string::npos)
            Switch = 1;
        else if (line.find("explanation:") != string::npos)
            Switch = 2;
        else if (line.find("version:") != string::npos)
            Switch = -1;

        if (Switch == 0)
        {
            if (line.find("question:") != string::npos)
            {
                question[i] += line.substr(10);
            }
            else
            {
                question[i] += line + "\n";
            }
        }
        else if (Switch == 1)
        {
            if (line.find("answer:") != string::npos)
            {
                answer[i] += line.substr(8);
            }
        }
        else if (Switch == 2)
        {
            if (line.find("explanation:") != string::npos)
            {
                explanation[i] += line.substr(13);
            }
            else
            {
                explanation[i] += line + "\n";
            }
        }

        if (line.find("type:") != string::npos)
        {
            i++;
            Switch = -1;
        }
    }

    double True, NumQ = 0;
    int j = 0;
    while (!question[j].empty() && j < 200)
    {
        string ans;
        cout << "Question " << j + 1 << ":" << question[j] << endl;
        int h = 1;
        while (h <= 3)
        {
            cout << "Enter your answer: ";
            getline(cin, ans);
            if (ans == answer[j])
            {
                True++;
                cout << "number of tries: " << h << endl
                     << "true" << endl
                     << endl;
                break;
            }
            else
            {
                cout << "number of tries: " << h << endl
                     << "false" << endl;
                if (h == 3)
                {
                    cout << "Explanation: " << explanation[j] << endl;
                }
            }
            h++;
        }
        NumQ++;
        j++;
        cout << endl;
    }

    double percentage = (True / NumQ) * 100;
    string grade;
    if (percentage >= 90)
        grade = "excellent";
    else if (percentage >= 80)
        grade = "good";
    else if (percentage >= 60)
        grade = "pass";
    else
        grade = "please ask help ASAP";

    cout << "\nNumber of correct problems: " << True
         << "\nPercentage of correct: " << percentage << "%"
         << "\n"
         << grade << endl;
}
