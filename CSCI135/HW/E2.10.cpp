/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: E2.10
*/
/*
This program finds the cost per 100 miles.
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    double gallons, mpg, gas_price, cost, distance;
    cout << "How many gallons: ";
    cin >> gallons;
    cout << "What's the fuel efficiency: ";
    cin >> mpg;
    cout << "What is the price of gas: ";
    cin >> gas_price;

    cost = (100 / mpg) * gas_price;
    distance = mpg * gallons;

    cout << cost << " " << distance << endl;
}