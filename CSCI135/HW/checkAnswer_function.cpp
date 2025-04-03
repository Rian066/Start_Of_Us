/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Project 2 A
*/
/*
This program does Project 2A.
*/

#include <iostream>
#include <fstream>
using namespace std;

struct Question
{
    string text;
    string answer;
    string explanation;
    string version;
    string type;
    string label;
};

void read_file(string fileName, Question ques[], int capacity, int &size)
{
    string line;

    ifstream fin(fileName);
    if (!fin)
    {
        cout << "Error: File not found." << endl;
        return;
    }

    Question q;
    int Switch = -1;
    while (getline(fin, line) && size != capacity)
    {
        if (line.find("question:") != string::npos)
            Switch = 0;
        else if (line.find("answer:") != string::npos)
            Switch = 1;
        else if (line.find("explanation:") != string::npos)
            Switch = 2;
        else if (line.find("version:") != string::npos)
            Switch = 3;
        else if (line.find("label:") != string::npos)
            Switch = 4;
        else if (line.find("type:") != string::npos)
            Switch = 5;

        if (Switch == 0)
        {
            if (line.find("question:") != string::npos)
            {
                q.text = line.substr(10);
            }
            else
            {
                q.text += line + "\n";
            }
        }
        else if (Switch == 1)
        {
            if (line.find("answer:") != string::npos)
            {
                q.answer = line.substr(8);
            }
        }
        else if (Switch == 2)
        {
            if (line.find("explanation:") != string::npos)
            {
                q.explanation = line.substr(13);
            }
            else
            {
                q.explanation += "\n" + line;
            }
        }
        else if (Switch == 3)
        {
            if (line.find("version:") != string::npos)
            {
                q.version = line.substr(9);
            }
        }
        else if (Switch == 4)
        {
            if (line.find("label:") != string::npos)
            {
                q.label = line.substr(7);
            }
        }
        else if (Switch == 5)
        {
            if (line.find("type:") != string::npos)
            {
                q.type = line.substr(6);
            }
        }

        if (line.find("type:") != string::npos)
        {
            Switch = -1;
            ques[size] = q;
            size++;
        }
    }
}

void display(Question ques[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << i + 1 << endl; // start labeling from 1

        // display question text of the ith question
        cout << "question: " << ques[i].text << endl;

        // display answer of the ith question
        cout << "answer: " << ques[i].answer << endl;

        // display explanation of the ith question
        cout << "explanation: " << ques[i].explanation << endl;
        cout << "type: " << ques[i].type << endl;
        cout << "version: " << ques[i].version << endl;
        cout << "label: " << ques[i].label << endl
             << endl;
    }
}

int main()
{
    const int CAPACITY = 1000;
    Question ques[CAPACITY];

    int size = 0;
    read_file("cs135_midterm_f24_v1.txt", ques, CAPACITY, size);
    read_file("cs135_midterm_f24_v2.txt", ques, CAPACITY, size);
    read_file("cs135_midterm_s24_v1.txt", ques, CAPACITY, size);
    display(ques, size);
}
