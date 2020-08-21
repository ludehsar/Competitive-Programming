//Complexity : O(NlogN)
// returns points of convex hull in CW direction.
double EPS = 1e-12;
struct PT {
  double x, y;
  PT() {}
  PT(double x, double y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (double c)     const { return PT(x*c,   y*c  ); }
  PT operator / (double c)     const { return PT(x/c,   y/c  ); }
  bool operator <(const PT &p) const {
    return x < p.x || (x == p.x && y < p.y);
  }
};
ostream &operator<<(ostream &os, const PT &p) {
  os << "(" << p.x << "," << p.y << ")";
}
// checks if a-b-c is CW or not.
bool isPointsCW(PT a, PT b, PT c) {
  return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y)+EPS < 0;
}
// checks if a-b-c is CCW or not.
bool isPointsCCW(PT a, PT b, PT c) {
  return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > EPS;
}
// checks if a-b-c is collinear or not.
bool isPointsCollinear(PT a, PT b, PT c) {
  return abs(a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y)) <= EPS;
}
void convex_hull(vector<PT>& a) { ///^ == upper hull, U == lower hull
  int a_sz = a.size();
  if (a_sz == 1) return;
  sort(a.begin(), a.end());
  PT p1 = a[0], p2 = a.back();
  vector<PT> up, down; // up will store upper hull/lower envelope, down will store lower hull/upper envelope
  up.push_back(p1);
  down.push_back(p1);
  int up_sz = 1, down_sz = 1;
  for (int i = 1; i < a_sz; i++) {
    if (i == a_sz - 1 || isPointsCW(p1, a[i], p2)) {
///include all the collinear points of the boundary instead of only the outer two points:-
///while (up_sz >= 2 && (!isPointsCW(up[up_sz-2], up[up_sz-1], a[i]) && !isPointsCollinear(up[up_sz-2], up[up_sz-1], a[i])) )
      while (up_sz >= 2 && !isPointsCW(up[up_sz-2], up[up_sz-1], a[i])) {
        up.pop_back();
        --up_sz;
      }
      up.push_back(a[i]);
      ++up_sz;
    }
    if (i == a_sz - 1 || isPointsCCW(p1, a[i], p2)) {
///include all the collinear points of the boundary instead of only the outer two points:-
///while(down_sz >= 2 && (!isPointsCCW(down[down_sz-2], down[down_sz-1], a[i]) && !isPointsCollinear(down[down_sz-2], down[down_sz-1], a[i])) )
      while(down_sz >= 2 && !isPointsCCW(down[down_sz-2], down[down_sz-1], a[i])) {
        down.pop_back();
        --down_sz;
      }
      down.push_back(a[i]);
      ++down_sz;
    }
  }
  // up has upper hull/lower envelope
  // down has lower hull/upper envelope
  // a has the overall convex hull
  a.clear();
  for (int i = 0; i < up_sz; i++) a.push_back(up[i]);
  for (int i = down_sz - 2; i > 0; i--) a.push_back(down[i]);
}
