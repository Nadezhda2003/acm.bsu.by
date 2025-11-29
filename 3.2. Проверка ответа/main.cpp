#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string line;
    getline(cin, line);
    stringstream ss(line);

    vector<int> a;
    int x;

    while (ss >> x) {
        a.push_back(x);
    }

    int k = a.size();

    if (k % 2 == 0 || a[0] != a[k - 1]) {
        cout << "NO";
        return 0;
    }

    vector<int> lev((k + 3) / 2, 0);
    stack<int> vis;

    for (int i = 0; i < k; i++)
    {
        int u = a[i];;
        if (lev[u] == 0)
        {
            vis.push(u);
            lev[u] = 1;
        }
        else
        {
            if (vis.top() == u || lev[u] == 2)
            {
                cout << "NO";
                return 0;
            }
            int temp = vis.top();
            vis.pop();
            if (u != vis.top())
            {
                cout << "NO";
                return 0;
            }
            else
            {
                lev[temp] = 2;
            }

        }

    }

    cout << "YES";
    return 0;
}