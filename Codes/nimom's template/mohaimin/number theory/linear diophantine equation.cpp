///*** Linear Diophantine -> ax+by=c.
/// finds one actual solution and solution count between range [xLow, xHigh] & [yLow, yHigh]***
///*** Complexity: O(log N)***
/**
1. Linear Diophantine Equation (ax+by=c)  will have solution only if (c%gcd(a,b) == 0);
2. The other solutions of (ax+by=c) are for any integer value of k ( x + k*(b/gcd(a,b)) , y - k*(a/gcd(a,b)) )
3. Chicken Nugget Theorem:
   1. if(a > 0, b > 0, x >= 0, y >= 0, gcd(a, b) == 1) then the greatest integer that can't be written in ax+by form is ab-a-b. Every integer greater than ab-a-b can be represented in ax+by form. There may be some numbers lesser than ab-a-b that can be expressed in ax+by form.
   2. if(a > 0, b > 0, x >= 0, y >= 0, gcd(a, b) == 1) then there are exactly ((a-1)*(b-1))/2 positive integers which cannot be expressed in ax+by form.
   3. if(a > 0, b > 0, x > 0, y > 0, gcd(a, b) > 1) then all the multiples of gcd(a, b) greater than lcm(a, b)-a-b are representable in ax+by form. i.e. lcm(a, b)-a-b is the highest multiple of gcd(a, b) which can't be expressed in ax+by form.
**/
///***important :: this algo will not work if (a==0 || b==0), we will have to compute the result separately in those case***
struct LinearDiophantineEquation{
  /// returns gcd(a, b); finds any x, y such that ax + by = gcd(a,b)
  ll extendedEuclid(ll a, ll b, ll &x, ll &y){ ///Range: ll (according to anachor)
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
  ///check if solution exists, if yes then finds one solution and store them in x and y
  bool getOneSolution(ll a, ll b, ll c, ll &x, ll &y, ll &gcd){
    gcd = extendedEuclid(abs(a), abs(b), x, y);
    if( c%gcd ) return false;
    x *= ( c/gcd );
    y *= ( c/gcd );
    if( a<0 ) x *= -1;
    if( b<0 ) y *= -1;
    return true;
  }
  void shiftResult(ll a, ll b, ll &x, ll &y, ll cnt){
    x += b*cnt;
    y -= a*cnt;
  }
  ///gets the number of solutions between range [xLow, xHigh] & [yLow, yHigh]
  ll getAllSolution(ll a, ll b, ll c, ll xLow, ll xHigh, ll yLow, ll yHigh){
    ll x, y, gcd;
    if( !getOneSolution(a, b, c, x, y, gcd) ) return 0;
    a /= gcd;
    b /= gcd;
    int sign_a = (a>0)?+1:-1;
    int sign_b = (b>0)?+1:-1;
    shiftResult(a, b, x, y, (xLow-x)/b);
    if(x < xLow) shiftResult(a, b, x, y, sign_b);
    if(x > xHigh) return 0;
    ll lx1 = x;
    shiftResult(a, b, x, y, (xHigh-x)/b);
    ll rx1 = x;
    shiftResult(a, b, x, y, -(yLow-y)/a);
    if(y < yLow) shiftResult(a, b, x, y, -sign_a);
    if(y > yHigh) return 0;
    ll lx2 = x;
    shiftResult(a, b, x, y, -(yHigh-y)/a);
    ll rx2 = x;
    if(lx2 > rx2) swap(lx2, rx2);
    ll lx = max(lx1, lx2);
    ll rx = min(rx1, rx2);
    if(lx > rx) return 0;
    return (rx-lx)/abs(b) +1;
  }
};
