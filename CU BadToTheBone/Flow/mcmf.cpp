namespace mcmf {
    const int MAX = 1000010;
    const ll INF = 1LL << 60;

    ll cap[MAX], flow[MAX], cost[MAX], dist[MAX];
    int n, m, s, t, Q[1000010], adj[MAX], link[MAX], last[MAX], from[MAX], visited[MAX];

    void init(int nodes, int source, int sink) {
        m = 0, n = nodes, s = source, t = sink;
        for (int i = 0; i <= n; ++i) last[i] = -1;
    }

    int addEdge(int u, int v, ll c, ll w) {
        adj[m] = v, cap[m] = c, flow[m] = 0, cost[m] = +w, link[m] = last[u], last[u] = m++;
        adj[m] = u, cap[m] = 0, flow[m] = 0, cost[m] = -w, link[m] = last[v], last[v] = m++;
        return m - 2;
    }

    bool spfa() {
        int i, j, x, f = 0, l = 0;
        for (i = 0; i <= n; ++i) visited[i] = 0, dist[i] = INF;
        dist[s] = 0, Q[l++] = s;
        while (f < l) {
            i = Q[f++];
            for (j = last[i]; j != -1; j = link[j]) {
                if (flow[j] < cap[j]) {
                    x = adj[j];
                    if (dist[x] > dist[i] + cost[j]) {
                        dist[x] = dist[i] + cost[j], from[x] = j;
                        if (!visited[x]) {
                            visited[x] = 1;
                            if (f && rand() & 7) Q[--f] = x;
                            else Q[l++] = x;
                        }
                    }
                }
            }
            visited[i] = 0;
        }
        return (dist[t] != INF);
    }

    pll solve() {
        int i, j;
        ll maxFlow = 0, minCost = 0;
        while (spfa()) {
            ll aug = INF;
            for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i]) {
                aug = min(aug, cap[j] - flow[j]);
            }
            for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i]) {
                flow[j] += aug, flow[j ^ 1] -= aug;
            }
            maxFlow += aug, minCost += aug * dist[t];
        }
        return {minCost, maxFlow};
    }
}
