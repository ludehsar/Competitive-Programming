const int mx = 100100;
int n, m, par[mx], sz[mx];
bool ans[mx];
pii queries[mx];
vii t[mx*5];
map<pii, int> M;
stack<int> st;

void update(int cur, int s, int e, int l, int r, pii val) {
    if (s > r || e < l) return;
    if (l <= s && e <= r) {
        t[cur].PB(val);
        return;
    }
    int c1 = (cur << 1), c2 = c1 | 1, m = (s + e) >> 1;
    update(c1, s, m, l, r, val);
    update(c2, m + 1, e, l, r, val);
}

int Find(int u) { return (par[u] == u ? u : Find(par[u])); }

bool isSame(int u, int v) { return Find(u) == Find(v); }

bool makeAns(int i) {
    if (queries[i].F != -1) {
        return isSame(queries[i].F, queries[i].S);
    }
    return 0;
}

void Merge(pii edge) {
    int u = Find(edge.F), v = Find(edge.S);
    if (u == v) return;
    if (sz[u] < sz[v]) swap(u, v);
    sz[u] += sz[v];
    par[v] = u;
    st.push(v);
}

void rollback(int moment) {
    while (st.size() > moment) {
        int cur = st.top();
        st.pop();
        sz[Find(cur)] -= sz[cur];
        par[cur] = cur;
    }
}

void dfs(int cur, int s, int e) {
    if (s > e) return;
    int moment = st.size();
    for (pii edge : t[cur]) {
        Merge(edge);
    }
    if (s == e) ans[s] = makeAns(s);
    else {
        int c1 = (cur << 1), c2 = c1 | 1, m = (s + e) >> 1;
        dfs(c1, s, m);
        dfs(c2, m + 1, e);
    }
    rollback(moment);
}

int main() {
    optimize();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        par[i] = i;
        sz[i] = 1;
    }
    for (int i = 1; i <= m; ++i) queries[i] = MP(-1, -1);
    for (int i = 1; i <= m; ++i) {
        string q;
        int u, v;
        cin >> q >> u >> v;
        if (u < v) swap(u, v);
        if (q == "conn") queries[i] = MP(u, v);
        else {
            if (q == "rem") {
                update(1, 1, m, M[MP(u, v)], i, MP(u, v));
                M.erase(MP(u, v));
            }
            else M[MP(u, v)] = i;
        }
    }
    for (auto it : M) update(1, 1, m, it.S, m, it.F);
    dfs(1, 1, m);
    for (int i = 1; i <= m; ++i) {
        if (queries[i].F != -1) {
            cout << (ans[i] ? "YES" : "NO") << endl;
        }
    }
    return 0;
}
