///O(nlgn)
///The implementation is for double version.
///modify for int/long long version. take help of comments in code.
double INF = 1e100;
double EPS = 1e-12;
struct PT {
  PT () {}
  double x, y; ///take int/long long as necessary
  int id;
  PT(double x_, double y_, int id_) : x(x_), y(y_), id(id_) {} ///take int/long long as necessary
};
struct cmp_x {
  bool operator()(const PT & a, const PT & b) const {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
  }
};
struct cmp_y {
  bool operator()(const PT & a, const PT & b) const {
    return a.y < b.y;
  }
};
vector<PT> points; ///contains input points;
vector<PT> temp_points;
double mindist; ///change double to int/long long as per necessity
pair<int, int> best_pair; ///contain best pair of points' indexes
void upd_ans(const PT & a, const PT & b) {
  double dist = sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)); ///remove sqrt() and store in int/long long variable as necessary
  if (dist + EPS < mindist) { /// remove EPS if working with int/long long
    mindist = dist;
    best_pair = {a.id, b.id};
  }
}
void ClosestPair(int l, int r) {
  if (r - l <= 3) {
    for (int i = l; i < r; ++i) {
      for (int j = i + 1; j < r; ++j) {
        upd_ans(points[i], points[j]);
      }
    }
    sort(points.begin() + l, points.begin() + r, cmp_y());
    return;
  }
  int mid = (l + r) >> 1;
  double midx = points[mid].x; ///take int/long long as necessary
  ClosestPair(l, mid);
  ClosestPair(mid, r);
  merge(points.begin() + l, points.begin() + mid, points.begin() + mid, points.begin() + r, temp_points.begin(), cmp_y());
  copy(temp_points.begin(), temp_points.begin() + r - l, points.begin() + l);
  int tsz = 0;
  for (int i = l; i < r; ++i) {
    ///take if((points[i].x - midx)*(points[i].x - midx) < mindist) as necessary
    if (abs(points[i].x - midx)+EPS < mindist) {
      ///take j >= 0 && (points[i].y-temp_points[j].y)*(points[i].y-temp_points[j].y) < mindist as necessary
      for (int j = tsz - 1; j >= 0 && points[i].y - temp_points[j].y + EPS < mindist; --j)
        upd_ans(points[i], temp_points[j]);
      temp_points[tsz++] = points[i];
    }
  }
}
int main() {
  int n; ///number of points
  cin >> n;
  points.clear();
  for( int i = 0; i < n; ++i ) {
    double x, y;
    cin >> x >> y;
    points.PB( PT(x, y, i) );
  }
  temp.points.clear();
  temp_points.resize((int)points.size());
  sort(points.begin(), points.end(), cmp_x()); ///points vector contains the input points
  ///Double version:
  mindist = INF;
  ClosestPair(0, (int)points.size());
  double ans = mindist;
  /** //int/long long version:
  mindist = infLL;
  ClosestPair(0, (int)points.size());
  double ans = sqrt( (double)mindist );
  **/
  cout << ans << endl; /// minimum distance
  cout << best_pair.F << " " << best_pair.S << endl; ///optimal pair of points' indexes
}
