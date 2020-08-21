///Graph hashing is not the same as string hashing;
///Be intuitive;
///No idea how this works. But is works;

///***Here double hashing was used. Single hashing will also do.
/**
Q) How to hash the path u-v-w?
A) There are two ways-
   1. hash value of the path = ((xx1[u]+xx1[v]+xx1[w]), (xx2[u]+xx2[v]+xx2[w]))
   2. hash value of the path = ((xx1[u]^xx1[v]^xx1[w]), (xx2[u]^xx2[v]^xx2[w]))

   Way no-1 can be used any time, but way no-2 can be used if and only if the path has no repetitive nodes;
**/
mt19937 rng((unsigned)chrono::system_clock::now().time_since_epoch().count());
const int MAXN = 1e5+5;	///MAX value of nodes;
int n;	/// No. of nodes;
ll xx1[MAXN], xx2[MAXN];	/// xx1[u] and xx2[u] stores the double hash value of node u;
int main() {
  for( int i = 1; i <= n; ++i ) {
    xx1[i] = rng(), xx2[i] = rng();
  }
}
