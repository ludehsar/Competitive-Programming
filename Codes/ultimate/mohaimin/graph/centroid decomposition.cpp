const int MAXN = 1e5+5; /// Maximum no. of nodes;
int n; /// Number of nodes;
vector<int> adjlist[MAXN];
int sub_cd[MAXN]; /// sub_cd[u] = subtree size of node u after each decomposing;
bool done_cd[MAXN]; /// done_cd[u] = node u have been decomposed;
void dfs_sub_cd(int u, int par) {
  sub_cd[u] = 1;
  for( auto v: adjlist[u] ) {
    if( done_cd[v] || v == par ) continue;
    dfs_sub_cd(v, u);
    sub_cd[u] += sub_cd[v];
  }
}
int dfs_find_centroid( int u, int par, int sz ) {
  for( auto v: adjlist[u] ) {
    if( !done_cd[v] && v != par && sub_cd[v] > sz ) {
      return dfs_find_centroid( v, u, sz );
    }
  }
  return u;
}
void dfs_decompose( int u ) {
  dfs_sub_cd(u, -1);
  int centroid = dfs_find_centroid(u, -1, sub_cd[u]/2);
  done_cd[centroid] = 1;
  for( auto v : adjlist[centroid] ) {
    if( !done_cd[v] ) dfs_decompose(v);
  }
}
