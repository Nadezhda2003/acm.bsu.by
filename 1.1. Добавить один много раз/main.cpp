#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <bitset>
#include <algorithm>

using namespace std;
long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }

pair<int, string> count_bit_changes(int k, vector<int>& initial_state, long long n) {
    string state = "";
    for (int bit : initial_state) {
        state += to_string(bit);
    }
    int max_changes = 0;


    int current_changes = 0;
    

    int total_changes = 0;

    return { max_changes, to_string(total_changes) + "/" + to_string(n) };
}

int main()
{
    int k;
    cin >> k;

    vector<int> initial_state(k);
    for (int i = 0; i < k; ++i) {
        cin >> initial_state[i];
    }

    long long n;
    cin >> n;

    auto result = count_bit_changes(k, initial_state, n);
    cout << result.first << endl;
    cout << result.second << endl;
	return 0;
}