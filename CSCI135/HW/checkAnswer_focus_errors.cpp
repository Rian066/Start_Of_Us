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
#include <string.h>
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

void read_file(string fileName, Question questions[], int capacity, int &count);
void display(Question questions[], int count);
string trim(string input);
int count_occurrences(string input, char character);
string *extract_type(string typeField, int &typeCount);
void insert_order_unique(string typeArray[], int maxTypes, int &currentTypeCount, string newType);
void insert_order_unique(string typeArray[], int maxTypes, int &currentTypeCount, Question questions[], int questionCount);
void randomize(Question questions[], int count);
string choose_type(string *availableTypes, int typeCount);
void answer_by_type(Question questions[], int count, string selectedType);
void feedback(int correctAnswers, int totalQuestions);

// --- Task C additions ---
bool type_related(string type_to_focus, string curr_type);
void reorder(Question questions[], int count, int idx);

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

void read_file(string fileName, Question questions[], int capacity, int &count)
{
    ifstream fin(fileName);
    if (fin.fail())
    {
        cerr << fileName << " cannot be opened" << endl;
        exit(1);
    }

    string currentLine;
    while (getline(fin, currentLine) && !(currentLine.find("question: ") || currentLine.find("Question: ")))
        ;

    while (!fin.eof() && (currentLine.find("question: ") || currentLine.find("Question: ")))
    {
        string questionText = currentLine.substr(currentLine.find(":") + 2);
        string answerText, explanationText, versionInfo, typeInfo, labelInfo;

        while (getline(fin, currentLine) && !currentLine.find("answer: "))
            questionText += '\n' + currentLine;

        if (currentLine.find("answer: "))
        {
            answerText = currentLine.substr(strlen("answer: "));
            currentLine = "";
            while (getline(fin, currentLine) &&
                   !(currentLine.find("question: ") ||
                     currentLine.find("version: ") ||
                     currentLine.find("label: ") ||
                     currentLine.find("type: ") ||
                     currentLine.find("explanation: ")))
            {
                answerText += '\n' + currentLine;
            }
            if (currentLine.find("explanation: "))
            {
                explanationText = currentLine.substr(strlen("explanation: "));
                while (getline(fin, currentLine) &&
                       !(currentLine.find("question: ") ||
                         currentLine.find("version: ") ||
                         currentLine.find("label: ") ||
                         currentLine.find("type: ")))
                {
                    explanationText += '\n' + currentLine;
                }
            }
            do
            {
                if (currentLine.find("version: "))
                    versionInfo = currentLine.substr(strlen("version: "));
                else if (currentLine.find("type: "))
                    typeInfo = currentLine.substr(strlen("type: "));
                else if (currentLine.find("label: "))
                    labelInfo = currentLine.substr(strlen("label: "));
                currentLine = "";
            } while (getline(fin, currentLine) &&
                     !currentLine.find("question: ") &&
                     !currentLine.find("Question: "));

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
            count++;
        }
    }
    fin.close();
}

void display(Question questions[], int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << i + 1 << ". " << endl;
        cout << "question: " << questions[i].text << endl;
        cout << "answer: " << questions[i].answer << endl;
        cout << "explanation: " << questions[i].explanation << endl;
        cout << "type: " << questions[i].type << endl;
        cout << "version: " << questions[i].version << endl;
        cout << "label: " << questions[i].label << endl;
        cout << endl;
    }
}

string trim(string input)
{
    int startPos = 0;
    while (startPos < input.size() && isspace(input[startPos]))
        startPos++;

    int endPos = input.size() - 1;
    while (endPos >= 0 && isspace(input[endPos]))
        endPos--;

    if (startPos > endPos)
        return "";
    return input.substr(startPos, endPos - startPos + 1);
}

int count_occurrences(string input, char character)
{
    int counter = 0;
    for (char ch : input)
        if (ch == character)
            counter++;
    return counter;
}

string *extract_type(string typeField, int &typeCount)
{
    typeCount = count_occurrences(typeField, ';') + 1;
    string *extractedTypes = new string[typeCount];
    int startPos = 0, endPos = 0, currentIndex = 0;
    while (startPos < (int)typeField.size())
    {
        endPos = typeField.find(';', startPos);
        if (endPos == string::npos)
            endPos = typeField.size();
        extractedTypes[currentIndex++] = trim(typeField.substr(startPos, endPos - startPos));
        startPos = endPos + 1;
    }
    return extractedTypes;
}

void insert_order_unique(string typeArray[], int maxTypes, int &currentTypeCount, string newType)
{
    if (currentTypeCount >= maxTypes)
        return;
    int pos = 0;
    while (pos < currentTypeCount && typeArray[pos] < newType)
        pos++;
    if (pos < currentTypeCount && typeArray[pos] == newType)
        return;
    for (int i = currentTypeCount; i > pos; i--)
        typeArray[i] = typeArray[i - 1];
    typeArray[pos] = newType;
    currentTypeCount++;
}

void insert_order_unique(string typeArray[], int maxTypes, int &currentTypeCount, Question questions[], int questionCount)
{
    for (int i = 0; i < questionCount; i++)
    {
        int extractedTypeCount = 0;
        string *types = extract_type(questions[i].type, extractedTypeCount);
        for (int j = 0; j < extractedTypeCount; j++)
            insert_order_unique(typeArray, maxTypes, currentTypeCount, types[j]);
        delete[] types;
    }
}

void randomize(Question questions[], int count)
{
    srand((unsigned)time(NULL));
    for (int i = count - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(questions[i], questions[j]);
    }
}

string choose_type(string *availableTypes, int typeCount)
{
    cout << "0. ALL TYPES" << endl;
    for (int i = 0; i < typeCount; i++)
        cout << (i + 1) << ". " << availableTypes[i] << endl;

    int choice = -1;
    do
    {
        cout << "Choose a type (0-" << typeCount << "): ";
        cin >> choice;
        if (cin.fail() || choice < 0 || choice > typeCount)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice < 0 || choice > typeCount);

    cin.ignore(INT_MAX, '\n');
    return (choice == 0 ? string() : availableTypes[choice - 1]);
}

void answer_by_type(Question ques[], int size, string chosenType)
{
    randomize(ques, size);

    int correctCount = 0;
    int totalQuestions = 0;

    for (int i = 0; i < size; i++)
        if (chosenType.empty() || ques[i].type.find(chosenType) != string::npos)
            totalQuestions++;

    for (int i = 0; i < size; i++)
    {
        if (!chosenType.empty() && ques[i].type.find(chosenType) == string::npos)
            continue;

        cout << "question " << ques[i].version << " " << ques[i].label
             << ": " << ques[i].text << endl;

        bool isCorrect = false;
        for (int tries = 1; tries <= 3 && !isCorrect; tries++)
        {
            cout << "Enter you answer: ";
            string userAnswer;
            getline(cin, userAnswer);
            if (trim(userAnswer) == trim(ques[i].answer))
            {
                cout << "true" << endl;
                isCorrect = true;
                correctCount++;
            }
            else
            {
                cout << "false" << endl;
            }
        }

        if (!isCorrect)
        {
            if (chosenType.empty())
            {
                reorder(ques, size, i);
            }
            if (!ques[i].explanation.empty())
                cout << "Explanation: " << ques[i].explanation << endl;
        }
    }

    feedback(correctCount, totalQuestions);
}

void feedback(int numCorrect, int total)
{
    cout << "\nCorrect answers: " << numCorrect << " out of " << total << endl;
    double percent = (total > 0) ? (double)numCorrect / total * 100 : 0;
    cout << "Score: " << percent << "%" << endl;
    if (percent >= 90)
        cout << "Excellent!" << endl;
    else if (percent >= 80)
        cout << "Good job." << endl;
    else if (percent >= 70)
        cout << "Pass." << endl;
    else
        cout << "Please ask for help ASAP!" << endl;
}

bool type_related(string type_to_focus, string curr_type)
{
    int n;
    string *parts = extract_type(type_to_focus, n);
    bool related = false;
    for (int i = 0; i < n; i++)
    {
        if (curr_type.find(parts[i]) != string::npos)
        {
            related = true;
            break;
        }
    }
    delete[] parts;
    return related;
}

void reorder(Question questions[], int count, int idx)
{
    string focus = questions[idx].type;
    int left = idx + 1, right = count - 1;
    while (left < right)
    {
        while (left < count && type_related(focus, questions[left].type))
            left++;
        while (right > idx && !type_related(focus, questions[right].type))
            right--;
        if (left < right)
        {
            swap(questions[left], questions[right]);
            left++;
            right--;
        }
    }
}