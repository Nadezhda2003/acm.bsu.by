#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>> graph;
vector<int> euler;

void dfs(int start, int n) {
    stack<pair<int, int>> st;
    vector<int> vis(n + 1, 0);

    st.push({ start, -1 });

    while (!st.empty())
    {
        int u = st.top().first;
        int parent = st.top().second;

        if (vis[u] < graph[u].size())
        {
            int v = graph[u][vis[u]++];
            if (v != parent)
            {
                euler.push_back(u);
                st.push({ v,u });
            }
        }
        else
        {
            euler.push_back(u);
            st.pop();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    graph.resize(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(1, n);

    for (int i = 0; i < euler.size(); i++) {
        if (i > 0) cout << " ";
        cout << euler[i];
    }
    cout << '\n';

    return 0;
}