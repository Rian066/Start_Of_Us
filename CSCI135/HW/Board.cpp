/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Project 3C
*/
/*
This program makes the play method.
*/

#include "Board.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

Board::Board() : Board(6, 4)
{
}

Board::Board(int numBins, int capacity)
{

    if (numBins < 5)
    {

        numBins = 5;
    }

    if (capacity < 4)
    {

        capacity = 4;
    }

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
    {

        cout << "--+";
    }

    cout << endl;
}

void Board::display() const
{

    string mapping[] = {

        "\033[31m\u2b24\033[0m", // Red ball (player 0)

        "\033[34m\u2b1f\033[0m", // Blue pentagon (player 1)

        "\033[31m\u25c9\033[0m", // Red double circle (player 2)

        "\033[34m\u2b54\033[0m" // Blue empty pentagon (player 3)

    };

    print(numBins);

    for (int j = capacity - 1; j >= 0; j--)
    {

        cout << "|";

        for (int i = 0; i < numBins; i++)
        {

            if (j < (int)grid[i].size())
            {

                int player = grid[i][j];

                cout << mapping[player % 4] << "|";
            }
            else
            {

                cout << "  |";
            }
        }

        cout << endl;

        print(numBins);
    }

    cout << " ";

    for (int i = 0; i < numBins; i++)
    {

        cout << " " << i << " ";
    }

    cout << endl;
}

int Board::add(int player)
{

    int bin;

    while (true)
    {

        cout << "Enter a bin index in [0, " << numBins - 1 << ") that is not full: ";

        cin >> bin;

        if (bin < 0 || bin >= numBins)
        {

            cout << "invalid bin index, needs to be in [0, " << numBins - 1 << ")" << endl;
        }
        else if (grid[bin].size() < capacity)
        {

            grid[bin].push_back(player);

            return bin;
        }
        else
        {

            cout << "the bin is full" << endl;
        }
    }
}

struct Coord
{

    int bin; // bin index (column)

    int idx; // index inside the bin (row)
};

int Board::winInHorizontal(int bin)
{

    if (grid[bin].empty())
    {

        return -1;
    }

    int index = grid[bin].size() - 1;

    int player = grid[bin][index];

    vector<Coord> candidates;

    int count = 1;

    Coord current;

    current.bin = bin;

    current.idx = index;

    candidates.push_back(current);

    for (int i = bin - 1; i >= 0; i--)
    {

        if (index < grid[i].size() && grid[i][index] == player)
        {

            Coord lf;

            lf.bin = i;

            lf.idx = index;

            candidates.push_back(lf);

            count++;
        }
        else
        {

            break;
        }
    }

    for (int i = bin + 1; i < numBins; i++)
    {

        if (index < grid[i].size() && grid[i][index] == player)
        {

            Coord rig;

            rig.bin = i;

            rig.idx = index;

            candidates.push_back(rig);

            count++;
        }
        else
        {

            break;
        }
    }

    if (count >= 4)
    {

        for (const Coord &coord : candidates)
        {

            grid[coord.bin][coord.idx] = player + 2;
        }

        return player;
    }

    return -1;
}

int Board::winInVertical(int bin)
{

    if (bin < 0 || bin >= numBins || grid[bin].empty())
        return -1;

    int player = grid[bin].back();

    for (int col = 0; col < numBins; ++col)
    {

        int count = 0;

        vector<Coord> candidates;

        for (int row = 0; row < (int)grid[col].size(); ++row)
        {

            if (grid[col][row] == player)
            {

                candidates.push_back({col, row});

                count++;

                if (count >= 4)
                {

                    for (const Coord &c : candidates)
                    {

                        grid[c.bin][c.idx] = player + 2; // Mark the winning discs
                    }

                    return player;
                }
            }
            else
            {

                count = 0;

                candidates.clear();
            }
        }
    }

    return -1;
}

int Board::winInDiagonal(int bin)
{

    if (bin < 0 || bin >= numBins || grid[bin].empty())
        return -1;

    int player = grid[bin].back();

    // Diagonal (\)

    for (int col = 0; col <= numBins - 4; ++col)
    {

        for (int row = 0; row <= capacity - 4; ++row)
        {

            vector<Coord> candidates;

            bool win = true;

            for (int i = 0; i < 4; ++i)
            {

                if ((int)grid[col + i].size() <= row + i || grid[col + i][row + i] != player)
                {

                    win = false;

                    break;
                }

                candidates.push_back({col + i, row + i});
            }

            if (win)
            {

                for (const Coord &c : candidates)
                {

                    grid[c.bin][c.idx] = player + 2;
                }

                return player;
            }
        }
    }

    // Anti-diagonal (/)

    for (int col = 0; col <= numBins - 4; ++col)
    {

        for (int row = capacity - 1; row >= 3; --row)
        {

            vector<Coord> candidates;

            bool win = true;

            for (int i = 0; i < 4; ++i)
            {

                if ((int)grid[col + i].size() <= row - i || grid[col + i][row - i] != player)
                {

                    win = false;

                    break;
                }

                candidates.push_back({col + i, row - i});
            }

            if (win)
            {

                for (const Coord &c : candidates)
                {

                    grid[c.bin][c.idx] = player + 2;
                }

                return player;
            }
        }
    }

    return -1; // No winner
}

int Board::win(int bin)
{

    int res;

    res = winInHorizontal(bin);

    if (res != -1)
        return res;

    res = winInVertical(bin);

    if (res != -1)
        return res;

    res = winInDiagonal(bin);

    if (res != -1)
        return res;

    return -1; // No winner
}

void Board::play()
{

    display();

    int player = 0;

    string players[] = {"red", "blue"};

    int count = 1;

    int winner = -1;

    while (winner == -1)
    {

        cout << "num drops: " << count << ", player: " << players[player] << endl;

        int bin = add(player);

        winner = win(bin);

        if (winner != -1)
        {

            cout << "winner: " << players[winner] << endl;

            display();

            break;
        }

        display();

        bool Full = true;

        for (int i = 0; i < numBins; i++)
        {

            if (grid[i].size() < capacity)
            {

                Full = false;

                break;
            }
        }

        if (Full)
        {

            cout << "a tie" << endl;

            break;
        }

        player = (player + 1) % 2;

        count++;
    }
}