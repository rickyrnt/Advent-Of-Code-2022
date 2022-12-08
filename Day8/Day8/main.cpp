#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	ifstream input("input.txt");
	string line;
	vector<vector<uint8_t>> trees;
	int score = 4;

	if (input.is_open()) {
		//construct array
		while (getline(input, line)) {
			vector<uint8_t>* row = new vector<uint8_t>;
			for (char ins : line){
				row->push_back(ins - 48);
			}trees.push_back(*row);
		}

		int left, right, up, down;
		for (int i = 1; i < trees.size() - 1; i++) {
			for (int j = 1; j < trees.size() - 1; j++) {
				//left
				left = 0;
				for (int k = j - 1; k >= 0; k--) {
					left++;

					if (trees[i][k] >= trees[i][j])
						break;
				}
				//right
				right = 0;
				for (int k = j + 1; k < trees.size(); k++) {
					right++;

					if (trees[i][k] >= trees[i][j])
						break;
				}
				//up
				up = 0;
				for (int k = i - 1; k >= 0; k--) {
					up++;

					if (trees[k][j] >= trees[i][j])
						break;
				}
				//down
				down = 0;
				for (int k = i + 1; k < trees.size(); k++) {
					down++;

					if (trees[k][j] >= trees[i][j])
						break;
				}

				int candidate = left * right * up * down;

				//cout << "at i:" << i << " j:" << j << "  left: " << left << "  right: " << right << "  up: " << up << "  down: " << down << "\n";
				if (candidate > score)
					score = candidate;
			}
		}
		cout << score;

		/* part 1
		//left to right
		uint8_t tallest;
		for (int i = 1; i < trees.size() - 1; i++) {
			tallest = trees[i][0] & 0b00001111;
			score++;
			for (int j = 1; j < trees.size() - 1; j++) {
				if (trees[i][j] > tallest && !(trees[i][j] / 0b10000000)) {
					trees[i][j] |= 0b10000000;
					score++;
				} 
				if ((trees[i][j] & 0b00001111) > tallest) {
					tallest = trees[i][j] & 0b00001111;
				}
				if (tallest == 9)
					break;
			}
		}

		//right to left

		for (int i = 1; i < trees.size() - 1; i++) {
			tallest = trees[i][trees.size() - 1] & 0b00001111;
			score++;
			for (int j = trees.size() - 2; j > 0; j--) {
				if (trees[i][j] > tallest && !(trees[i][j] / 0b10000000)) {
					trees[i][j] |= 0b10000000;
					score++;
				}
				if ((trees[i][j] & 0b00001111) > tallest) {
					tallest = trees[i][j] & 0b00001111;
				}
				if (tallest == 9)
					break;
			}
		}

		//top to bottom

		for (int j = 1; j < trees.size() - 1; j++) {
			tallest = trees[0][j] & 0b00001111;
			score++;
			for (int i = 1; i < trees.size() - 1; i++) {
				if (trees[i][j] > tallest && !(trees[i][j] / 0b10000000)) {
					trees[i][j] |= 0b10000000;
					score++;
				}
				if ((trees[i][j] & 0b00001111) > tallest) {
					tallest = trees[i][j] & 0b00001111;
				}
				if (tallest == 9)
					break;
			}
		}

		//bottom to top

		for (int j = 1; j < trees.size() - 1; j++) {
			tallest = trees[trees.size() - 1][j] & 0b00001111;
			score++;
			for (int i = trees.size() - 2; i > 0; i--) {
				if (trees[i][j] > tallest && !(trees[i][j] / 0b10000000)) {
					trees[i][j] |= 0b10000000;
					score++;
				}
				if ((trees[i][j] & 0b00001111) > tallest) {
					tallest = trees[i][j] & 0b00001111;
				}
				if (tallest == 9)
					break;
			}
		}

		cout << score;*/
		
	} else { cout << "input not open! \n"; }
}