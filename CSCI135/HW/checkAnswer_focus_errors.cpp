/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Project 2C
*/
/*
This program implements motivation.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <ctime>

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

void read_file(const string &fileName, Question questions[], int capacity, int &count);
void display(const Question questions[], int count);
string trim(const string &input);
int count_occurrences(const string &input, char character);
string *extract_type(const string &typeField, int &typeCount);
void insert_order_unique(string typeArray[], int maxTypes, int &currentTypeCount, const string &newType);
void insert_order_unique(string typeArray[], int maxTypes, int &currentTypeCount, const Question questions[], int questionCount);
void randomize(Question questions[], int count);
string choose_type(const string availableTypes[], int typeCount);
void answer_by_type(Question questions[], int count, const string &selectedType);
void feedback(int correctAnswers, int totalQuestions);
bool type_related(string type_to_focus, string curr_type);
void reorder(Question questions[], int size, int idx);

#ifndef UNIT_TEST
int main()
{
    const int MAX_QUESTIONS = 1000;
    Question questions[MAX_QUESTIONS];
    int questionCount = 0;

    read_file("cs135_midterm_f24_v1.txt", questions, MAX_QUESTIONS, questionCount);
    read_file("cs135_midterm_f24_v2.txt", questions, MAX_QUESTIONS, questionCount);
    read_file("cs135_midterm_s24_v1.txt", questions, MAX_QUESTIONS, questionCount);

    const int MAX_TYPES = 30;
    string typeList[MAX_TYPES];
    int typeCount = 0;

    insert_order_unique(typeList, MAX_TYPES, typeCount, questions, questionCount);
    string selectedType = choose_type(typeList, typeCount);
    answer_by_type(questions, questionCount, selectedType);

    return 0;
}
#endif

void read_file(const string &fileName, Question questions[], int capacity, int &count)
{
    ifstream fin(fileName);
    if (fin.fail())
    {
        cerr << fileName << " cannot be opened" << endl;
        exit(1);
    }

    string currentLine;
    while (getline(fin, currentLine) && currentLine.find("question: ") != 0 && currentLine.find("Question: ") != 0)
        ;

    while (!fin.eof() && (currentLine.find("question: ") == 0 || currentLine.find("Question: ") == 0))
    {
        string questionText = currentLine.substr(currentLine.find(":") + 2);
        string answerText, explanationText, versionInfo, typeInfo, labelInfo;

        while (getline(fin, currentLine) && currentLine.find("answer: ") != 0)
            questionText += '\n' + currentLine;

        if (currentLine.find("answer: ") == 0)
        {
            answerText = currentLine.substr(strlen("answer: "));
            while (getline(fin, currentLine) && currentLine.find("question: ") != 0 && currentLine.find("version: ") != 0 && currentLine.find("label: ") != 0 && currentLine.find("type: ") != 0 && currentLine.find("explanation: ") != 0)
            {
                answerText += '\n' + currentLine;
            }
            if (currentLine.find("explanation: ") == 0)
            {
                explanationText = currentLine.substr(strlen("explanation: "));
                while (getline(fin, currentLine) && currentLine.find("question: ") != 0 && currentLine.find("version: ") != 0 && currentLine.find("label: ") != 0 && currentLine.find("type: ") != 0)
                {
                    explanationText += '\n' + currentLine;
                }
            }
            do
            {
                if (currentLine.find("version: ") == 0)
                    versionInfo = currentLine.substr(strlen("version: "));
                else if (currentLine.find("type: ") == 0)
                    typeInfo = currentLine.substr(strlen("type: "));
                else if (currentLine.find("label: ") == 0)
                    labelInfo = currentLine.substr(strlen("label: "));
            } while (getline(fin, currentLine) && currentLine.find("question: ") != 0 && currentLine.find("Question: ") != 0);

            if (count >= capacity)
            {
                fin.close();
                return;
            }
            questions[count].text = questionText;
            questions[count].answer = answerText;
            questions[count].explanation = explanationText;
            questions[count].version = versionInfo;
            questions[count].type = typeInfo;
            questions[count].label = labelInfo;
            ++count;
        }
    }
    fin.close();
}

void display(const Question questions[], int count)
{
    for (int i = 0; i < count; ++i)
    {
        cout << i + 1 << ".\n";
        cout << "question: " << questions[i].text << "\n";
        cout << "answer: " << questions[i].answer << "\n";
        cout << "explanation: " << questions[i].explanation << "\n";
        cout << "type: " << questions[i].type << "\n";
        cout << "version: " << questions[i].version << "\n";
        cout << "label: " << questions[i].label << "\n\n";
    }
}

string trim(const string &input)
{
    size_t start = input.find_first_not_of(" \t\n\r");
    if (start == string::npos)
        return "";
    size_t end = input.find_last_not_of(" \t\n\r");
    return input.substr(start, end - start + 1);
}

int count_occurrences(const string &input, char character)
{
    int counter = 0;
    for (char ch : input)
        if (ch == character)
            ++counter;
    return counter;
}

string *extract_type(const string &typeField, int &typeCount)
{
    typeCount = count_occurrences(typeField, ';') + 1;
    string *extracted = new string[typeCount];
    size_t pos = 0;
    for (int i = 0; i < typeCount; ++i)
    {
        size_t next = typeField.find(';', pos);
        if (next == string::npos)
            next = typeField.length();
        extracted[i] = trim(typeField.substr(pos, next - pos));
        pos = next + 1;
    }
    return extracted;
}

void insert_order_unique(string typeArray[], int maxTypes, int &currentTypeCount, const string &newType)
{
    if (currentTypeCount >= maxTypes)
        return;
    int pos = 0;
    while (pos < currentTypeCount && typeArray[pos] < newType)
        ++pos;
    if (pos < currentTypeCount && typeArray[pos] == newType)
        return;
    for (int i = currentTypeCount; i > pos; --i)
        typeArray[i] = typeArray[i - 1];
    typeArray[pos] = newType;
    ++currentTypeCount;
}

void insert_order_unique(string typeArray[], int maxTypes, int &currentTypeCount, const Question questions[], int questionCount)
{
    for (int i = 0; i < questionCount; ++i)
    {
        int n;
        string *arr = extract_type(questions[i].type, n);
        for (int j = 0; j < n; ++j)
        {
            insert_order_unique(typeArray, maxTypes, currentTypeCount, arr[j]);
        }
        delete[] arr;
    }
}

void randomize(Question questions[], int count)
{
    srand((unsigned)time(nullptr));
    for (int i = count - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);
        swap(questions[i], questions[j]);
    }
}

string choose_type(const string availableTypes[], int typeCount)
{
    cout << "0. ALL TYPES\n";
    for (int i = 0; i < typeCount; ++i)
        cout << i + 1 << ". " << availableTypes[i] << "\n";
    int choice;
    do
    {
        cout << "Choose a type (0-" << typeCount << "): ";
        if (!(cin >> choice) || choice < 0 || choice > typeCount)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid choice. Try again.\n";
        }
        else
            break;
    } while (true);
    cin.ignore(INT_MAX, '\n');
    return (choice == 0 ? string() : availableTypes[choice - 1]);
}

void answer_by_type(Question questions[], int count, const string &chosenType)
{
    randomize(questions, count);
    int correct = 0, total = 0;
    for (int i = 0; i < count; ++i)
        if (chosenType.empty() || questions[i].type.find(chosenType) != string::npos)
            ++total;
    for (int i = 0; i < count; ++i)
    {
        if (!chosenType.empty() && questions[i].type.find(chosenType) == string::npos)
            continue;
        cout << "question " << questions[i].version << " " << questions[i].label << ": " << questions[i].text << "\n";
        bool ok = false;
        for (int tries = 1; tries <= 3; ++tries)
        {
            cout << "Enter your answer: ";
            string resp;
            getline(cin, resp);
            if (trim(resp) == trim(questions[i].answer))
            {
                cout << "true\n";
                ok = true;
                ++correct;
                break;
            }
            else
            {
                cout << "false\n";
            }
        }
        if (!ok)
        {
            if (!questions[i].explanation.empty())
                cout << "Explanation: " << questions[i].explanation << "\n";
            if (chosenType.empty())
                reorder(questions, count, i);
        }
    }
    feedback(correct, total);
}

void feedback(int correctAnswers, int totalQuestions)
{
    cout << "\nCorrect answers: " << correctAnswers << " out of " << totalQuestions << "\n";
    double pct = totalQuestions ? (100.0 * correctAnswers / totalQuestions) : 0.0;
    cout << "Score: " << pct << "%\n";
    if (pct >= 90.0)
        cout << "Excellent!\n";
    else if (pct >= 80.0)
        cout << "Good job.\n";
    else if (pct >= 70.0)
        cout << "Pass.\n";
    else
        cout << "Please ask for help ASAP!\n";
}

bool type_related(string type_to_focus, string curr_type)
{
    int num;
    string *focusArr = extract_type(type_to_focus, num);
    for (int i = 0; i < num; i++)
    {
        if (curr_type.find(focusArr[i]) != string::npos)
        {
            delete[] focusArr;
            return true;
        }
    }
    delete[] focusArr;
    return false;
}

void reorder(Question questions[], int size, int idx)
{
    string focusType = questions[idx].type;
    for (int i = idx + 1; i < size - 1; i++)
    {
        if (!type_related(focusType, questions[i].type))
        {
            for (int j = size - 1; j > i; j--)
            {
                if (type_related(focusType, questions[j].type))
                {
                    swap(questions[i], questions[j]);
                    break;
                }
            }
        }
    }
}