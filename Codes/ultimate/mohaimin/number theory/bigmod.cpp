ll expo( ll b, ll p, ll m ) {
  ll res = 1LL, x = b%m;
  while(p) {
    if ( p&1LL ) res = ( res*x ) % m;
    x = ( x*x ) % m;
    p >>= 1LL;
  }
  return res;
}
