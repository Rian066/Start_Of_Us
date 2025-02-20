#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    vector<int> Ann, Bob, Carol, Deb;
    fstream fin("text.txt");
    int test1, test2, test3, highestScore = 0;
    string name, header;

    getline(fin, header);
    while (fin >> name >> test1 >> test2 >> test3)
    {
        if (test1 > highestScore)
        {
            name = name;
            highestScore = test1;
        }
    }

    cout << "Top student is: " << name << " " << highestScore << endl;
}
