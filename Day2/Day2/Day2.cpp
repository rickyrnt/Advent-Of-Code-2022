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
    char opp, you;

    if (input.is_open()) {
        while (getline(input, line)) {
            opp = line[0];
            you = line[2];
            if (you == 'X') {
                if (opp == 'A') {
                    score += 3;
                } else if (opp == 'B') {
                    score += 1;
                } else {
                    score += 2;
                }
            } else if (you == 'Y') {
                score += 3;
                if (opp == 'A') {
                    score += 1;
                } else if (opp == 'B') {
                    score += 2;
                } else {
                    score += 3;
                }
            } else {
                score += 6;
                if (opp == 'A') {
                    score += 2;
                } else if (opp == 'B') {
                    score += 3;
                } else {
                    score ++;
                }
            }
        }
        cout << score;
    }
}