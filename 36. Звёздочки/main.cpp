#include <fstream>
#include <vector>
#pragma GCC target("avx")
#pragma GCC optimize("O3")
using namespace std;

int count_prev_stars(vector<int> counter_x, int prev_star, int curr_star) {
	int count = 0;
	for (int i = prev_star + 1; i <= curr_star; i++)
		count += counter_x[i];
	return count;
}
int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");

	int n;
	input >> n;
	vector<int> levels_stars(n);
	vector<int> y_coord_stars(n);
	vector<int> x_coord_stars(n);
	vector<int> levels_output(n);

	int x_max = 0;

	int x_star = 0, y_star = 0;

	for (int i = 0; i < n; i++)
	{
		input >> x_star >> y_star;
		x_coord_stars[i] = x_star;
		y_coord_stars[i] = y_star;

		x_max = max(x_max, x_coord_stars[i] + 1);
		levels_stars[i] = 0;
		levels_output[i] = 0;
	}

	vector<int> counter_x(x_max);
	counter_x[x_coord_stars[0]]++;

	int y_prev_pos = 0;
	levels_output[0]++;

	for (int i = 1; i < n; i++) {
		if (y_coord_stars[i - 1] == y_coord_stars[i])
		{
			levels_stars[i] += levels_stars[i - 1];
			levels_stars[i] += count_prev_stars(counter_x, x_coord_stars[i - 1], x_coord_stars[i]);
			levels_stars[i]++;
		}
		else {
			levels_stars[i] += levels_stars[y_prev_pos] + 1;
			if (x_coord_stars[i] > x_coord_stars[y_prev_pos]) {
				levels_stars[i] += count_prev_stars(counter_x, x_coord_stars[y_prev_pos], x_coord_stars[i]);
			}
			else if (x_coord_stars[i] < x_coord_stars[y_prev_pos])
				levels_stars[i] -= count_prev_stars(counter_x, x_coord_stars[i], x_coord_stars[y_prev_pos]);
			y_prev_pos = i;
		}
		counter_x[x_coord_stars[i]]++;
		levels_output[levels_stars[i]]++;
	}

	for (int i = 0; i < n; i++)
	{
		output << levels_output[i] << '\n';
	}
	return 0;
}