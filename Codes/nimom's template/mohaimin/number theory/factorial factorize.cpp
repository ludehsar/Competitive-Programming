///How many times prime p occurs in n! (O(lgn))
long long factorialPrimePower ( long long n, long long p ) {
  long long freq = 0;
  long long x = n;
  while ( x ) {
    freq += x / p;
    x = x / p;
  }
  return freq;
}
///prime factorization of n! (O(nlgn))
void factFactorize ( long long n ) {
  for ( int i = 0; i < prime.size() && prime[i] <= n; i++ ) {
    ll x = n;
    ll freq = 0;
    while ( x ) {
      freq += x / prime[i];
      x = x / prime[i];
    }
    cout << prime[i] << '^' << freq << endl;
  }
}
