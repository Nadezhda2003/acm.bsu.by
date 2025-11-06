#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct SegmentTree {
    int n;
    vector<int> min_val;
    vector<int> lazy;

    SegmentTree(int size) {
        n = size;
        min_val.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(1, 0, n - 1);
    }

    void build(int node, int left, int right) {
        if (left == right) {
            min_val[node] = 0;
            return;
        }
        int mid = (left + right) >> 1;
        build((node << 1), left, mid);
        build((node << 1) + 1, mid + 1, right);
        min_val[node] = min(min_val[(node << 1)], min_val[(node << 1) + 1]);
    }

    void apply(int node, int val) {
        min_val[node] += val;
        lazy[node] += val;
    }

    void push(int node) {
        if (lazy[node] != 0) {
            apply((node << 1), lazy[node]);
            apply((node << 1) + 1, lazy[node]);
            lazy[node] = 0;
        }
    }

    void update_range(int node, int left, int right, int l, int r, int val) {
        if (l > right || r < left) return;
        if (l <= left && right <= r) {
            apply(node, val);
            return;
        }
        push(node);
        int mid = (left + right) >> 1;
        update_range((node << 1), left, mid, l, r, val);
        update_range((node << 1) + 1, mid + 1, right, l, r, val);
        min_val[node] = min(min_val[(node << 1)], min_val[(node << 1) + 1]);
    }

    int query_min(int node, int left, int right, int l, int r) {
        if (l > right || r < left) return 1e9;
        if (l <= left && right <= r) return min_val[node];
        push(node);
        int mid = (left + right) >> 1;
        return min(query_min((node << 1), left, mid, l, r),
            query_min((node << 1) + 1, mid + 1, right, l, r));
    }

    void range_add(int l, int r, int val) {
        update_range(1, 0, n - 1, l, r, val);
    }

    int range_min(int l, int r) {
        return query_min(1, 0, n - 1, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N, K, M;
    cin >> N >> K >> M;

    SegmentTree st(N - 1);
    st.range_add(0, N - 2, K);

    for (int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        int l = x, r = y - 1;
        int m = st.range_min(l, r);
        if (m > 0) {
            cout << "1\n";
            st.range_add(l, r, -1);
        }
        else {
            cout << "0\n";
        }
    }

    return 0;
}