//Complexity: O(sqrt(V) * E), constant may be a bit high.
//Works on self loops, undirected graphs.
//if( h.R[u] != -1 ) then u is situated in left part, h.R[u] is situated in right part;
//if( h.L[u] != -1 ) then u is situated in right part, h.L[u] is situated in left part;
struct Hopcroft_karp {
  int n;
  vector< vector<int> > edge;
  vector<int> dis, parent, L, R;
  vector<int> Q;
  Hopcroft_karp(int n_) : n(n_), edge(n_+1), dis(n_+1), parent(n_+1), L(n_+1), R(n_+1), Q( ((n_+1)*10)+1 ) {};
  void add_edge( int u, int v ) {
    edge[u].push_back(v);
  }
  bool dfs(int i) {
    int len = edge[i].size();
    for (int j = 0; j < len; j++) {
      int x = edge[i][j];
      if (L[x] == -1 || (parent[L[x]] == i)) {
        if (L[x] == -1 || dfs(L[x])) {
          L[x] = i;
          R[i] = x;
          return (true);
        }
      }
    }
    return false;
  }
  bool bfs() {
    int x, f = 0, l = 0;
    fill( dis.begin(), dis.end(), -1 );
    for (int i = 1; i <= n; i++) {
      if (R[i] == -1) {
        Q[l++] = i;
        dis[i] = 0;
      }
    }
    while (f < l) {
      int i = Q[f++];
      int len = edge[i].size();
      for (int j = 0; j < len; j++) {
        x = edge[i][j];
        if (L[x] == -1) return true;
        else if (dis[L[x]] == -1) {
          parent[L[x]] = i;
          dis[L[x]] = dis[i] + 1;
          Q[l++] = L[x];
        }
      }
    }
    return false;
  }
  int matching() {
    int counter = 0;
    fill( L.begin(), L.end(), -1 );
    fill( R.begin(), R.end(), -1 );
    while (bfs()) {
      for (int i = 1; i <= n; i++) {
        if (R[i] == -1 && dfs(i)) counter++;
      }
    }
    return counter;
  }
};
int main() {
  int T;
  cin >> T;
  for( int test = 1; test <= T; ++test ) {
    int n, m;  //no. of nodes; no. of edges;
    cin >> n >> m;
    Hopcroft_karp h(n);
    for( int i = 0; i < m; ++i ) {
      int u, v;
      cin >> u >> v;
      /** //Undirected:
      h.add_edge(u, v);
      h.add_edge(v, u);
      **/
      //Directed:
      h.add_edge(u, v);
    }
    /** //Undirected:
    int ans = h.matching()/2; //we divide by 2 because incase of undirected graphs matching() returns the number of nodes involved in maximum matching;
    **/
    //Directed:
    int ans = h.matching();
    cout << ans << endl;
    //print the actual maximum matching (this part is not applicable for undirected graphs!)
    for( int i = 1; i <= n; ++i ) {
      if( h.L[i] != -1 ) cout << h.L[i] << " " << i << endl;
    }
  }
}
