#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <bitset>
#include <omp.h>

#define OUT_ROW 2000000
#define CAVE_SIZE 4000001
//#define CAVE_SIZE 20

using namespace std;

bool insertPair(set<pair<int, int>>& cave, int xMin, int xMax);

int main() {
	ifstream input("input.txt");
	string line;
	vector<pair<pair<int, int>, pair<int, int>>> coords;
	//map<int, bool> beacs;
	if (input.is_open()) {
		while (getline(input, line)) {
			int index = line.find("x=") + 2;
			int sensX = stoi(line.substr(index, line.find(",", index) - index));
			index = line.find("y=", index) + 2;
			int sensY = stoi(line.substr(index, line.find(":", index) - index));
			index = line.find("x=", index) + 2;
			int tarX = stoi(line.substr(index, line.find(",", index) - index));
			index = line.find("y=", index) + 2;
			int tarY = stoi(line.substr(index, line.length() - index));

			/*sensX = 5;
			sensY = 5;
			tarX = 3;
			tarY = 5;*/
			coords.push_back(make_pair(make_pair(sensX, sensY), make_pair(tarX, tarY)));
		}
		int count = 0;
#pragma omp parallel for num_threads(5) 
		for (int i = 0; i < CAVE_SIZE; i++) {
			count++;
			set<pair<int, int>> cave;
			if(count % 100000 == 0)
				cout << omp_get_thread_num() << ": test num " << count << "/" << CAVE_SIZE << " (" << (count * 100) / (CAVE_SIZE) << "\%)\n";
			for (pair<pair<int, int>, pair<int, int>> coord : coords) {
				int sensX = coord.first.first;
				int sensY = coord.first.second;
				int tarX = coord.second.first;
				int tarY = coord.second.second;
				int dist = abs(tarX - sensX) + abs(tarY - sensY);
				int row = abs(i - sensY);
				if (row < dist) {
					if (insertPair(cave, max(sensX - (dist - row), 0), min(sensX + (dist - row), CAVE_SIZE))) {
						cave.clear();
						break;
					}
				}
			}

			if (cave.size() > 1) {
				set<pair<int, int>>::iterator iter = cave.begin();
				pair<int, int> out = *iter;
				cout << i << ", " << (out.second + 1) << "\n";
				unsigned long long y = i;
				unsigned long long x = (out.second + 1);
				unsigned long long calculation = y + (x * 4000000);
				cout << calculation << "\n";
			}

			cave.clear();
		}
		/*int score = 0;
		set<pair<int, int>>::iterator iter = cave.begin();
		for (int i = 0; i < cave.size(); i++) {
			pair<int, int> curr = *iter;
			cout << curr.first << "-" << curr.second << "\n";
			score += curr.second - curr.first;
			iter++;
		}
		cout << score - beacs.size() + 1 << "\n";*/
	} else { cout << "input not open! \n"; }
}

bool insertPair(set<pair<int, int>>& cave, int xMin, int xMax) {
	cave.insert(make_pair(xMin, xMax));
	
	bool deleted = true;
	while (cave.size() > 1 && deleted) {
		set<pair<int, int>>::iterator iter = cave.begin();
		deleted = false;
		pair<int, int> curr;
		pair<int, int> prev = *iter;
		for (int i = 0; i < cave.size() - 1; i++) {
			iter++;
			curr = *iter;
			if (curr.first <= prev.second + 1) {
				int lowUp = prev.first;
				int hiUp = prev.second;
				if(curr.second > hiUp)
					hiUp = curr.second;
				if (lowUp == 0 && hiUp == CAVE_SIZE)
					return true;
				cave.erase(curr);
				cave.erase(prev);
				cave.insert(make_pair(lowUp, hiUp));
				deleted = true;
				break;
			}
			prev = curr;
		}
	}
	return false;
}