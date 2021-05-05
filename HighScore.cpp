#include "Header.h"

void HS()
{
    clearScreen();
    ifstream ReadFile;

    ReadFile.open("Score.txt", std::ios::in);

    vector<int> l;
    while (!ReadFile.eof())
    {
        int n;
        ReadFile >> n;
        l.push_back(n);
    }
    ReadFile.close();

    sort(l.begin(), l.end());
    for (int i = 1; i <= 3; i++)
        cout << i << ".  " << l[i] << " seconds" << endl;
}