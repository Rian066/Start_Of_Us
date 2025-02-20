/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Project 1 A
*/
/*
This program matches user answer with gives answer to a question.
*/

#include <iostream>
using namespace std;

int main()
{
    string q1, q2, ans1, ans2, user_ans;

    q1 = "What is -1 + 5 / 3 ?";
    q2 = "Assume that n is properly declared and initialized. Write a condition to represent that n does NOT satisify 0 < n < 100.";

    ans1 = "0";
    ans2 = "(n <= 0 || n >= 100)";

    cout << q1 << endl
         << "Your answer: ";
    cin >> user_ans;

    cout << boolalpha << (ans1 == user_ans) << endl;
    cin.ignore();

    cout << endl
         << q2 << endl
         << "Your answer: ";
    getline(cin, user_ans);

    cout << boolalpha << (ans2 == user_ans) << endl;
}