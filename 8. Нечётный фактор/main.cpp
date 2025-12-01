#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    //ifstream fin("oddfactor.in");
    //ofstream fout("oddfactor.out");
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges(m);
    vector<vector<pair<int, int>>> g(n + 1);

    int a, b;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        edges[i] = { a,b };
        g[a].push_back({ b,i });
        g[b].push_back({ a,i });
    }

    vector<int> used(n + 1, 0);
    vector<int> parent(n + 1, -1);
    vector<int> parent_edge(n + 1, -1);
    vector<int> need(n + 1, 0);
    vector<int> res;

    for (int s = 1; s <= n; s++)
    {
        if (used[s]) continue;
        
        vector<int> ord;
        stack<int> st;
        st.push(s);
        used[s] = 1;

        while (!st.empty())
        {
            int v = st.top();
            st.pop();
            ord.push_back(v);

            for (auto& p : g[v])
            {
                int t = p.first;
                int id = p.second;

                if (!used[t])
                {
                    used[t] = 1;
                    parent[t] = v;
                    parent_edge[t] = id;
                    st.push(t);
                }
            }
        }

        if (ord.size() % 2 != 0)
        {
            cout << -1 << '\n';
            return 0;
        }

        for (int v : ord) need[v] = 1;
        for (int j = ord.size() - 1; j >= 0; j--)
        {
            int v = ord[j];
            int p = parent[v];
            if (p == -1) continue;

            if (need[v])
            {
                res.push_back(parent_edge[v]);
                need[v] ^= 1;
                need[p] ^= 1;
            }
        }
        if (need[s])
        {
            cout << -1 << '\n';
            return 0;
        }
    }
    cout << res.size() << '\n';
    for (int id : res)
    {
        cout << edges[id].first << ' ' << edges[id].second << '\n';
    }
    return 0;
}