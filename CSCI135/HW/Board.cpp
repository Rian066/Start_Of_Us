/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Project 3A
*/
/*
This program makes the game board.
*/

#include "Board.hpp"
#include <iostream>
#include <vector>

using namespace std;

Board::Board() : Board(6, 4)
{
}

Board::Board(int numBins, int capacity)
{
    if (numBins < 5)
        numBins = 5;
    if (capacity < 4)
        capacity = 4;

    this->numBins = numBins;
    this->capacity = capacity;

    for (int i = 0; i < numBins; i++)
    {
        vector<int> oneBin;
        grid.push_back(oneBin);
    }
}

void print(int numBins)
{
    cout << "+";
    for (int i = 0; i < numBins; i++)
        cout << "--+";
    cout << endl;
}

void Board::display() const
{
    string mapping[] = {
        "\033[31m\u2b24\033[0m",
        "\033[34m\u2b1f\033[0m",
        "\033[31m\u25c9\033[0m",
        "\033[34m\u2b54\033[0m"};

    print(numBins);
    for (int j = capacity - 1; j >= 0; j--)
    {
        cout << "|";
        for (int i = 0; i < numBins; i++)
        {
            if (j < grid[i].size())
                cout << mapping[grid[i][j]] << "|";
            else
                cout << "  |";
        }
        cout << endl;
        print(numBins);
    }

    for (int i = 0; i < numBins; i++)
        cout << " " << i << " ";
    cout << endl;
}

int Board::add(int player)
{
    int bin;
    while (true)
    {
        cout << "Enter a bin index in [0, " << numBins << ") that is not full: ";
        cin >> bin;

        if (bin < 0 || bin >= numBins)
        {
            cout << "invalid bin index, needs to be in [0, " << numBins << ")\n";
        }
        else if (grid[bin].size() >= capacity)
        {
            cout << "the bin is full\n";
        }
        else
        {
            grid[bin].push_back(player);
            return bin;
        }

        cout << "Re-enter a bin index in [0, " << numBins << ") that is not full: ";
    }
}
