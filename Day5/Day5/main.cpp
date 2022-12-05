#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

void flipStack(stack<char>& st);

int main() {
	ifstream input("input.txt");
	string line;
	vector<stack<char>> stacks;
	int numStacks, toMove, src, tgt, fromI, toI;

	if (input.is_open()) {
		getline(input, line);
		numStacks = ((line.length() + 1) / 4);
		for (int i = 0; i < numStacks; i++) {
			stack<char>* ins = new stack<char>();
			stacks.push_back(*ins);
		}
		while (line[1] != '1') {
			for (int i = 0; i < numStacks; i++) {
				if (line[(i * 4) + 1] != ' ') {
					stacks[i].push(line[(i * 4) + 1]);
				}
			}
			getline(input, line);
		}
		getline(input, line);
		for (int i = 0; i < numStacks; i++) {
			flipStack(stacks[i]);
		}

		stack<char>* temp = new stack<char>();
		while (getline(input, line)) {
			fromI = line.find(" from");
			toI = line.find(" to");
			toMove = stoi(line.substr(5, fromI));
			src = stoi(line.substr(fromI + 6, toI)) - 1;
			tgt = stoi(line.substr(toI + 4, line.length())) - 1;
			
			for (int i = 0; i < toMove; i++) {
				temp->push(stacks[src].top());
				stacks[src].pop();
			}
			for (int i = 0; i < toMove; i++) {
				stacks[tgt].push(temp->top());
				temp->pop();
			}
		}

		for (int i = 0; i < numStacks; i++) {
			cout << stacks[i].top();
		}
	} else { cout << "input not open! \n"; }
}

void flipStack(stack<char>& st) {
	stack<char>* temp = new stack<char>();
	int size = st.size();
	for (int i = 0; i < size; i++) {
		temp->push(st.top());
		st.pop();
	}
	temp->swap(st);
}