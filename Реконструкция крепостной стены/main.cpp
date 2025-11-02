#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int max_n = 300005;
long long a[max_n], prefix[max_n];
vector<long long> values[max_n * 4];
vector<long long> prefix_sums[max_n * 4];

void build(int node, int l, int r)
{
    if (l == r)
    {
        values[node] = { a[l] };
        prefix_sums[node] = { a[l] };
        return;
    }
    int mid = (l + r) >> 1;
    build((node << 1), l, mid);
    build((node << 1) + 1, mid + 1, r);

    values[node].resize(values[(node << 1)].size() + values[(node << 1) + 1].size());
    merge(values[(node << 1)].begin(), values[(node << 1)].end(),
        values[(node << 1) + 1].begin(), values[(node << 1) + 1].end(),
        values[node].begin());

    prefix_sums[node].resize(values[node].size());
    prefix_sums[node][0] = values[node][0];
    for (size_t i = 1; i < values[node].size(); i++)
    {
        prefix_sums[node][i] = prefix_sums[node][i - 1] + values[node][i];
    }
}

pair<long long, int> query(int node, int l, int r, int ql, int qr, long long h)
{
    if (qr < l || ql > r)
        return make_pair(0, 0);

    if (ql <= l && r <= qr)
    {
        int pos = lower_bound(values[node].begin(), values[node].end(), h) - values[node].begin();
        if (pos == 0)
            return make_pair(0, 0);
        return make_pair(prefix_sums[node][pos - 1], pos);
    }

    int mid = (l + r) >> 1;
    auto left_res = query((node << 1), l, mid, ql, qr, h);
    auto right_res = query((node << 1) + 1, mid + 1, r, ql, qr, h);

    return make_pair(left_res.first + right_res.first, left_res.second + right_res.second);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        prefix[i] = prefix[i - 1] + a[i];
    }

    build(1, 1, n);

    while (q--)
    {
        int l, r;
        long long h;
        cin >> l >> r >> h;

        long long total_sum = prefix[r] - prefix[l - 1];
        int total_count = r - l + 1;

        auto res = query(1, 1, n, l, r, h);
        long long sum_lt = res.first;
        int cnt_lt = res.second;

        long long cost = (h * cnt_lt - sum_lt) + (total_sum - sum_lt - h * (total_count - cnt_lt));
        cout << cost << '\n';
    }

    return 0;
}