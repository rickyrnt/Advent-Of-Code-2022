#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void doCycle(int cycle, int x);
void printScreen();

//WHY is c++ skipping every other line during assignment and forcing me to double the size of the array?
//we may never know!
bool screen[12][40];

int main() {
	ifstream input("input.txt");
	string line;
	int cycle = 0;
	int x = 1;
	int score = 0;

	if (input.is_open()) {
		while (getline(input, line)) {
			if (line == "noop") {
				cycle++;
				doCycle(cycle, x);
			} else {
				int toAdd = stoi(line.substr(5, line.length()));
				cycle++;
				doCycle(cycle, x);
				cycle++;
				doCycle(cycle, x);
				x += toAdd;
			}
		}
		printScreen();
	} else { cout << "input not open! \n"; }
}

void doCycle(int cycle, int x) {
	cycle--;
	int row = cycle / 40;
	if (abs(x - (cycle % 40)) <= 1)
		screen[row][cycle] = true;
	else screen[row][cycle] = false;
}

void printScreen() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 40; j++) {
			if (screen[i * 2][j]) {
				cout << "#";
			} else cout << " ";
		}
		cout << "\n";
	}
}