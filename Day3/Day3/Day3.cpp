// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <bitset>

using namespace std;

int getVal(char a);
void indexChars(string chars, bitset<52>& bits);

int main()
{
    int score = 0;
    ifstream input("input.txt");
    string line, ln2, ln3;
    bitset<52> bits1, bits2, bits3, out;

    if (input.is_open()) {
        //down at the bottom is my initial O(n^2) solution. Now I will implement the O(n) solution for part 2 just for fun
        while (getline(input, line)) {
            getline(input, ln2);
            getline(input, ln3);

            indexChars(line, bits1);
            indexChars(ln2, bits2);
            indexChars(ln3, bits3);

            out = bits1 & bits2 & bits3;
            for (int i = 0; i < 52; i++) {
                if (out[i])
                    score += i + 1;
            }
        }
        cout << score;
    /*    //part two

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

void indexChars(string chars, bitset<52>& bits) {
    //i wrote 'em all out just for fun
    bits = 0b0000000000000000000000000000000000000000000000000000;

    for (int i = 0; i < chars.length(); i++)
        bits[getVal(chars[i] - 1)] = 1;
}