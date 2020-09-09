///Covers all types of conditions :)
struct ConvexHullTrick{
  vector<ll> m, b;
  int ptr = 0;
  bool bad(int l1, int l2, int l3) { ///add precision if only WA.
    return (long double)(b[l3] - b[l1])*(m[l1] - m[l2]) <= (long double)(b[l2] - b[l1])*(m[l1] - m[l3]); ///(slope dec+query min),(slope inc+query max)
    return (long double)(b[l3] - b[l1])*(m[l1] - m[l2]) > (long double)(b[l2] - b[l1])*(m[l1] - m[l3]); ///(slope dec+query max), (slope inc+query min)
  }
  void insert_line(ll _m, ll _b) {
    m.push_back(_m);
    b.push_back(_b);
    int s = m.size();
    while(s >= 3 && bad(s-3, s-2, s-1)) {
      s--;
      m.erase(m.end()-2);
      b.erase(b.end()-2);
    }
  }
  ll f(int i, ll x) { return m[i]*x + b[i]; }

  ///(slope dec+query min), (slope inc+query max) -> x increasing
  ///(slope dec+query max), (slope inc+query min) -> x decreasing
  ll query(ll x) {
    if(ptr >= m.size()) ptr = m.size()-1;
    while(ptr < m.size()-1 && f(ptr+1, x) < f(ptr, x)) ptr++; /// f(ptr+1, x) > f(ptr, x) for max query
    return f(ptr, x);
  }

  ///if there is no condition on x then simply ternary search on the function "f"
};
