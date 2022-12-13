#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <map>

using namespace std; 
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

void ropeMove(int &x, int &y, int hX, int hY);
void addPair(int x, int y, map<pair<int, int>, bool> &visited);

int main() {
	ifstream input("input.txt");
	string line;
	int x, y, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, hX, hY, toMove, lastX, lastY;
	x = y = x1 = y1 = x2 = y2 = x3 = y3 = x4 = y4 = x5 = y5 = x6 = y6 = x7 = y7 = x8 = y8 = hX = hY = lastX = lastY = 0;
	char inst;
	map<pair<int, int>, bool> visited;
	int score = 1;

	if (input.is_open()) {
		while (getline(input, line)) {
			addPair(x, y, visited);
			inst = line[0];
			toMove = stoi(line.substr(2, line.length()));

			for (int i = 0; i < toMove; i++) {
				
				switch (inst) {
				case 'R':
					hX++;
					break;
				case 'L':
					hX--;
					break;
				case 'U':
					hY++;
					break;
				case 'D':
					hY--;
				}
				ropeMove(x1, y1, hX, hY);
				ropeMove(x2, y2, x1, y1);
				ropeMove(x3, y3, x2, y2);
				ropeMove(x4, y4, x3, y3);
				ropeMove(x5, y5, x4, y4);
				ropeMove(x6, y6, x5, y5);
				ropeMove(x7, y7, x6, y6);
				ropeMove(x8, y8, x7, y7);
				ropeMove(x, y, x8, y8);
				//cout << x << ", " << y << "\n";
				addPair(x, y, visited);

				//print out path of rope in real time
				/*for (int j = 10; j >= -10; j--) {
					for (int i = -30; i < 30; i++) {
						if (hX == i && hY == j)
							cout << "H";
						else if (x1 == i && y1 == j)
							cout << "1";
						else if (x2 == i && y2 == j)
							cout << "2";
						else if (x3 == i && y3 == j)
							cout << "3";
						else if (x4 == i && y4 == j)
							cout << "4";
						else if (x5 == i && y5 == j)
							cout << "5";
						else if (x6 == i && y6 == j)
							cout << "6";
						else if (x7 == i && y7 == j)
							cout << "7";
						else if (x8 == i && y8 == j)
							cout << "8";
						else if (x == i && y == j)
							cout << "T";
						else cout << ".";
					}
					cout << "\n";
				}
				cout << score << "\n";
				score++;
				sleep_for(100ms);
				if (score == 92)
					cout << "gmmmmmmmmm\n";*/
			}
		}

		for (int j = 10; j >= -10; j--) {
			for (int i = -30; i < 30; i++) {
				pair<int, int> check = make_pair(i, j);
				if (visited.count(check))
					cout << "#";
				else cout << ".";
			}
			cout << "\n";
		}

		cout << visited.size() << "\n";
		//cout << score;
	} else { cout << "input not open! \n"; }
}

void ropeMove(int &x, int &y, int hX, int hY) {
	if (hX - x > 1) {
		x = hX - 1;
		if (hY - y > 1) {
			y = hY - 1;
		} else if (hY - y < -1) {
			y = hY + 1;
		} else y = hY;
	}else if (hX - x < -1) {
		x = hX + 1;
		if (hY - y > 1) {
			y = hY - 1;
		} else if (hY - y < -1) {
			y = hY + 1;
		} else y = hY;
	} else if (hY - y > 1) {
		y = hY - 1;
		if (hX - x > 1) {
			x = hX - 1;
		} else if (hY - y < -1) {
			x = hX + 1;
		} else x = hX;
	} else if (hY - y < -1) {
		y = hY + 1;
		if (hX - x > 1) {
			x = hX - 1;
		} else if (hY - y < -1) {
			x = hX + 1;
		} else x = hX;
	}
}

void addPair(int x, int y, map<pair<int, int>, bool>& visited) {
	pair<int, int> toIns = make_pair(x, y);
	visited.try_emplace(toIns, true);
}