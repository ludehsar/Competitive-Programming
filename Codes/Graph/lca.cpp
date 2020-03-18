//https://cp-algorithms.com/graph/lca_binary_lifting.html

int n, l;
vector<vector<int>> adjlist;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int u, int par)
{
    tin[u] = ++timer;
    up[u][0] = par;
    for (int i = 1; i <= l; ++i) up[u][i] = up[up[u][i-1]][i-1];
    for (auto v : adjlist[u]) {
        if (v != par) dfs(v, u);
    }
    tout[u] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n+1);
    tout.resize(n+1);
    timer = 0;
    l = ceil(log2(n+1));
    up.assign(n+1, vector<int>(l + 1));
    dfs(root, root);
}
