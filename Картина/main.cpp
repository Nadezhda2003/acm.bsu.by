#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Segment {
    int l, r;
    Segment(int l, int r) : l(l), r(r) {}
    bool operator<(const Segment& other) const {
        return l < other.l;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    set<Segment> black_segments;

    for (int i = 0; i < n; i++) {
        char c;
        int l, x;
        cin >> c >> l >> x;
        int r = l + x;

        if (c == 'B') {
            vector<Segment> overlaps;
            for (const auto& seg : black_segments) {
                if (!(seg.r < l || r < seg.l)) {
                    overlaps.push_back(seg);
                }
            }

            if (!overlaps.empty()) {
                int new_l = l, new_r = r;
                for (const auto& seg : overlaps) {
                    new_l = min(new_l, seg.l);
                    new_r = max(new_r, seg.r);
                    black_segments.erase(seg);
                }
                black_segments.insert(Segment(new_l, new_r));
            }
            else {
                black_segments.insert(Segment(l, r));
            }

        }
        else {
            vector<Segment> to_remove;
            vector<Segment> to_add;

            for (const auto& seg : black_segments) {
                if (seg.l < r && seg.r > l) {
                    to_remove.push_back(seg);
                    if (seg.l < l) {
                        to_add.push_back(Segment(seg.l, l));
                    }
                    if (seg.r > r) {
                        to_add.push_back(Segment(r, seg.r));
                    }
                }
            }

            for (const auto& seg : to_remove) {
                black_segments.erase(seg);
            }
            for (const auto& seg : to_add) {
                black_segments.insert(seg);
            }
        }

        vector<Segment> temp(black_segments.begin(), black_segments.end());
        black_segments.clear();
        for (const auto& seg : temp) {
            if (seg.r > seg.l) {
                black_segments.insert(seg);
            }
        }

        int count = black_segments.size();
        long long total_len = 0;
        for (const auto& seg : black_segments) {
            total_len += (seg.r - seg.l);
        }

        cout << count << " " << total_len << "\n";
    }

    return 0;
}