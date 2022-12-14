#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void insertPair(map<int, set<int>*>& cave, int x, int y);
bool dropSand(map<int, set<int>*>& cave, int x, int y, int maxY);

int main() {
	ifstream input("input.txt");
	string line;
	map<int, set<int>*> cave;
	int score = 0;

	if (input.is_open()) {
		int maxY = 0;
		while (getline(input, line)) {
			int i = 0;
			pair<int, int> last = make_pair(-1, -1);
			while (i < line.length()) {
				int x = stoi(line.substr(i, line.find(',', i)));
				i = line.find(',', i) + 1;

				int y = stoi(line.substr(i, line.find(" ->", i)));
				int shift = line.find(" ->", i);
				if (shift != -1)
					i = shift + 4;
				else
					i = line.length();

				if (y > maxY)
					maxY = y;

				insertPair(cave, x, y);

				if (last != make_pair(-1, -1)) {
					if (last.first > x) {
						for (int i = x + 1; i < last.first; i++)
							insertPair(cave, i, y);
					} else if (last.first < x) {
						for (int i = last.first + 1; i < x; i++)
							insertPair(cave, i, y);
					} else if (last.second > y) {
						for (int i = y + 1; i < last.second; i++)
							insertPair(cave, x, i);
					} else {
						for (int i = last.second + 1; i < y; i++)
							insertPair(cave, x, i);
					}
				}

				last = make_pair(x, y);
			}
		}

		maxY += 2;

		while (cave[500]->count(0) < 1) {
			dropSand(cave, 500, 0, maxY);
			score++;
		}

		cout << score;

		/*for (pair<int, set<int>*> rocks : cave) {
			for (int y : *rocks.second) {
				cout << rocks.first << ", " << y << "\n";
			}
		}*/
	} else { cout << "input not open! \n"; }
}

void insertPair(map<int, set<int>*>& cave, int x, int y) {
	if (cave.count(x) < 1) {
		set<int>* toIns = new set<int>;
		cave.emplace(x, toIns);
	}
	cave[x]->insert(y);
}

bool dropSand(map<int, set<int>*>& cave, int x, int y, int maxY) {
	bool hit = false;
	set<int>::iterator iter = cave[x]->begin();
	for (int i = 0; i < cave[x]->size(); i++) {
		if (*iter > y) {
			y = *iter - 1;
			hit = true;
			break;
		}
		iter++;
	}
	if (!hit) {
		insertPair(cave, x, maxY - 1);
		return true;
	}

	if (cave.count(x - 1) == 0) {
		insertPair(cave, x - 1, maxY - 1);
		return true;
	} else if (cave[x - 1]->count(y + 1) == 0) {
		return dropSand(cave, x - 1, y, maxY);
	} else if (cave.count(x + 1) == 0) {
		insertPair(cave, x + 1, maxY - 1);
		return true;
	} else if (cave[x + 1]->count(y + 1) == 0) {
		return dropSand(cave, x + 1, y, maxY);
	} else {
		insertPair(cave, x, y);
		//cout << x << ", " << y << "\n";
		return true;
	}
}