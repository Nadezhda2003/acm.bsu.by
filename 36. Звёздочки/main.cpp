#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#pragma GCC target("avx")
#pragma GCC optimize("O3")
using namespace std;

const int LEAF = 524287; // 2^19 - 1
const int SIZE = 1048575; // 2^20
int Tree[SIZE];

void modify(int x)
{
	int i = LEAF + x;
	while (i >= 0)
	{
		Tree[i]++;
		i = ((i + 1) >> 1) - 1;
	}
}

int Sum_counter(int index, int curr_l, int curr_r, int l, int r)
{
	if (l >= curr_r || r <= curr_l)
		return 0;
	if (l <= curr_l && r >= curr_r)
		return Tree[index];
	int k = (curr_l + curr_r) >> 1;
	return Sum_counter((index << 1) + 1, curr_l, k, l, r) + Sum_counter((index << 1) + 2, k, curr_r, l, r);
}

int sum(int l, int r)
{
	return Sum_counter(0, 0, LEAF + 1, l, r);
}
int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");

	int n;
	input >> n;
	vector <int> levels(n);
	levels[0] = 1;
	int startX, startY;
	input >> startX >> startY;
	int currentY = startY, minBound = startX + 1, currentLevel = 1;
	modify(startX);

	for (int j = 1; j < n; j++) {
		input >> startX >> startY;

		if (startY != currentY) {
			currentY = startY;
			minBound = 0;
			currentLevel = 0;
		}

		currentLevel += sum(minBound, startX + 1);
		minBound = startX + 1;
		levels[currentLevel++]++;
		modify(startX);
	}

	for (int j = 0; j < n; j++) {
		output << levels[j] << '\n';
	}
	return 0;
}