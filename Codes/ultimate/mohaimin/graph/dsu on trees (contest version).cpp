int cnt[MAXN];
bool big[MAXN];
void add(int u, int par, int x){
  cnt[ col[u] ] += x;
  for(auto v: adjlist[u])
    if(v != par && !big[v]) add(v, u, x);
}
void dfs(int u, int par, bool keep){
  int mx_val = -1, bigChild = -1;
  for(auto v : adjlist[u])
    if(v != par && sz[v] > mx_val) mx_val = sz[v], bigChild = v;
  for(auto v : adjlist[u])
    if(v != par && v != bigChild)
      dfs(v, u, 0); // run a dfs on small childs and clear them from cnt
  if(bigChild != -1)
    dfs(bigChild, u, 1), big[bigChild] = 1;  // bigChild marked as big and not cleared from cnt
  add(u, par, 1);
  //now cnt[c] is the number of vertices in subtree of vertex u that has color c. You can answer the queries easily.
  if(bigChild != -1) big[bigChild] = 0;
  if(keep == 0) add(u, par, -1);
}
But why it is O(nlogn)? You know that why dsu has O(qlogn) time (for q queries); the code uses the same method. Merge smaller to greater.
If you have heard heavy-light decomposition you will see that function add will go light edges only, because of this, code works in O(nlogn) time. Any problems of this type can be solved with same dfs function and just differs in add function.
