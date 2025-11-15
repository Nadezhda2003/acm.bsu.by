#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int n, m;
long long k;
vector<vector<long long>> a;

void dfs1(int i, int j, int steps, int max_steps, long long xor_val,
    vector<unordered_map<long long, int>>& cnt) {
    xor_val ^= a[i][j];
    if (steps == max_steps) {
        cnt[i * m + j][xor_val]++;
        return;
    }
    if (i + 1 < n) dfs1(i + 1, j, steps + 1, max_steps, xor_val, cnt);
    if (j + 1 < m) dfs1(i, j + 1, steps + 1, max_steps, xor_val, cnt);
}

long long dfs2(int i, int j, int steps, int max_steps, long long xor_val,
    vector<unordered_map<long long, int>>& cnt) {
    if (steps == max_steps) {
        long long need = k ^ xor_val;
        return cnt[i * m + j].count(need) ? cnt[i * m + j][need] : 0;
    }
    long long res = 0;
    if (i > 0) res += dfs2(i - 1, j, steps + 1, max_steps, xor_val ^ a[i][j], cnt);
    if (j > 0) res += dfs2(i, j - 1, steps + 1, max_steps, xor_val ^ a[i][j], cnt);
    return res;
}

int main() {
    cin >> n >> m >> k;
    a.resize(n, vector<long long>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    int total_steps = n + m - 2;
    int half1 = total_steps / 2;
    int half2 = total_steps - half1;

    vector<unordered_map<long long, int>> cnt(n * m);
    dfs1(0, 0, 0, half1, 0, cnt);

    long long result = dfs2(n - 1, m - 1, 0, half2, 0, cnt);
    cout << result << endl;

    return 0;
}