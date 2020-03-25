struct edge {
    int u, v, w;
    bool operator<(const edge& p) const
    {
        return w < p.w;
    }
};

int par[MAXN], size[MAXN];
vector<edge> e;

int find_root(int i) { return (par[i] == i ? i : par[i] = find_root(par[i])); }

void unite(int u, int v) {
    u = find_root(u), v = find_root(v);
    if (u != v) {
        if (size[u] < size[v]) swap(u, v);
        par[v] = u;
        size[u] += size[v];
    }
}

int mst(int n) {
    sort(e.begin(), e.end());
    for (int i = 1; i <= n; i++) {
        par[i] = i;
        size[i] = 1;
    }
    int s = 0;
    for (int i = 0; i < (int)e.size(); i++) {
        int u = find_root(e[i].u);
        int v = find_root(e[i].v);
        if (u != v) {
            unite(u, v);
            s += e[i].w;
        }
    }
    return s;
}
