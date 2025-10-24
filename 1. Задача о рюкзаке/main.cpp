#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

struct Item {
    long long weight, value;
    int index;
};

struct Subset {
    long long weight, value;
    int mask;

    bool operator<(const Subset& other) const {
        return weight < other.weight;
    }
};

vector<Subset> generate_subsets(const vector<Item>& items) {
    int n = items.size();
    vector<Subset> subsets;

    for (int mask = 0; mask < (1 << n); mask++) {
        long long weight = 0, value = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                weight += items[i].weight;
                value += items[i].value;
            }
        }
        subsets.push_back({ weight, value, mask });
    }

    sort(subsets.begin(), subsets.end());
    vector<Subset> filtered;
    long long max_val = -1;

    for (const auto& subset : subsets) {
        if (subset.value > max_val) {
            filtered.push_back(subset);
            max_val = subset.value;
        }
    }

    return filtered;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    long long W;
    cin >> n >> W;

    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight >> items[i].value;
        items[i].index = i + 1;
    }

    int half = n >> 1;
    vector<Item> first_half(items.begin(), items.begin() + half);
    vector<Item> second_half(items.begin() + half, items.end());

    vector<Subset> left_subsets = generate_subsets(first_half);
    vector<Subset> right_subsets = generate_subsets(second_half);

    vector<long long> right_weights;
    vector<long long> right_values;
    vector<int> right_masks;

    for (const auto& subset : right_subsets) {
        right_weights.push_back(subset.weight);
        right_values.push_back(subset.value);
        right_masks.push_back(subset.mask);
    }

    vector<long long> prefix_max(right_values.size());
    for (size_t i = 0; i < right_values.size(); i++) {
        if (i == 0) {
            prefix_max[i] = right_values[i];
        }
        else {
            prefix_max[i] = max(prefix_max[i - 1], right_values[i]);
        }
    }

    long long best_value = -1;
    int best_left_mask = 0, best_right_mask = 0;

    for (const auto& left : left_subsets) {
        if (left.weight > W) continue;

        long long remaining = W - left.weight;

        int idx = upper_bound(right_weights.begin(), right_weights.end(), remaining) - right_weights.begin() - 1;

        if (idx >= 0) {
            long long total_value = left.value + prefix_max[idx];
            if (total_value > best_value) {
                best_value = total_value;
                best_left_mask = left.mask;
                for (int j = idx; j >= 0; j--) {
                    if (right_values[j] == prefix_max[idx] && right_weights[j] <= remaining) {
                        best_right_mask = right_masks[j];
                        break;
                    }
                }
            }
        }
    }

    vector<int> result;

    for (int i = 0; i < half; i++) {
        if (best_left_mask & (1 << i)) {
            result.push_back(first_half[i].index);
        }
    }

    for (int i = 0; i < (int)second_half.size(); i++) {
        if (best_right_mask & (1 << i)) {
            result.push_back(second_half[i].index);
        }
    }

    cout << result.size() << "\n";
    if (!result.empty()) {
        for (size_t i = 0; i < result.size(); i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }

    return 0;
}