// OFFLINE
// Complexity: O(NlgN)
// very easy concept and implementation
// https://codeforces.com/blog/entry/61710

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
};

ostream &operator<<(ostream &os, const PT &p) {
  os << "(" << p.x << "," << p.y << ")";
}


int steps = 600;

vector<PT> lower_hull, upper_hull;
int lower_hull_sz, upper_hull_sz;

bool leBorder = 0, riBorder = 0;

double func( double xx, double val )
{
	double ans1 = INF, ans2 = -INF, ans;
	for( int i = 0; i < lower_hull_sz-1; ++i ) {
		if( leBorder && (i == 0) ) continue;
		PT a = lower_hull[i], b = lower_hull[i+1];		// straight line passes through points a and b
		double m = (a.y-b.y)/(a.x-b.x);		// slope of the straight line; if the TL is strict, then better precalculate all the slopes and store them beforehand
		double c = a.y - a.x*(m);		// intercept of the straight line; if the TL is strict, then better precalculate all the intercepts and store them beforehand
		double aa = m*xx;
		double bb = c;
		double cc = aa+bb;
		ans1 = min( ans1, cc );
	}
	for( int i = 0; i < upper_hull_sz-1; ++i ) {
		if( riBorder && (i == upper_hull_sz-2) ) continue;
		PT a = upper_hull[i], b = upper_hull[i+1];		// straight line passes through points a and b
		double m = (a.y-b.y)/(a.x-b.x);		// slope of the straight line; if the TL is strict, then better precalculate all the slopes and store them beforehand
		double c = a.y - a.x*(m);		// intercept of the straight line; if the TL is strict, then better precalculate all the intercepts and store them beforehand
		double aa = m*xx;
		double bb = c;
		double cc = aa+bb;
		ans2 = max( ans2, cc );
	}
	ans = ans1-ans2;
	return ans;
}

bool Ternary_Search(double val)
{
	double lo = -INF, hi = INF, mid1, mid2;
	leBorder = 0, riBorder = 0;
	if( lower_hull[0].x == lower_hull[1].x ) lo = lower_hull[0].x+val, leBorder = 1;
	if( upper_hull[upper_hull_sz-2].x == upper_hull[upper_hull_sz-1].x ) hi = upper_hull[upper_hull_sz-1].x-val, riBorder = 1;
	if( lo > hi ) return 0;
	for( int i = 0; i < steps; ++i ) {
		mid1 = (lo*2.0 + hi)/3.0;
		mid2 = (lo + 2.0*hi)/3.0;
		double ff1 = func(mid1, val);
		double ff2 = func(mid2, val);
		if( ff1 >= 0 || ff2 >= 0 ) return 1;
		if( ff1 > ff2 ) hi = mid2;
		else lo = mid1;
	}
	if( func(lo, val) >= 0 ) return 1;
	return 0;
}
