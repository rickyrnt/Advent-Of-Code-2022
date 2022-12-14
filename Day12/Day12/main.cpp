#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


struct edge {
	struct node* nodeTo;
	struct edge* next;
};

struct node {
	unsigned int height, cost, totalCost;
	pair<int, int> coords;
	struct edge* head;
	struct node* parent;
};

bool cmp(const struct node* a, const struct node* b) {
	return a->totalCost > b->totalCost;
}

void addEdge(struct node& n, struct edge* e);
void resetCost(vector<vector<struct node>>& map);

int main() {
	ifstream input("input.txt");
	string line;
	vector<vector<struct node>> map;
	pair<int, int> end;
	vector<pair<int, int>> starts;
	unsigned int score = UINT_MAX;

	if (input.is_open()) {
		int row = 0;
		while (getline(input, line)) {
			vector<struct node> rowIns;
			for (int i = 0; i < line.length(); i++) {
				struct node toIns;
				toIns.coords = make_pair(i, row);
				//toIns.cost = toIns.totalCost = UINT_MAX;      job taken by resetCost()
				toIns.head = NULL;
				if (line[i] == 'S') {
					toIns.height = 0;
					starts.push_back(make_pair(i, row));
				} else if (line[i] == 'E') {
					toIns.height = 25;
					end = make_pair(i, row);
				} else if (line[i] == 'a') {
					toIns.height = 0;
					starts.push_back(make_pair(i, row));
				} else {
					toIns.height = line[i] - 97;
				}
				rowIns.push_back(toIns);
			}
			map.push_back(rowIns);
			row++;
		}

		for (int i = 0; i < map.size(); i++) {
			for (int j = 0; j < map[i].size(); j++) {
				int level = map[i][j].height;
				struct edge* toAdd;
				if (i > 0 && map[i - 1][j].height <= level + 1) {
					toAdd = new struct edge;
					toAdd->nodeTo = &map[i - 1][j];
					toAdd->next = NULL;
					addEdge(map[i][j], toAdd);
				}
				if (i < map.size() - 1 && map[i + 1][j].height <= level + 1) {
					toAdd = new struct edge;
					toAdd->nodeTo = &map[i + 1][j];
					toAdd->next = NULL;
					addEdge(map[i][j], toAdd);
				}
				if (j > 0 && map[i][j - 1].height <= level + 1) {
					toAdd = new struct edge;
					toAdd->nodeTo = &map[i][j - 1];
					toAdd->next = NULL;
					addEdge(map[i][j], toAdd);
				}
				if (j < map[i].size() - 1 && map[i][j + 1].height <= level + 1) {
					toAdd = new struct edge;
					toAdd->nodeTo = &map[i][j + 1];
					toAdd->next = NULL;
					addEdge(map[i][j], toAdd);
				}
			}
		}

		vector<struct node*> heap;
		for (int s = 0; s < starts.size(); s++) {
			resetCost(map);
			map[starts[s].second][starts[s].first].cost = map[starts[s].second][starts[s].first].totalCost = 0;
			cout << "Testing " << starts[s].first << ", " << starts[s].second << ". Best score: " << score << "\n";
			heap.clear();
			for (int i = 0; i < map.size(); i++) {
				for (int j = 0; j < map[i].size(); j++) {
					heap.push_back(&map[i][j]);
				}
			}
			//make_heap(heap.begin(), heap.end(), cmp);
			//cout << "i did it";
			while (map[end.second][end.first].totalCost == UINT_MAX) {
				make_heap(heap.begin(), heap.end(), cmp);
				/*for (int i = 0; i < 10; i++) {
					if (heap.size() == i)
						break;
					cout << heap[i]->totalCost << " ";
				}
				cout << "\n";*/
				struct node* currNode = heap[0];
				if (currNode->totalCost == UINT_MAX)
					break;
				heap[0] = heap.back();
				heap.pop_back();
				struct edge* curr = currNode->head;
				//a* with manhattan length heuristic
				while (curr != NULL) {
					if (curr->nodeTo->cost > currNode->cost + 1) {
						curr->nodeTo->cost = currNode->cost + 1;
						curr->nodeTo->totalCost = curr->nodeTo->cost + abs(end.first - curr->nodeTo->coords.first + end.second - curr->nodeTo->coords.second);
						//curr->nodeTo->totalCost = curr->nodeTo->cost;
						curr->nodeTo->parent = currNode;
					}
					curr = curr->next;
				}
			}

			if (map[end.second][end.first].cost < score)
				score = map[end.second][end.first].cost;
		}
		cout << score;

		/*for (int i = 0; i < heap.size(); i++) {
			cout << heap[i]->totalCost << " ";
		}*/

		/*for (int i = 0; i < map.size(); i++) {
			for (int j = 0; j < map[i].size(); j++) {
				cout << map[i][j].height << "  ";
			}
			cout << "\n";
		}*/
	} else { cout << "input not open! \n"; }
}

void addEdge(struct node& n, struct edge* e) {
	if (n.head == NULL) {
		n.head = e;
	} else {
		struct edge* curr = n.head;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = e;
	}
}

void resetCost(vector<vector<struct node>>& map) {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			map[i][j].cost = map[i][j].totalCost = UINT_MAX;
			map[i][j].parent = NULL;
		}
	}
}