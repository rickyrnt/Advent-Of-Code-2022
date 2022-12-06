#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
	ifstream input("input.txt");
	string line;
	int index = 0;

	if (input.is_open()) {
		while (getline(input, line)) {
		checkNext:
			for (int i = index; i < index + 13; i++) {
				for (int j = i + 1; j < index + 14; j++) {
					if (line[j] == line[i]) {
						index++;
						goto checkNext;
					}
				}
			}
			cout << index + 14;
		}
	} else { cout << "input not open! \n"; }
}