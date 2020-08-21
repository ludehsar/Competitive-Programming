///HLD path query + Euler tour(pre-order traversal) subtree query

const int MAXN = 1e5+5;	/// max no. of nodes;
int n;	///number of nodes;

vector<int> adjlist[MAXN];
int sub[MAXN]; ///sub[u] = size of subtree u;
int head[MAXN]; ///head[u] = head of node u's chain;
int par[MAXN]; ///par[u] = parent of node u; parent of root node is -1;
int depth[MAXN]; ///depth[u] = depth of node u;

int tin[MAXN];
int tout[MAXN];
int timer;

/**
No need to clear at the beginning of a test case: sub, head, par, depth, tin, tout;
**/

/**
1. Position of node u in segment tree is: tin[u];
2. Subtree query(u): [tin[u], tout[u]]
3. Path query(u, v): [tin[u], tin[v]] (here u and v are of the same chain and depth[u] <= depth[v])
4. u--v is a heavy edge if and only if depth[u] == depth[v]-1 and adjlist[u][0] = v; Thus u and v are of the same chain;
**/

int arr[MAXN];	/// contains the values for the segment tree
int tree[MAXN * 4];

void init_hld( int node, int l, int r ) {
  if( l == r ) {
    tree[node] = arr[l];
    return;
  }
  int mid = (l + r)/2;
  init_hld( 2*node, l, mid );
  init_hld( 2*node+1, mid+1, r );
  tree[node] = max( tree[2*node], tree[2*node+1] );
}
void update_hld( int node, int l, int r, int b, int x ) { ///point update
  if( l == r ) {
    tree[node] = x;
    return;
  }
  int mid = (l + r)/2;
  if( mid >= b ) update_hld( 2*node, l, mid, b, x );
  else update_hld( 2*node+1, mid+1, r, b, x );
  tree[node] = max( tree[2*node], tree[2*node+1] );
}
int query_hld( int node, int l, int r, int b, int e ) {
  if( l > e || r < b ) return -inf;
  if( l >= b && r <= e ) return tree[node];
  int mid = (l + r)/2;
  return max( query_hld( 2*node, l, mid, b, e ), query_hld( 2*node+1, mid+1, r, b, e ) );
}

void dfs_sub( int u, int p, int dep ) {
  sub[u] = 1;
  par[u] = p;
  depth[u] = dep;
  int cur = 0;
  for( auto &v: adjlist[u] ) {
    if( v == p ) continue;
    dfs_sub(v, u, dep+1);
    sub[u] += sub[v];
    if(sub[v] > cur) {
      cur = sub[v];
      swap(v, adjlist[u][0]);
    }
  }
}

void dfs_hld( int u, int p ) {
  tin[u] = timer++;
  for( auto v: adjlist[u] ) {
    if( v == p ) continue;
    head[v] = (v == adjlist[u][0] ? head[u] : v);
    dfs_hld(v, u);
  }
  tout[u] = timer-1;
}

void preprocess(int root) {
  timer = 1;
  head[root] = root;
  dfs_sub(root, -1, 0);
  dfs_hld(root, -1);
}

int ultimate_query_hld(int u, int v) {
  int ans = -inf;
  while(head[u] != head[v]) {
    if(depth[head[u]] > depth[head[v]]) swap(u, v);
    ans = max(ans, query_hld(1, 1, n, tin[head[v]], tin[v]));
    v = par[head[v]];
  }
  if(depth[u] > depth[v]) swap(u, v);
  ans = max(ans, query_hld(1, 1, n, tin[u], tin[v]));
  return ans;
}

void ultimate_update_hld(int u, int v, int x) {
  while(head[u] != head[v]) {
    if(depth[head[u]] > depth[head[v]]) swap(u, v);
    update_hld(1, 1, n, tin[head[v]], tin[v], x);
    v = par[head[v]];
  }
  if(depth[u] > depth[v]) swap(u, v);
  update_hld(1, 1, n, tin[u], tin[v], x);
}

int lca(int u, int v) {
  while(head[u] != head[v]) {
    if(depth[head[u]] > depth[head[v]]) swap(u, v);
    v = par[head[v]];
  }
  if(depth[u] > depth[v]) swap(u, v);
  return u;
}
