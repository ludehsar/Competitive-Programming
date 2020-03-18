//complexity: O(E+V)
//https://cp-algorithms.com/graph/bridge-searching.html
//nodes are 1-based indexed.

int n; // number of nodes
vector<vector<int>> adjlist; // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int u, int par = -1) {
    visited[u] = true;
    tin[u] = low[u] = timer++;
    for (auto to : adjlist[u]) {
        if (to == par) continue;
        if (visited[to]) {
            low[u] = min(low[u], tin[to]);
        }
        else {
            dfs(to, u);
            low[u] = min(low[u], low[to]);
            if (low[to] > tin[u]) {
                IS_BRIDGE(u, to);
            }
        }
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(n+1, false);
    tin.assign(n+1, -1);
    low.assign(n+1, -1);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) dfs(i);
    }
}


