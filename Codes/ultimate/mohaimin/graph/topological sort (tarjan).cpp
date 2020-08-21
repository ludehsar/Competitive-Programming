///complexity: O(N)
vi adjlist[10005];
bool vis[10005];
vector<int> toposort;
void dfs_topo( int u ) {
  vis[u] = 1;
  for( auto v : adjlist[u] ) {
    if( !vis[v] ) dfs_topo(v);
  }
  toposort.PB(u);
}
int main() {
  for( int i = 1; i <= n; ++i ) {
    if( !vis[i] ) dfs_topo(i);
  }
  reverse( toposort.begin(), toposort.end() );
}
