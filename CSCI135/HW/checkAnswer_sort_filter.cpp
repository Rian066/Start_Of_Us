/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Project 1 D
*/
/*
This program sorts using question type.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // for transform()

using namespace std;

// Function to trim spaces from a string (leading and trailing)
string trim(const string &str)
{
    size_t first = str.find_first_not_of(" ");
    size_t last = str.find_last_not_of(" ");
    return str.substr(first, last - first + 1);
}

// Function to convert string to lowercase
string toLowerCase(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

struct Question
{
    string question;
    string answer;
    string type;
    string explanation;
};

int main()
{
    string filename;
    cout << "Enter a txt file name with at least question and answer entries: ";
    cin >> filename;

    ifstream file(filename);
    if (!file)
    {
        cerr << "Error opening file." << endl;
        return 1;
    }

    vector<Question> questions;
    vector<string> types;
    string line, currentQuestion, currentAnswer, currentType, currentExplanation;

    while (getline(file, line))
    {
        if (line.rfind("question:", 0) == 0)
        {
            currentQuestion = line.substr(9);
        }
        else if (line.rfind("answer:", 0) == 0)
        {
            currentAnswer = line.substr(7);
        }
        else if (line.rfind("type:", 0) == 0)
        {
            currentType = line.substr(5);
            currentType = trim(currentType); // Remove leading and trailing spaces
            // Add each type separately if there are multiple types
            size_t pos = 0;
            while ((pos = currentType.find(";")) != string::npos)
            {
                string type = trim(currentType.substr(0, pos));
                if (find(types.begin(), types.end(), type) == types.end())
                {
                    types.push_back(type);
                }
                currentType.erase(0, pos + 1);
            }
            if (find(types.begin(), types.end(), currentType) == types.end())
            {
                types.push_back(trim(currentType));
            }
            questions.push_back({currentQuestion, currentAnswer, currentType, currentExplanation});
        }
        else if (line.rfind("explanation:", 0) == 0)
        {
            currentExplanation = line.substr(12);
        }
    }

    // Sort types using bubble sort
    bubbleSort(types);

    // Display sorted types
    for (size_t i = 0; i < types.size(); ++i)
    {
        cout << i + 1 << ". " << types[i] << endl;
    }

    int choice;
    cout << "Enter the type number: ";
    cin >> choice;

    if (choice < 1 || choice > types.size())
    {
        cerr << "Invalid choice." << endl;
        return 1;
    }

    string selectedType = types[choice - 1];
    int correct = 0, total = 0;

    // Loop through the questions, filtered by selected type
    for (const auto &q : questions)
    {
        if (q.type.find(selectedType) != string::npos)
        {
            total++;
            int tries = 0;
            bool correctAnswer = false;

            while (tries < 3)
            {
                string userAnswer;
                cout << "Question: " << q.question << endl;
                cout << "Enter your answer: ";
                cin.ignore(); // to clear the newline character from previous input
                getline(cin, userAnswer);

                // Trim and convert both answers to lowercase for case-insensitive comparison
                if (toLowerCase(trim(userAnswer)) == toLowerCase(trim(q.answer)))
                {
                    correctAnswer = true;
                    break;
                }
                else
                {
                    cout << "Try " << tries + 1 << " failed." << endl;
                    tries++;
                }
            }

            if (correctAnswer)
            {
                correct++;
            }
            else if (!q.explanation.empty())
            {
                cout << "Explanation: " << q.explanation << endl;
            }
        }
    }

    // Calculate and display percentage and feedback
    double percentage = (correct / (double)total) * 100;
    cout << "Number of correct answers: " << correct << endl;
    cout << "Percentage: " << percentage << "%" << endl;

    if (percentage >= 90)
    {
        cout << "Excellent" << endl;
    }
    else if (percentage >= 80)
    {
        cout << "Good" << endl;
    }
    else if (percentage >= 60)
    {
        cout << "Pass" << endl;
    }
    else
    {
        cout << "Please ask for help ASAP" << endl;
    }

    return 0;
}
