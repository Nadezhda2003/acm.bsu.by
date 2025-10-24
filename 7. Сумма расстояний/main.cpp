#include <iostream>
#include <bitset>

using namespace std;
const int N = 2000;
bitset<N> adj[N];
int dist[N][N];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		for (int j = 0; j < n; j++)
		{
			adj[i][j] = (s[j] == '1');
			dist[i][j] = n;
		}
	}

    for (int u = 0; u < n; u++) {
        bitset<N> visited;
        bitset<N> cur;

        dist[u][u] = 0;
        visited[u] = 1;
        cur[u] = 1;

        int d = 1;
        while (true) {
            bitset<N> next;
            for (int j = cur._Find_first(); j < N; j = cur._Find_next(j))
                    next |= adj[j];
            next &= ~visited;
            if (next.none()) break;
            for (int v = v = next._Find_first(); v < N; v = next._Find_next(v))
                    dist[u][v] = d;

            visited |= next;
            cur = next;
            d++;
        }
    }

	long long result = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			result += dist[i][j] * dist[i][j];
	
   cout << result << '\n';
	return 0;
}