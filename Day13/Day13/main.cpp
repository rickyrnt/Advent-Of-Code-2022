#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void insertElem(string line, struct packet& packet);
int comparePackets(struct packet left, struct packet right);
void wipePacket(struct packet& pack);
bool cmp(struct packet* left, struct packet* right);
string debugPacket(struct packet& pack);

struct packet {
	vector<pair<struct packet*, int>> data;
};

int main() {
	ifstream input("input.txt");
	string line;
	int score = 0;
	int index = 0;
	struct packet* toIns;
	struct packet* div1;
	struct packet* div2;
	vector<struct packet*> packettes;

	if (input.is_open()) {
		while (getline(input, line)) {
			index++;

			toIns = new struct packet;
			insertElem(line.substr(1, line.length() - 2), *toIns);
			packettes.push_back(toIns);
			getline(input, line);
			toIns = new struct packet;
			insertElem(line.substr(1, line.length() - 2), *toIns);
			packettes.push_back(toIns);

			/*insertElem(line.substr(1, line.length() - 2), left);
			packettes.push_back(left);
			getline(input, line);
			insertElem(line.substr(1, line.length() - 2), right);
			packettes.push_back(right);

			int test = comparePackets(left, right);

			wipePacket(left);
			wipePacket(right);*/
			getline(input, line);
		}
		div1 = new struct packet;
		insertElem("[2]", *div1);
		packettes.push_back(div1);
		div2 = new struct packet;
		insertElem("[6]", *div2);
		packettes.push_back(div2);

		sort(packettes.begin(), packettes.end(), cmp);
		for (int i = 0; i < packettes.size(); i++) {
			if (packettes[i] == div1) {
				cout << "div1: ";
				score = i + 1;
			}
			if (packettes[i] == div2) {
				cout << "div2: ";
				score *= i + 1;
			}
			cout << debugPacket(*packettes[i]) << "\n";
		}
		cout << score;
	} else { cout << "input not open! \n"; }
}

void insertElem(string line, struct packet& packets){
	int i = 0;
	while (i < line.length()) {
		if (line[i] == '[') {
			struct packet* toIns = new struct packet;
			int j = 1;
			int k = i;
			while (j > 0) {
				k++;
				if (line[k] == '[')
					j++;
				else if (line[k] == ']')
					j--;
			}
			insertElem(line.substr(i + 1, k - i - 1), *toIns);
			packets.data.push_back(make_pair(toIns, -1));
			i = k + 2;
		} else {
			if (line.find(',', i) == -1) {
				packets.data.push_back(make_pair(nullptr, stoi(line.substr(i, line.length()))));
				i = line.length();
			} else {
				packets.data.push_back(make_pair(nullptr, stoi(line.substr(i, line.find(',', i)))));
				i = line.find(',', i) + 1;
			}
		}
	}
}

bool cmp(struct packet* left, struct packet* right) {
	if (comparePackets(*left, *right) == 1)
		return true;
	else return false;
}

int comparePackets(struct packet left, struct packet right) {
	if (left.data.size() == 0) {
		if (right.data.size() != 0)
			return true;
		else return -1;
	}
	for (int i = 0; i < left.data.size(); i++) {
		if (i >= right.data.size())
			return false;
		if (left.data[i].first == nullptr && right.data[i].first == nullptr) {
			if (left.data[i].second < right.data[i].second)
				return true;
			else if (left.data[i].second > right.data[i].second)
				return false;
		} else {
			if (left.data[i].first == nullptr) {
				struct packet* temp = new struct packet;
				temp->data.push_back(make_pair(nullptr, left.data[i].second));
				left.data[i] = make_pair(temp, -1);
			} else if (right.data[i].first == nullptr) {
				struct packet* temp = new struct packet;
				temp->data.push_back(make_pair(nullptr, right.data[i].second));
				right.data[i] = make_pair(temp, -1);
			}

			int result = comparePackets(*left.data[i].first, *right.data[i].first);
			if(result != -1){
				return result;
			}
		}
		if (i == left.data.size() - 1 && i != right.data.size() - 1)
			return true;
	}

	return -1;
}

void wipePacket(struct packet& pack) {
	for (pair<struct packet*, int> data : pack.data) {
		if (data.first != nullptr) {
			wipePacket(*data.first);
			delete data.first;
		}
		pack.data.clear();
	}
}

string debugPacket(struct packet& pack) {
	stringstream out;
	out << "[";
	for (int i = 0; i < pack.data.size(); i++) {
		if (pack.data[i].first == nullptr) {
			out << pack.data[i].second;
		} else {
			out << debugPacket(*pack.data[i].first);
		}

		if (i != pack.data.size() - 1)
			out << ",";
	}
	out << "]";
	return out.str();
}