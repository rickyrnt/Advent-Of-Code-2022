// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int getVal(char a);

int main()
{
    int score = 0;
    ifstream input("input.txt");
    string line, ln2, ln3;

    if (input.is_open()) {
        //part two

    funny:
        while (getline(input, line)) {
            getline(input, ln2);
            getline(input, ln3);

            while (true) {
                for (int i = 0; i < line.length(); i++) {
                    for (int j = 0; j < ln2.length(); j++) {
                        if (line[i] == ln2[j]) {
                            for (int k = 0; k < ln3.length(); k++) {
                                if (ln3[k] == line[i]) {
                                    score += getVal(line[i]);
                                    goto funny;
                                }
                            }
                        }
                    }
                }
            }
        }
        cout << score;

        /*part one
    funny:
        while (getline(input, line)) {
            //O(n^2). Cry about it.
            for (int i = 0; i < line.length() / 2; i++) {
                for (int j = line.length() / 2; j < line.length(); j++) {
                    if (line[i] == line[j]) {
                        score += getVal(line[i]);
                        goto funny;
                    }
                }
            }
        }
        cout << score;
        */
    } else { cout << "input not open!"; }
}

int getVal(char a) {
    if (a >= 97) {
        return a - 96;
    } else return a - 38;
}