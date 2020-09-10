/**
Ford-Fulkerson method
Complexity O ( V * E^2 )
**/

struct Ford {

    int n, s, t;
    const int inf = 2147483647;
    vector < vector < int > > capacity;
    vector < vector < int > > adj;
    int parent[mx];

    Ford ( int n, int s, int t ): n(n), s(s), t(t), adj(n+1), capacity( n+1, vector < int > (n+1, 0) ) {}

    void addEdge( int u, int v, int cap ) {
        adj[u].push_back ( v );
        adj[v].push_back ( u );
        capacity[u][v] = cap;
        /**
        For undirected graph :
        capacity[u][v] = cap;
        capacity[v][u] = cap;
        **/
    }

    int bfs() {
        mem ( parent, -1 );
        parent[s] = -2;
        queue<pair<int, int>> q;
        q.push({s, inf});

        while (!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int next : adj[cur]) {
                if (parent[next] == -1 && capacity[cur][next] > 0 ) {
                    parent[next] = cur;
                    int new_flow = min(flow, capacity[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({next, new_flow});
                }
            }
        }

        return 0;
}

    int maxflow() {
        int flow = 0;
        int new_flow;

        while (new_flow = bfs()) {
            flow += new_flow;
            int cur = t;
            while (cur != s) {
                int prev = parent[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
        }

        return flow;
    }

};



int main()
{
    optimize();
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    Ford ford ( n, s, t );

    for ( int i = 1; i <= m; i++ ) {
        int u, v, w;
        cin >> u >> v >> w;
        ford.addEdge( u, v, w );
    }

    cout << ford.maxflow();

    return 0;
}
