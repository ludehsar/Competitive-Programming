/**
  * Strongly Connected Component
  * Kosaraju's Algorighm
  * Complexity: O(V + E)
  */

int n;
stack<int> Stack;
vi adj[mxN], tadj[mxN]; // tadj contains the reverse directions of all the directed edges of adj.
bool visited[mxN];
vvi scc; // Contains all the scc(s).

void dfs(int u) {
    if (visited[u]) return;
    visited[u] = 1;
    for (int v : adj[u]) {
        dfs(v);
    }
    Stack.push(u);
}

void dfs2(int id, int u) {
    if (visited[u]) return;
    visited[u] = 1;
    scc[id].PB(u);
    for (int v : tadj[u]) {
        dfs2(id, v);
    }
}

// Just call the function when finding all the scc(s).
// This stores all the scc(s) in the scc vector.
void kosaraju() {
    mem(visited, 0);
    for (int u = 1; u <= n; ++u) {
        if (!visited[u]) {
            dfs(u);
        }
    }
    mem(visited, 0);
    int cnt = 0;
    while (!Stack.empty()) {
        int u = Stack.top();
        Stack.pop();
        if (!visited[u]) {
            scc.PB(vi(0));
            dfs2(cnt, u);
            cnt++;
        }
    }
}
