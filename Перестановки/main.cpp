#include <iostream>
#include <vector>
using namespace std;
#pragma GCC target("avx")
#pragma GCC optimize("O3")

const int N = 200005;

int n;
int c[N];
int seg[4 * N];

void build(int idx, int l, int r) {
    if (l == r) {
        seg[idx] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(idx << 1, l, mid);
    build(idx << 1 | 1, mid + 1, r);
    seg[idx] = seg[idx << 1] + seg[idx << 1 | 1];
}

int find_kth(int idx, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (seg[idx << 1] >= k) {
        return find_kth(idx << 1, l, mid, k);
    }
    else {
        return find_kth(idx << 1 | 1, mid + 1, r, k - seg[idx << 1]);
    }
}

void remove(int idx, int l, int r, int pos) {
    if (l == r) {
        seg[idx] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        remove(idx << 1, l, mid, pos);
    }
    else {
        remove(idx << 1 | 1, mid + 1, r, pos);
    }
    seg[idx] = seg[idx << 1] + seg[idx << 1 | 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    build(1, 1, n);

    vector<int> p(n + 1);
    for (int i = n; i >= 1; i--) {
        int k = i - c[i];
        int num = find_kth(1, 1, n, k);
        p[i] = num;
        remove(1, 1, n, num);
    }

    for (int i = 1; i <= n; i++) {
        cout << p[i] << " ";
    }
    cout << "\n";

    return 0;
}