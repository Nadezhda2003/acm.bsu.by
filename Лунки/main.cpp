#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    vector<int> a(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }

    int B = sqrt(N);
    vector<int> next_pos(N + 1), steps(N + 1), last_hole(N + 1);

    for (int i = N; i >= 1; i--) {
        int to = i + a[i];
        if (to > N) {
            next_pos[i] = -1;
            steps[i] = 1;
            last_hole[i] = i;
        }
        else if (to / B != i / B) {
            next_pos[i] = to;
            steps[i] = 1;
            last_hole[i] = i;
        }
        else {
            next_pos[i] = next_pos[to];
            steps[i] = steps[to] + 1;
            last_hole[i] = last_hole[to];
        }
    }

    while (M--) {
        int type;
        cin >> type;
        if (type == 0) {
            int pos, val;
            cin >> pos >> val;
            a[pos] = val;
            int block = pos / B;
            int start = block * B;
            int end = min(N, start + B - 1);
            for (int i = end; i >= start; i--) {
                int to = i + a[i];
                if (to > N) {
                    next_pos[i] = -1;
                    steps[i] = 1;
                    last_hole[i] = i;
                }
                else if (to / B != i / B) {
                    next_pos[i] = to;
                    steps[i] = 1;
                    last_hole[i] = i;
                }
                else {
                    next_pos[i] = next_pos[to];
                    steps[i] = steps[to] + 1;
                    last_hole[i] = last_hole[to];
                }
            }
        }
        else {
            int start;
            cin >> start;
            int total_steps = 0;
            int last = start;
            while (start != -1) {
                total_steps += steps[start];
                last = last_hole[start];
                start = next_pos[start];
            }
            cout << last << " " << total_steps << "\n";
        }
    }

    return 0;
}