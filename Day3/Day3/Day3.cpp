// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
    int score = 0;
    ifstream input("input.txt");
    string line;

    if (input.is_open()) {
        while (getline(input, line)) {
            //O(n^2). Cry about it.
        funny:
            for (int i = 0; i < line.length() / 2; i++) {
                for (int j = line.length() / 2; j < line.length(); j++) {
                    if (line[i] == line[j]) {
                        cout << line[i] << " aka " << getVal(line[i]) << "\n";
                        goto funny;
                    }
                }
            }
        }
    }
}

int getVal(char a) {
    if (a >= 97) {
        return 96 - a;
    } else return 92 - a;
}