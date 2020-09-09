int par[10005];
int sz[10005];
int Find(int r) { //Path compression
  if( par[r] == r ) return r;
  par[r] = Find(par[r]);
  return par[r];
}
void Union(int a, int b) { //Union by size of subtrees.
  a = Find(a);
  b = Find(b);
  if (a != b) {
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] += sz[b];
  }
}
int main() {
  for( int i = 0; i < 10005; ++i ) {
    par[i] = i;
    sz[i] = 1;
  }
}
