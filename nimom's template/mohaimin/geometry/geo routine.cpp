#include <bits/stdc++.h>
using namespace std;
#define optimize() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<pii> vii;
typedef vector<pll> vll;
typedef long double ld;
#define F first
#define S second
#define MP make_pair
#define PB push_back
double INF = 1e100;
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
  bool operator ==(const PT &p) const {
    return (abs(x-p.x) <= EPS && abs(y-p.y) <= EPS);
  }
};
double dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
double dist2(PT p, PT q)   { return dot(p-q,p-q); }
double cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }
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
// rotate a point CCW or CW around the origin
PT RotateCCW90(PT p)   { return PT(-p.y,p.x); }
PT RotateCW90(PT p)    { return PT(p.y,-p.x); }
PT RotateCCW(PT p, double t) {	// rotate a point CCW t degrees around the origin
  return PT(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t));
}
// rotate a point p CCW around another point q by angle t(radian)
PT RotateCCW_around_point(PT p, PT q, double t) {
  return PT((p.x-q.x)*cos(t)-(p.y-q.y)*sin(t)+q.x, (p.x-q.x)*sin(t)+(p.y-q.y)*cos(t)+q.y);
}
// project point c onto line through a and b
// assuming a != b
PT ProjectPointLine(PT a, PT b, PT c) {
  return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);
}
// project point c onto line segment through a and b
PT ProjectPointSegment(PT a, PT b, PT c) {
  double r = dot(b-a,b-a);
  if (abs(r) < EPS) return a;
  r = dot(c-a, b-a)/r;
  if (r+EPS < 0) return a;
  if (r > 1+EPS) return b;
  return a + (b-a)*r;
}
// compute distance from c to segment between a and b
double DistancePointSegment(PT a, PT b, PT c) {
  return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}
// compute distance between point (x,y,z) and plane ax+by+cz=d
double DistancePointPlane(double x, double y, double z,
                          double a, double b, double c, double d) {
  return abs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}
// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d) {
  return abs(cross(b-a, c-d)) < EPS;
}
bool LinesCollinear(PT a, PT b, PT c, PT d) {
  return LinesParallel(a, b, c, d)
    && abs(cross(a-b, a-c)) < EPS
    && abs(cross(c-d, c-a)) < EPS;
}
// determine if line segment from a to b intersects with
// line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
  if (LinesCollinear(a, b, c, d)) {
    if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
      dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
    if (dot(c-a, c-b) > EPS && dot(d-a, d-b) > EPS && dot(c-b, d-b) > EPS)
      return false;
    return true;
  }
  if (cross(d-a, b-a) * cross(c-a, b-a) > EPS) return false;
  if (cross(a-c, d-c) * cross(b-c, d-c) > EPS) return false;
  return true;
}
// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
  b=b-a; d=c-d; c=c-a;
  assert(dot(b, b) > EPS && dot(d, d) > EPS);
  return a + b*cross(c, d)/cross(b, d);
}
// shift the straight line passing through points a and b
// by distance Dist.
// If Dist is negative the line is shifted rightwards or upwards.
// If Dist is positive the line is shifted leftwards or downwards.
// The new line passes through points c and d
pair<PT,PT> ShiftLineByDist(PT a, PT b, double Dist) {
  double r = sqrt( dist2(a, b) );
  double delx = (Dist*(a.y-b.y))/r;
  double dely = (Dist*(b.x-a.x))/r;
  PT c = PT(a.x+delx, a.y+dely);
  PT d = PT(b.x+delx, b.y+dely);
  return MP(c, d);
}
// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
// *** The centers of the two circles must not coincide. i.e (a != b)
vector<PT> CircleCircleIntersection(PT a, PT b, double r, double R) {
  vector<PT> ret;
  double d = sqrt(dist2(a, b));
  if (d > r+R || d+min(r, R) < max(r, R)) return ret;
  double x = (d*d-R*R+r*r)/(2*d);
  double y = sqrt(r*r-x*x);
  PT v = (b-a)/d;
  ret.push_back(a+v*x + RotateCCW90(v)*y);
  if (y > 0)
    ret.push_back(a+v*x - RotateCCW90(v)*y);
  return ret;
}
// This code computes the area or centroid of a (possibly nonconvex)
// polygon, assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.  Note that the centroid is often known as
// the "center of gravity" or "center of mass".
double ComputeSignedArea(const vector<PT> &p) {
  double area = 0;
  for(int i = 0; i < p.size(); i++) {
    int j = (i+1) % p.size();
    area += p[i].x*p[j].y - p[j].x*p[i].y;
  }
  return area / 2.0;
}
double ComputeArea(const vector<PT> &p) {
  return abs(ComputeSignedArea(p));
}
PT ComputeCentroid(const vector<PT> &p) {
  PT c(0,0);
  double scale = 6.0 * ComputeSignedArea(p);
  for (int i = 0; i < p.size(); i++){
    int j = (i+1) % p.size();
    c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
  }
  return c / scale;
}
// angle from p2->p1 to p2->p3, returns -PI to PI (but you may choose to return the absolute value only which is "more practical").
double angle(PT p1, PT p2, PT p3) {
  PT va = p1-p2,vb=p3-p2;
  double x,y;
  x=dot(va,vb);
  y=cross(va,vb);
  return(atan2(y,x)); /// return abs( atan2(y,x) ) to get the absolute value of angle. (tested)
}
double angle_to_radian( double theta ) {
  return ((M_PI/180.0)*theta);
}
double radian_to_angle( double x ) {
  return ((180.0/M_PI)*x);
}
int main() {
  // expected: (-5,2)
  cerr << RotateCCW90(PT(2,5)) << endl;
  // expected: (5,-2)
  cerr << RotateCW90(PT(2,5)) << endl;
  // expected: (-5,2)
  cerr << RotateCCW(PT(2,5),M_PI/2) << endl;
  // expected: (5,2)
  cerr << ProjectPointLine(PT(-5,-2), PT(10,4), PT(3,7)) << endl;
  // expected: (5,2) (7.5,3) (2.5,1)
  cerr << ProjectPointSegment(PT(-5,-2), PT(10,4), PT(3,7)) << " "
    << ProjectPointSegment(PT(7.5,3), PT(10,4), PT(3,7)) << " "
    << ProjectPointSegment(PT(-5,-2), PT(2.5,1), PT(3,7)) << endl;
  // expected: 6.78903
  cerr << DistancePointPlane(4,-4,3,2,-2,5,-8) << endl;
  // expected: 1 0 1
  cerr << LinesParallel(PT(1,1), PT(3,5), PT(2,1), PT(4,5)) << " "
    << LinesParallel(PT(1,1), PT(3,5), PT(2,0), PT(4,5)) << " "
    << LinesParallel(PT(1,1), PT(3,5), PT(5,9), PT(7,13)) << endl;
  // expected: 0 0 1
  cerr << LinesCollinear(PT(1,1), PT(3,5), PT(2,1), PT(4,5)) << " "
    << LinesCollinear(PT(1,1), PT(3,5), PT(2,0), PT(4,5)) << " "
    << LinesCollinear(PT(1,1), PT(3,5), PT(5,9), PT(7,13)) << endl;
  // expected: (1,2)
  cerr << ComputeLineIntersection(PT(0,0), PT(2,4), PT(3,1), PT(-1,3)) << endl;
  // area should be 5.0
  // centroid should be (1.1666666, 1.166666)
  PT pa[] = { PT(0,0), PT(5,0), PT(1,1), PT(0,5) };
  vector<PT> p(pa, pa+4);
  PT c = ComputeCentroid(p);
  cerr << "Area: " << ComputeArea(p) << endl;
  cerr << "Centroid: " << c << endl;
  // expected: 0
  cerr << isPointsCCW( PT(5, 6), PT(10, 10), PT(11, 5) ) << endl;
  // expected: 1
  cerr << isPointsCCW( PT(5, 6), PT(10, 2), PT(11, 5) ) << endl;
  // expected: 1
  cerr << isPointsCW( PT(5, 6), PT(10, 10), PT(11, 5) ) << endl;
  // expected: 0
  cerr << isPointsCW( PT(5, 6), PT(10, 2), PT(11, 5) ) << endl;
  // expected: 0
  cerr << isPointsCollinear( PT(5, 6), PT(10, 2), PT(11, 5) ) << endl;
  // expected: 1
  cerr << isPointsCollinear( PT(5, 6), PT(10, 6), PT(11, 6) ) << endl;
  // expected: (-0.437602,12.6564) (2.5624,14.6564)
  cerr << ShiftLineByDist( PT(4, 6), PT(7, 8), 8 ).F << " " << ShiftLineByDist( PT(4, 6), PT(7, 8), 8 ).S << endl;
  // expected: (8.4376,-0.656402) (11.4376,1.3436)
  cerr << ShiftLineByDist( PT(4, 6), PT(7, 8), -8 ).F << " " << ShiftLineByDist( PT(4, 6), PT(7, 8), -8 ).S << endl;
}
