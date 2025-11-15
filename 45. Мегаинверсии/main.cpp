#include <iostream>
#include <vector>
using namespace std;

struct Tree {
    int n;
    vector<long long> bit;

    Tree(int n_) : n(n_), bit(n_ + 1, 0) {}

    void update(int idx, int delta) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += delta;
    }

    long long query(int idx) {
        long long res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }

    long long range_sum(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    Tree bit_left(n);
    vector<long long> left_count(n + 1, 0);
    for (int j = 1; j <= n; j++) {
        left_count[j] = bit_left.range_sum(p[j] + 1, n);
        bit_left.update(p[j], 1);
    }

    Tree bit_right(n);
    vector<long long> right_count(n + 1, 0);
    for (int j = n; j >= 1; j--) {
        right_count[j] = bit_right.query(p[j] - 1);
        bit_right.update(p[j], 1);
    }

    long long ans = 0;
    for (int j = 1; j <= n; j++) {
        ans += left_count[j] * right_count[j];
    }

    cout << ans << "\n";

    return 0;
}