//Insertion - O(lgN), query - O(lgN)
//Querying in empty cht container gives runtime error!
//y = mx+b;
const ll IS_QUERY = -(1LL<<62); //-INF
struct Line {
  ll m, b;
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != IS_QUERY) return m < rhs.m;
    const Line* s = succ();
    if (!s) return 0;
    ll x = rhs.m;
    return (long double)b - s->b < (long double)(s->m - m) * x; //add precision only if wa;
  }
};
// Keeps upper hull for maximums.
// add lines with -m and -b and return -ans to make this code working for minimums.
struct HullDynamic : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
        return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if (z == end()) return y->m == x->m && y->b <= x->b;
    return (long double)(x->b - y->b)*(z->m - y->m) >= (long double)(y->b - z->b)*(y->m - x->m); //add precision only if wa;
  }
  void insert_line(ll m, ll b) {
    auto y = insert({ m, b });  // insert({-m, -b)} instead to work for minimums.
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) { erase(y); return; }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  ll query(ll x) {
    auto l = *lower_bound((Line) { x, IS_QUERY });
    return l.m * x + l.b;  // return (-1LL)*(l.m * x + l.b) instead for getting minimums.
  }
};
int main() {
  HullDynamic cht;
  int T;
  cin >> T;
  while(T--) {
    cht.clear();
  }
}
