#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream input("input.txt");
    string line, elf1, elf2;
    int st1, ed1, st2, ed2;
    int score = 0;

    if (input.is_open()) {
        while (getline(input, line)) {
            elf1 = line.substr(0, line.find(','));
            elf2 = line.substr(line.find(',') + 1, line.length());
            
            st1 = stoi(elf1.substr(0, elf1.find('-')));
            ed1 = stoi(elf1.substr(elf1.find('-') + 1, elf1.length()));
            st2 = stoi(elf2.substr(0, elf2.find('-')));
            ed2 = stoi(elf2.substr(elf2.find('-') + 1, elf2.length()));

            if ((st1 >= st2 && ed1 <= ed2) || (st2 >= st1 && ed2 <= ed1) || (st1 < st2 && ed1 >= st2) || (st2 < st1 && ed2 >= st1)) {
                score++;
            }
        }
        cout << score;
    } else { cout << "input not open!"; }
}