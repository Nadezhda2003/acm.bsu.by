#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair <long long, long long>> clients(300006);
const long long n = 1000006;

struct Node {
    long long left = 0, right = 0;
    long long sum_d = 0;
    long long end_time = 0;

    void init_node(long long pos, long long time)
    {
        left = pos;
        right = pos + 1;
        end_time = left + time;
        sum_d = time;
    }
};


struct Data {
    Node combine(Node left, Node right) {
        Node res;
        res.left = left.left;
        res.right = right.right;
        res.sum_d = left.sum_d + right.sum_d;

        long long check_l = left.end_time - left.right;
        long long check_r = right.end_time - right.left - right.sum_d;
        if (check_l < 0 || check_r >= check_l) {
            res.end_time = right.end_time;
        }
        else {
            res.end_time = right.end_time + check_l - check_r;
        }

        return res;
    }

    const long long size = 4194304;
    vector <Node> tree;

    void init()
    {
        tree.resize(size);
    }

    void build(long long idx, long long l, long long r) {
        long long mid = (l + r) >> 1;
        if (l == mid) {
            tree[idx].init_node(l, 0);
        }
        else {
            build(idx * 2 + 1, l, mid);
            build(idx * 2 + 2, mid, r);
            tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
        }
    }

    void update(long long idx, long long l, long long r, long long pos, long long t) {
        long long mid = (l + r) >> 1;
        if (l == mid) {
            tree[idx].init_node(pos, t);
        }
        else
        {
            if (pos < mid) {
                update(idx * 2 + 1, l, mid, pos, t);
            }
            else {
                update(idx * 2 + 2, mid, r, pos, t);
            }

            tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
        }
    }

    Node query(long long idx, long long l, long long r, long long ql, long long qr) {
        if (ql <= l && r <= qr) {
            return tree[idx];
        }
        else
        {
            long long mid = (l + r) >> 1;

            if (qr <= mid) {
                return query(idx * 2 + 1, l, mid, ql, qr);
            }
            else if (ql > mid) {
                return query(idx * 2 + 2, mid, r, ql, qr);
            }
            else 
            {
                Node left_res, right_res;
                left_res = query(idx * 2 + 1, l, mid, ql, qr);
                right_res = query(idx * 2 + 2, mid, r, ql, qr);
                return combine(left_res, right_res);
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long q;
    cin >> q;

    Data tree;
    tree.init();
    tree.build(1, 0, n);

    for (long long i = 0; i < q; i++) {
        char type;
        cin >> type;

        if (type == '+') {
            int t, d;
            cin >> t >> d;
            clients[i] = { t, d };
            tree.update(1, 0, n, t, d);
        }
        else if (type == '-') {
            int idx;
            cin >> idx;
            clients[i] = { 0, 0 };
            long long p = clients[idx - 1].first;
            tree.update(1, 0, n, p, 0);
        }
        else if (type == '?') {
            int t_query;
            cin >> t_query;
            clients[i] = { 0, 0 };
            Node res = tree.query(1, 0, n, 0, t_query + 1);
            cout << res.end_time - t_query << '\n';
        }
    }

    return 0;
}