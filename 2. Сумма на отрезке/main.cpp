#include <iostream>
#include <vector>
#pragma GCC target("avx")
#pragma GCC optimize("O3")
using namespace std;

struct Node {
    long long se, so;
    long long ce, co;
    long long add;
};

struct SegTree {
    long long n;
    vector<Node> tree;

    void init(long long size) {
        n = 1;
        while (n < size) {
            n *= 2;
        }
        tree.assign(2 * n - 1, Node{ 0, 0, 0, 0, 0 });
    }

    void build(vector<long long>& data, long long node, long long start, long long end) {
        if (end - start == 1) {
            if (start < data.size()) {
                if (data[start] % 2 == 0) {
                    tree[node].se = data[start];
                    tree[node].ce = 1;
                }
                else {
                    tree[node].so = data[start];
                    tree[node].co = 1;
                }
            }
        }
        else {
            long long mid = (start + end) >> 1;
            build(data, (node << 1) + 1, start, mid);
            build(data, (node << 1) + 2, mid, end);
            tree[node].se = tree[(node << 1) + 1].se + tree[(node << 1) + 2].se;
            tree[node].ce = tree[(node << 1) + 1].ce + tree[(node << 1) + 2].ce;
            tree[node].so = tree[(node << 1) + 1].so + tree[(node << 1) + 2].so;
            tree[node].co = tree[(node << 1) + 1].co + tree[(node << 1) + 2].co;
        }
    }

    void apply(long long node, long long start, long long end) {
        if (tree[node].add == 0 || end - start <= 1)
            return;
        else
        {
            long long mid = (start + end) >> 1;
            tree[(node << 1) + 1].add += tree[node].add;
            tree[(node << 1) + 2].add += tree[node].add;
            if (tree[node].add % 2 == 0)
            {
                tree[(node << 1) + 1].se += tree[node].add * tree[(node << 1) + 1].ce;
                tree[(node << 1) + 1].so += tree[node].add * tree[(node << 1) + 1].co;
                tree[(node << 1) + 2].se += tree[node].add * tree[(node << 1) + 2].ce;
                tree[(node << 1) + 2].so += tree[node].add * tree[(node << 1) + 2].co;
            }
            else
            {
                long long num1 = tree[(node << 1) + 1].se + tree[node].add * tree[(node << 1) + 1].ce;
                long long num2 = tree[(node << 1) + 1].so + tree[node].add * tree[(node << 1) + 1].co;
                long long col1 = tree[(node << 1) + 1].ce;
                long long col2 = tree[(node << 1) + 1].co;
                tree[(node << 1) + 1].so = num1;
                tree[(node << 1) + 1].se = num2;
                tree[(node << 1) + 1].co = col1;
                tree[(node << 1) + 1].ce = col2;

                num1 = tree[(node << 1) + 2].se + tree[node].add * tree[(node << 1) + 2].ce;
                num2 = tree[(node << 1) + 2].so + tree[node].add * tree[(node << 1) + 2].co;
                col1 = tree[(node << 1) + 2].ce;
                col2 = tree[(node << 1) + 2].co;
                tree[(node << 1) + 2].so = num1;
                tree[(node << 1) + 2].se = num2;
                tree[(node << 1) + 2].co = col1;
                tree[(node << 1) + 2].ce = col2;
            }
            tree[node].add = 0;
        }
    }
    void update_add(long long l, long long r, long long node, long long start, long long end) {
        apply(node, start, end);
        if (l >= end || r <= start) {
            return;
        }
        if (start >= l && end <= r) {
            tree[node].add = 1;

            long long num = tree[node].se + tree[node].ce;
            long long col = tree[node].ce;
            tree[node].se = tree[node].so + tree[node].co;
            tree[node].so = num;
            tree[node].ce = tree[node].co;
            tree[node].co = col;
            return;
        }
        long long mid = (start + end) >> 1;
        update_add(l, r, (node << 1) + 1, start, mid);
        update_add(l, r, (node << 1) + 2, mid, end);
        tree[node].se = tree[(node << 1) + 1].se + tree[(node << 1) + 2].se;
        tree[node].so = tree[(node << 1) + 1].so + tree[(node << 1) + 2].so;
        tree[node].ce = tree[(node << 1) + 1].ce + tree[(node << 1) + 2].ce;
        tree[node].co = tree[(node << 1) + 1].co + tree[(node << 1) + 2].co;
    }

    void update_set(long long index, long long value, long long node, long long start, long long end) {
        apply(node, start, end);
        if (end - start == 1) {
            if (value % 2 == 0) {
                tree[node].se = value;
                tree[node].ce = 1;
                tree[node].so = 0;
                tree[node].co = 0;
            }
            else {
                tree[node].so = value;
                tree[node].co = 1;
                tree[node].se = 0;
                tree[node].ce = 0;
            }
        }
        else {
            long long mid = (start + end) >> 1;
            if (index < mid) {
                update_set(index, value, (node << 1) + 1, start, mid);
            }
            else {
                update_set(index, value, (node << 1) + 2, mid, end);
            }
            tree[node].se = tree[(node << 1) + 1].se + tree[(node << 1) + 2].se;
            tree[node].so = tree[(node << 1) + 1].so + tree[(node << 1) + 2].so;
            tree[node].ce = tree[(node << 1) + 1].ce + tree[(node << 1) + 2].ce;
            tree[node].co = tree[(node << 1) + 1].co + tree[(node << 1) + 2].co;
        }
    }

    long long query_sum_even(long long l, long long r, long long node, long long start, long long end) {
        apply(node, start, end);
        if (l >= end || r <= start) {
            return 0;
        }
        if (start >= l && end <= r) {
            return tree[node].se;
        }
        long long mid = (start + end) >> 1;
        return query_sum_even(l, r, (node << 1) + 1, start, mid) + query_sum_even(l, r, (node << 1) + 2, mid, end);
    }

    long long query_sum_odd(long long l, long long r, long long node, long long start, long long end) {
        apply(node, start, end);
        if (l >= end || r <= start) {
            return 0;
        }
        if (start >= l && end <= r) {
            return tree[node].so;
        }
        long long mid = (start + end) >> 1;
        return query_sum_odd(l, r, (node << 1) + 1, start, mid) + query_sum_odd(l, r, (node << 1) + 2, mid, end);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (long long i = 0; i < n; i++) {
        cin >> a[i];
    }

    SegTree tree;
    tree.init(n);
    tree.build(a, 0, 0, n);

    while (q--) {
        long long t;
        cin >> t;
        if (t == 1) {
            long long p, v;
            cin >> p >> v;
            tree.update_set(p - 1, v, 0, 0, n);
        }
        else if (t == 2) {
            long long l, r;
            cin >> l >> r;
            tree.update_add(l - 1, r, 0, 0, n);
        }
        else if (t == 3) {
            long long l, r;
            cin >> l >> r;
            cout << tree.query_sum_even(l - 1, r, 0, 0, n) << "\n";
        }
        else if (t == 4) {
            long long l, r;
            cin >> l >> r;
            cout << tree.query_sum_odd(l - 1, r, 0, 0, n) << "\n";
        }
    }

    return 0;
}