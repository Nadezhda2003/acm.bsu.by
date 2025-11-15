#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

map<int, vector<long long>> generate(const vector<long long>& arr) {
    int n = arr.size();
    map<int, vector<long long>> result;
    for (int mask = 0; mask < (1 << n); mask++) {
        int cnt = 0;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                cnt++;
                sum += arr[i];
            }
        }
        result[cnt].push_back(sum);
    }
    return result;
}

int main() {
    int N;
    cin >> N;
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    long long L, R;
    cin >> L >> R;

    int n1 = N / 2;
    int n2 = N - n1;

    vector<long long> left_arr(A.begin(), A.begin() + n1);
    vector<long long> right_arr(A.begin() + n1, A.end());

    auto left_subsets = generate(left_arr);
    auto right_subsets = generate(right_arr);

    for (auto& p : right_subsets) {
        sort(p.second.begin(), p.second.end());
    }

    long long ans = 0;

    for (const auto& p1 : left_subsets) {
        int k1 = p1.first;
        const vector<long long>& sums1 = p1.second;
        for (long long sum1 : sums1) {
            for (const auto& p2 : right_subsets) {
                int k2 = p2.first;
                const vector<long long>& sums2 = p2.second;
                int k = k1 + k2;
                if (k == 0) continue;

                long long low_bound = L * k - sum1;
                long long up_bound = R * k - sum1;

                auto it_low = lower_bound(sums2.begin(), sums2.end(), low_bound);
                auto it_up = upper_bound(sums2.begin(), sums2.end(), up_bound);
                ans += (it_up - it_low);
            }
        }
    }

    cout << ans << "\n";

    return 0;
}