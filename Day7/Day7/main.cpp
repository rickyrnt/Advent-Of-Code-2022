#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct directory {
	int size, childSize;
	unordered_map<string, directory*> children;
	directory* parent;
	string name;
};


void calcChildSize(directory* start);
void printDirectory(directory* start, int iter);
void getDelete(directory* start);

int score = INT_MAX;
int spaceNeeded = 0;

int main() {
	ifstream input("input.txt");
	string line, target;

	directory root, slash;
	slash.name = "/";
	slash.size = 0;
	root.children["/"] = &slash;
	directory* curr = &root;

	if (input.is_open()) {
		while (getline(input, line)) {
			if (line[0] == '$') {
				if (line.substr(0, 4) == "$ cd") {
					target = line.substr(5, line.length());

					if (target == "..") {
						curr = curr->parent;
					} else {
						curr = curr->children[target];
					}
				}
			} else {
				if (line.substr(0, 3) == "dir") {
					directory* tgtNode = new directory();
					tgtNode->parent = curr;
					tgtNode->size = 0;
					tgtNode->name = line.substr(4, line.length());
					curr->children[line.substr(4, line.length())] = tgtNode;
				} else curr->size += stoi(line.substr(0, line.find(" ")));
			}
		}
		
		calcChildSize(&slash);
		printDirectory(&slash, 0);

		spaceNeeded = slash.size + slash.childSize - 40000000;

		getDelete(&slash);

		cout << "score: " << score;

	} else { cout << "input not open! \n"; }
}

void calcChildSize(directory* start) {
	start->childSize = 0;
	for (pair<string, directory*> child : start->children) {
		calcChildSize(child.second);
		start->childSize += child.second->size + child.second->childSize;
	}
}

void printDirectory(directory* start, int iter) {
	cout << string(iter * 4, ' ') << "-" << start->name << " size " << start->size + start->childSize << "\n";
	for (pair<string, directory*> child : start->children) {
		printDirectory(child.second, iter + 1);
	}
}

void getDelete(directory* start) {
	for (pair<string, directory*> child : start->children) {
		getDelete(child.second);
	}
	int totalSize = start->childSize + start->size;
	if (totalSize > spaceNeeded && totalSize < score)
		score = totalSize;
}