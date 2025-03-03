#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    string filename;
    cout << "Enter a file name: ";
    cin >> filename;

    string question[200];
    string answer[200];
    string explanation[200];
    string version[200];
    string type[200];
    string label[200];
    string line;

    ifstream fin(filename);

    int i, Switch = 0;
    while (getline(fin, line))
    {
        if (line.find("question:") != string::npos)
            Switch = 0;
        else if (line.find("answer:") != string::npos)
            Switch = 1;
        else if (line.find("explanation:") != string::npos)
            Switch = 2;
        else
            Switch = 5;

        if (Switch == 0)
        {
            if (line.find("question:") != string::npos)
            {
                question[i] += line.substr(9);
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
                explanation[i] += line.substr(12);
            }
            else
            {
                explanation[i] += line;
            }
        }

        if (line.find("type:") != string::npos)
        {
            i++;
        }
    }

    int True, False, j = 0;
    while (!question[j].empty())
    {
        string ans;
        cout << "\033[1m" << "Question" << j + 1 << ":" << "\033[0m" << "\033[35m" << question[j] << "\033[0m" << endl;
        int h = 1;
        while (h <= 3)
        {
            cout << "Enter your answer: ";
            cin >> ans;

            if (ans == answer[j])
            {
                True++;
                cout << boolalpha << "number of tries: " << h << endl
                     << (ans == answer[j]) << endl
                     << endl;
                break;
            }
            else
            {
                cout << boolalpha << "number of tries: " << h << endl
                     << (ans == answer[j]) << endl;
                if (h == 3 and ans != answer[j])
                {
                    cout << "\033[1m" << "Explanation:" << "\033[0m" << "\033[35m" << explanation[j] << "\033[0m" << endl
                         << endl;
                }
            }
            h++;
        }
        False++;
        j++;
    }

    string grade;
    if ((True / (True + False)) >= 90)
        grade = "excellent";
    if ((True / (True + False)) >= 80 and (True / (True + False)) < 90)
        grade = "good";
    if ((True / (True + False)) >= 60 and (True / (True + False)) < 80)
        grade = "pass";
    if ((True / (True + False)) < 60)
        grade = "please ask help ASAP";

    cout << "\nnumber of correct problems: " << True << "\npercentage of correct: " << (True / (True + False)) << "%\n"
         << grade << endl;
}