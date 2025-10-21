#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class SegmentTree {
private:
    vector<long long> tree_sum, tree_min, tree_max, lazy;
    int n;

    void apply(int node, int start, int end, long long value) {
        tree_sum[node] += value * (end - start + 1);
        tree_min[node] += value;
        tree_max[node] += value;
        if (start != end) {
            lazy[node] += value;
        }
    }

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            int mid = (start + end) / 2;
            apply(node * 2, start, mid, lazy[node]);
            apply(node * 2 + 1, mid + 1, end, lazy[node]);
            lazy[node] = 0;
        }
    }

    void update(int idx, long long value, int node, int start, int end) {
        if (start == end) {
            tree_sum[node] = value;
            tree_min[node] = value;
            tree_max[node] = value;
        }
        else {
            push(node, start, end);
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(idx, value, node * 2, start, mid);
            }
            else {
                update(idx, value, node * 2 + 1, mid + 1, end);
            }
            tree_sum[node] = tree_sum[node * 2] + tree_sum[node * 2 + 1];
            tree_min[node] = min(tree_min[node * 2], tree_min[node * 2 + 1]);
            tree_max[node] = max(tree_max[node * 2], tree_max[node * 2 + 1]);
        }
    }

    void range_add(int L, int R, long long value, int node, int start, int end) {
        if (R < start || end < L) {
            return;
        }
        if (L <= start && end <= R) {
            apply(node, start, end, value);
        }
        else {
            push(node, start, end);
            int mid = (start + end) / 2;
            range_add(L, R, value, node * 2, start, mid);
            range_add(L, R, value, node * 2 + 1, mid + 1, end);
            tree_sum[node] = tree_sum[node * 2] + tree_sum[node * 2 + 1];
            tree_min[node] = min(tree_min[node * 2], tree_min[node * 2 + 1]);
            tree_max[node] = max(tree_max[node * 2], tree_max[node * 2 + 1]);
        }
    }

    long long query_sum(int L, int R, int node, int start, int end) {
        if (R < start || end < L) {
            return 0;
        }
        if (L <= start && end <= R) {
            return tree_sum[node];
        }
        push(node, start, end);
        int mid = (start + end) / 2;
        return query_sum(L, R, node * 2, start, mid) + query_sum(L, R, node * 2 + 1, mid + 1, end);
    }

    long long query_min(int L, int R, int node, int start, int end) {
        if (R < start || end < L) {
            return LLONG_MAX;
        }
        if (L <= start && end <= R) {
            return tree_min[node];
        }
        push(node, start, end);
        int mid = (start + end) / 2;
        return min(query_min(L, R, node * 2, start, mid), query_min(L, R, node * 2 + 1, mid + 1, end));
    }

    long long query_max(int L, int R, int node, int start, int end) {
        if (R < start || end < L) {
            return LLONG_MIN;
        }
        if (L <= start && end <= R) {
            return tree_max[node];
        }
        push(node, start, end);
        int mid = (start + end) / 2;
        return max(query_max(L, R, node * 2, start, mid), query_max(L, R, node * 2 + 1, mid + 1, end));
    }

public:
    SegmentTree(int size) {
        n = size;
        tree_sum.resize(4 * n);
        tree_min.resize(4 * n, LLONG_MAX);
        tree_max.resize(4 * n, LLONG_MIN);
        lazy.resize(4 * n);
    }

    void update(int idx, long long value) {
        update(idx, value, 1, 0, n - 1);
    }

    void range_add(int L, int R, long long value) {
        range_add(L, R, value, 1, 0, n - 1);
    }

    long long query_sum(int L, int R) {
        return query_sum(L, R, 1, 0, n - 1);
    }

    long long query_min(int L, int R) {
        return query_min(L, R, 1, 0, n - 1);
    }

    long long query_max(int L, int R) {
        return query_max(L, R, 1, 0, n - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    SegmentTree seg_tree(n);
    vector<long long> results;

    while (true) {
        int type;
        cin >> type;
        if (type == 0) {
            break;
        }
        if (type == 1) {
            int i;
            long long v;
            cin >> i >> v;
            seg_tree.update(i, v);
        }
        else if (type == 2) {
            int a, b;
            long long v;
            cin >> a >> b >> v;
            seg_tree.range_add(a, b, v);
        }
        else if (type == 3) {
            int a, b;
            cin >> a >> b;
            results.push_back(seg_tree.query_sum(a, b));
        }
        else if (type == 4) {
            int a, b;
            cin >> a >> b;
            results.push_back(seg_tree.query_min(a, b));
        }
        else if (type == 5) {
            int a, b;
            cin >> a >> b;
            results.push_back(seg_tree.query_max(a, b));
        }
    }

    for (long long res : results) {
        cout << res << "\n";
    }

    return 0;
}