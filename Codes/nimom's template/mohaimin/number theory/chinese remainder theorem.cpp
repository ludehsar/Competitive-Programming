/**
  x = a1(mod m1)
  x = a2(mod m2)
  .
  .
  x = a_n(mod m_n)
  solves this equation given all a_i's and all m_i's. Finds a **unique** value of x mod lcm(m1, m2, ... m_n), in other words only one solution of x exists which is lesser than lcm(m1, m2, ... m_n)
  Assumption: LCM of all mods (i.e all m_i) will fit into long long
  Complexity: O(nlg(L)), L = lcm(m1, m2, ..... m_n)
**/
struct ChineseRemainderTheorem{
  ll ans, lcm; ///ans means x, lcm means lcm(m1, m2,...mn)
  bool haveSolution; ///does the given congruence equation have any solution?
  ChineseRemainderTheorem(){}
  /// the chinese remainder theorem process is occuring in this constructor
  ChineseRemainderTheorem(const vector<ll> &a, const vector<ll> &m) { ///do not pass empty vectors here; all the values in the vectors must be non-negative!!
    assert( (int)a.size() == (int)m.size() );
    ll a1 = a[0];
    ll m1 = m[0];
    a1 %= m1;
    haveSolution = true;
    for( int i = 1; i < (int)a.size(); ++i ) {
      ll a2 = a[i];
      ll m2 = m[i];
      ll g = __gcd(m1, m2);
      if ( a1 % g != a2 % g ) {
        haveSolution = false;
        return;
      }
      ll p, q;
      extendedEuclid(m1/g, m2/g, p, q);
      ll hululu = m1 / g * m2;
      ll x = ( ((((__int128)a1 * ((m2/g) % hululu))%hululu * (q % hululu)) % hululu) + ((((((__int128)a2 % hululu) * ((m1/g) % hululu)) % hululu) * (p % hululu)) % hululu) ) % hululu;
      a1 = x;
      if( a1 < 0 ) a1 += hululu;
      m1 = hululu;
    }
    ans = a1, lcm = m1;
  }
  /// returns gcd(a, b); finds any x, y such that ax + by = gcd(a,b)
  ll extendedEuclid(ll a, ll b, ll &x, ll &y){ ///Range: ll(according to anachor)
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {
      ll q = a/b;
      ll t = b; b = a%b; a = t;
      t = xx; xx = x-q*xx; x = t;
      t = yy; yy = y-q*yy; y = t;
    }
    return a;
  }
};
