///Graph hashing is not the same as string hashing;
///Be intuitive;
///No idea how this works. But is works;

///***Here double hashing was used. Single hashing will also do.
/**
Q) How to hash the path u-v-w?
A) hash value of the path = ((po1[u]+po1[v]+po1[w])%MOD1, (po2[u]+po2[v]+po2[w])%MOD2)
**/
const int MAXN = 1e5+5;  ///MAX value of nodes;
int n;  ///no. of nodes;
int base1 = 131, base2 = 137;  ///fairly big prime number; prime numbers strictly greater than max no. of nodes may also do;
ll po1[MAXN], po2[MAXN];  /// po1[u] and po2[u] stores the double hash value of node u;
#define MOD1 1000000007
#define MOD2 1000000009
int main() {
  po1[0] = po2[0] = 1;
  for( int i = 1; i <= n; ++i ) {
    po1[i] = po1[i-1]*base1;
    po1[i] %= MOD1;
   
    po2[i] = po2[i-1]*base2;
    po2[i] %= MOD2;
  }
}
