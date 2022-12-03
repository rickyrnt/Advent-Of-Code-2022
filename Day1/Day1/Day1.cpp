// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
    string line;
    ifstream myfile("adv1.txt");
    vector<int> cals;
    cals.push_back(0);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line.length() == 0) {
                cals.push_back(0);
            } else {
                cals.back() += stoi(line, nullptr);
            }
        }
        myfile.close();
    } else {
        cout << "file not open!";
    }
    sort(cals.begin(), cals.end());

    cout << cals[cals.size() - 1] + cals[cals.size() - 2] + cals[cals.size() - 3];
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
