#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    int n;
    long long m;
    cin >> n >> m;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] %= m;
    }

    int n1 = n / 2;
    int n2 = n - n1;

    set<long long> sums1;
    sums1.insert(0);

    for (int i = 0; i < n1; i++) {
        set<long long> new_sums;
        for (long long sum : sums1) {
            long long new_sum = (sum + a[i]) % m;
            new_sums.insert(new_sum);
        }
        sums1.insert(new_sums.begin(), new_sums.end());
    }

    vector<long long> v1(sums1.begin(), sums1.end());

    set<long long> sums2;
    sums2.insert(0);

    for (int i = n1; i < n; i++) {
        set<long long> new_sums;
        for (long long sum : sums2) {
            long long new_sum = (sum + a[i]) % m;
            new_sums.insert(new_sum);
        }
        sums2.insert(new_sums.begin(), new_sums.end());
    }

    vector<long long> v2(sums2.begin(), sums2.end());
    sort(v2.begin(), v2.end());

    long long answer = 0;

    for (long long sum1 : v1) {
        long long target = m - 1 - sum1;

        auto it = upper_bound(v2.begin(), v2.end(), target);
        if (it != v2.begin()) {
            it--;
            long long sum2 = *it;
            answer = max(answer, (sum1 + sum2) % m);
        }

        if (!v2.empty()) {
            long long sum2 = v2.back();
            answer = max(answer, (sum1 + sum2) % m);
        }
    }

    cout << answer << endl;

    return 0;
}