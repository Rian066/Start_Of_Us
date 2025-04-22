/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Project 2B
*/
/*
This program organizes the tasks into functions, each concentrate on a task.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <cctype>
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

string trim(string s)
{
    int i = 0;
    int j = (int)s.length() - 1;
    while (i <= j && isspace(s[i]))
        i++;
    while (j >= i && isspace(s[j]))
        j--;
    if (i > j)
        return "";
    return s.substr(i, j - i + 1);
}

int count_occurrence(const string &s, char ch)
{
    int cnt = 0;
    for (int i = 0; i < (int)s.length(); i++)
        if (s[i] == ch)
            cnt++;
    return cnt;
}

string *extract_type(const string &type, int &num)
{
    int semis = count_occurrence(type, ';');
    num = semis + 1;
    string *arr = new string[num];
    int start = 0;
    for (int k = 0; k < num; k++)
    {
        int pos = (int)type.find(';', start);
        string piece;
        if (pos == (int)string::npos)
            piece = type.substr(start);
        else
            piece = type.substr(start, pos - start);
        arr[k] = trim(piece);
        if (pos == (int)string::npos)
            break;
        start = pos + 1;
    }
    return arr;
}

void insert_order_unique(string types[], int cap, int &count, const string &toAdd)
{
    if (count >= cap)
        return;
    int i = 0;
    while (i < count && types[i] < toAdd)
        i++;
    if (i < count && types[i] == toAdd)
        return; // already present
    // shift right to make room
    for (int j = count; j > i; j--)
        types[j] = types[j - 1];
    types[i] = toAdd;
    count++;
}

void insert_order_unique(string types[], int cap, int &count, Question q[], int qsize)
{
    for (int i = 0; i < qsize; i++)
    {
        int n;
        string *arr = extract_type(q[i].type, n);
        for (int j = 0; j < n; j++)
            insert_order_unique(types, cap, count, arr[j]);
        delete[] arr;
    }
}

string choose_type(string types[], int count)
{
    int choice;
    do
    {
        cout << "0. ALL TYPES\n";
        for (int i = 0; i < count; i++)
            cout << (i + 1) << ". " << types[i] << "\n";
        cout << "Enter a type: ";
        cin >> choice;
    } while (choice < 0 || choice > count);
    cin.ignore(INT_MAX, '\n'); // clear newline
    if (choice == 0)
        return "";
    return types[choice - 1];
}

void randomize(Question q[], int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        int r = rand() % (i + 1);
        Question tmp = q[i];
        q[i] = q[r];
        q[r] = tmp;
    }
}

void feedback(int correct, int total)
{
    cout << "number of correct problems: " << correct << "\n";
    double pct = total > 0 ? (100.0 * correct) / total : 0.0;
    cout << "percentage of correct: " << pct << "%\n";
    if (pct >= 90)
        cout << "excellent\n";
    else if (pct >= 80)
        cout << "good\n";
    else if (pct >= 70)
        cout << "pass\n";
    else
        cout << "please ask help ASAP\n";
}

void answer_by_type(Question q[], int size, const string &chosen)
{
    randomize(q, size);
    int correct = 0, asked = 0;
    for (int i = 0; i < size; i++)
    {
        if (!chosen.empty() && q[i].type.find(chosen) == string::npos)
            continue;
        asked++;
        cout << "question " << q[i].version << " " << q[i].label
             << ": " << q[i].text << "\n";
        for (int t = 1; t <= 3; t++)
        {
            cout << "Enter your answer: ";
            string ans;
            getline(cin, ans);
            cout << "number of tries: " << t << "\n";
            if (ans == q[i].answer)
            {
                cout << "true\n\n";
                correct++;
                break;
            }
            else
            {
                cout << "false\n";
                if (t == 3 && !q[i].explanation.empty())
                    cout << q[i].explanation << "\n";
            }
        }
    }
    feedback(correct, asked);
}

void read_file(const string &fname, Question q[], int cap, int &sz)
{
    ifstream fin(fname.c_str());
    if (!fin)
    {
        cerr << fname << " cannot open\n";
        exit(1);
    }
    string line;
    while (getline(fin, line))
        if (line.size() >= 9 && line.substr(0, 9) == "question:")
            break;
    while (line.size() >= 9 && line.substr(0, 9) == "question:")
    {
        if (sz >= cap)
            return;
        q[sz].text = trim(line.substr(9));

        while (getline(fin, line) && (line.size() < 7 || line.substr(0, 7) != "answer:"))
            q[sz].text += "\n" + line;
        q[sz].answer = trim(line.size() >= 7 ? line.substr(7) : "");

        while (getline(fin, line) &&
               (line.size() < 12 || line.substr(0, 12) != "explanation:"))
            q[sz].answer += "\n" + line;
        q[sz].explanation.clear();
        if (line.size() >= 12 && line.substr(0, 12) == "explanation:")
        {
            q[sz].explanation = trim(line.substr(12)) + "\n";
            while (getline(fin, line) &&
                   line.substr(0, 8) != "version:" &&
                   line.substr(0, 5) != "type:" &&
                   line.substr(0, 6) != "label:")
                q[sz].explanation += line + "\n";
        }

        if (line.size() >= 8 && line.substr(0, 8) == "version:")
        {
            q[sz].version = trim(line.substr(8));
            getline(fin, line);
        }

        if (line.size() >= 5 && line.substr(0, 5) == "type:")
        {
            q[sz].type = trim(line.substr(5));
            getline(fin, line);
        }

        if (line.size() >= 6 && line.substr(0, 6) == "label:")
        {
            q[sz].label = trim(line.substr(6));
            getline(fin, line);
        }
        sz++;
    }
    fin.close();
}

int main()
{
    srand((unsigned)time(NULL));

    const int CAP = 1000;
    Question ques[CAP];
    int size = 0;

    read_file("cs135_midterm_f24_v1.txt", ques, CAP, size);
    read_file("cs135_midterm_f24_v2.txt", ques, CAP, size);
    read_file("cs135_midterm_s24_v1.txt", ques, CAP, size);

    const int TYPE_CAP = 30;
    string types[TYPE_CAP];
    int typeCount = 0;

    insert_order_unique(types, TYPE_CAP, typeCount, ques, size);

    string chosen = choose_type(types, typeCount);

    answer_by_type(ques, size, chosen);

    return 0;
}
