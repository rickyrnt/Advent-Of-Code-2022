#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct monkey {
	vector<unsigned long long> items;
	string op;
	unsigned long long opNum, divBy, toTrue, toFalse;
	unsigned long inspections = 0;
};

int main() {
	ifstream input("input.txt");
	string line;
	vector<monkey> monks;
	unsigned long primeDivisor = 1;

	if (input.is_open()) {
		while (getline(input, line)) {
			//insert leading break into input to make this align
			getline(input, line);
			monkey funky;
			//starting items
			getline(input, line);
			for (int i = line.find(": ") + 2; i < line.length(); i += 4) {
				funky.items.push_back(stoi(line.substr(i, i + 2)));
			}
			//operation
			getline(input, line);
			if (line[23] == '*') {
				if (line[25] == 'o')
					funky.op = "**";
				else {
					funky.op = "*";
					funky.opNum = stoi(line.substr(25, line.length()));
				}
			} else {
				funky.op = "+";
				funky.opNum = stoi(line.substr(25, line.length()));
			}
			//test
			getline(input, line);
			funky.divBy = stoi(line.substr(21, line.length()));
			primeDivisor *= funky.divBy;
			getline(input, line);
			funky.toTrue = stoi(line.substr(29, line.length()));
			getline(input, line);
			funky.toFalse = stoi(line.substr(30, line.length()));
			monks.push_back(funky);
		}
		for (int i = 0; i < 10000; i++) {
			for (int j = 0; j < monks.size(); j++) {
				monkey* disMonk = &monks[j];
				for (int k = 0; k < disMonk->items.size(); k++) {
					disMonk->inspections++;
					if (disMonk->op == "**") {
						disMonk->items[k] *= disMonk->items[k];
					} else if (disMonk->op[0] == '*') {
						disMonk->items[k] *= disMonk->opNum;
					} else {
						disMonk->items[k] += disMonk->opNum;
					}

					//disMonk->items[k] /= 3;
					disMonk->items[k] %= primeDivisor;

					if (disMonk->items[k] % disMonk->divBy == 0) {
						monks[disMonk->toTrue].items.push_back(disMonk->items[k]);
					} else monks[disMonk->toFalse].items.push_back(disMonk->items[k]);
				}
				disMonk->items.clear();
			}
		}
		unsigned long long most = monks[0].inspections;
		unsigned long long most2 = monks[1].inspections;
		if (most2 > most) {
			int temp = most;
			most = most2;
			most2 = temp;
		}
		for (int i = 2; i < monks.size(); i++) {
			if (monks[i].inspections > most) {
				most2 = most;
				most = monks[i].inspections;
			} else if (monks[i].inspections > most2) {
				most2 = monks[i].inspections;
			}
		}
		unsigned long long out = most * most2;
		cout << out;
	} else { cout << "input not open! \n"; }
}