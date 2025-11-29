#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Node {
    int left, right;
    int count;
    Node *l_child, *r_child;

    Node(int l, int r) : left(l), right(r), count(0), l_child(nullptr), r_child(nullptr) {}
};

class PersistentSegmentTree {
private:
    vector<Node*> roots;
    vector<int> sorted_values;
    map<int, int> value_to_index;

    Node* build(int left, int right) {
        Node* node = new Node(left, right);
        if (left == right) {
            return node;
        }

        int mid = (left + right) >> 1;
        node->l_child = build(left, mid);
        node->r_child = build(mid + 1, right);
        return node;
    }

    Node* update(Node* prev, int pos, int delta) {
        int left = prev->left;
        int right = prev->right;
        Node* node = new Node(left, right);

        if (left == right) {
            node->count = prev->count + delta;
            return node;
        }

        int mid = (left + right) >> 1;
        if (pos <= mid) {
            node->l_child = update(prev->l_child, pos, delta);
            node->r_child = prev->r_child;
        }
        else {
            node->l_child = prev->l_child;
            node->r_child = update(prev->r_child, pos, delta);
        }

        node->count = node->l_child->count + node->r_child->count;
        return node;
    }

    int query(Node* node, int q_left, int q_right) {
        if (!node || q_right < node->left || q_left > node->right) {
            return 0;
        }

        if (q_left <= node->left && node->right <= q_right) {
            return node->count;
        }

        return query(node->l_child, q_left, q_right) +
            query(node->r_child, q_left, q_right);
    }

public:
    PersistentSegmentTree(const vector<int>& arr) {
        
        sorted_values = arr;
        sort(sorted_values.begin(), sorted_values.end());
        sorted_values.erase(unique(sorted_values.begin(), sorted_values.end()), sorted_values.end());

        for (int i = 0; i < sorted_values.size(); i++) {
            value_to_index[sorted_values[i]] = i;
        }

        roots.push_back(build(0, sorted_values.size() - 1));

        for (int i = 0; i < arr.size(); i++) {
            int pos = value_to_index[arr[i]];
            roots.push_back(update(roots.back(), pos, 1));
        }
    }

    int range_query(int l, int r, int x, int y) {
        
        auto it_x = lower_bound(sorted_values.begin(), sorted_values.end(), x);
        auto it_y = upper_bound(sorted_values.begin(), sorted_values.end(), y);

        if (it_x == sorted_values.end() || it_y == sorted_values.begin()) {
            return 0;
        }

        int idx_x = it_x - sorted_values.begin();
        int idx_y = it_y - sorted_values.begin() - 1;

        if (idx_x > idx_y) {
            return 0;
        }
        
        int total = query(roots[r + 1], idx_x, idx_y);
        int before = query(roots[l], idx_x, idx_y);

        return total - before;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    PersistentSegmentTree pst(arr);

    for (int i = 0; i < q; i++) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        cout << pst.range_query(l - 1, r - 1, x, y) << "\n";
    }

    return 0;
}