///*** Linear Diophantine[ax+by=c] one actual solution and solution count between range (x1,x2) & (y1,y2)***
///*** Complexity: O(log N)***
/*
1. Linear Diophantine Equation [ ax+by=c ] will have solution only if [c % gcd(a,b) == 0];
2. The other solutions of [ax+by=c] are for any integer value of k [x + k*(b/gcd(a,b)) , y - k*(a/gcd(a,b))]
3. The largest number that can't be expressed in ax+by form where ( [a,b,x,y all are >=0] and a,b are co-prime) is [ab-a-b].
4. All multiples of gcd(a, b) greater than [lcm(a, n)-a-n] are representable in the form [ax+by] where [a,b,x,y all are >=0]
5. There are exactly [(a-1)*(b-1)/2] values that can't be expressed in ax+by where [a,b,x,y all are >=0]
6. Compare [ax + by = gcd(a,b)] with [ ( a%b )x + by = gcd( a,b )] or [( a - (Floor( a/b ) * b) )x + by = gcd( a,b )] For Recursion.
7. Extended Euclid Algorithm finds the x, y and gcd( a,b ) of Bézout’s lemma [ ax + by = gcd( a,b ) ]
*/
///***important :: this algo will not work if [a==0 || b==0], we will have to compute the result separately, in those case***
struct LinearDiophantineEquation{
  int extendedEuclid(int a,int b,long long &x,long long &y){
    if(!b){
      x=1,y=0;
      return a;
    }
    long long x0,y0;
    int gcd=extendedEuclid(b,a%b,x0,y0);
    x=y0;
    y=x0-(a/b)*y0;
    return gcd;
  }
  bool getOneSolution(int a,int b,int c,long long &x,long long &y,long long &gcd){
    gcd=extendedEuclid(abs(a),abs(b),x,y);
    if(c%gcd)return false;
    x*=(c/gcd);
    y*=(c/gcd);
    if(a<0)x*=-1;
    if(b<0)y*=-1;
    return true;
  }
  void shiftResult(int a,int b,long long &x,long long &y,long long cnt){
    x+=b*cnt;   //this can cause overflow in int
    y-=a*cnt;   //this can cause overflow in int
  }
  int getAllSolution(int a,int b,int c,int xLow,int xHigh,int yLow,int yHigh){
    long long x,y,gcd;
    if(!getOneSolution(a,b,c,x,y,gcd))return 0;
    a/=gcd;
    b/=gcd;
    int sign_a=(a>0)?+1:-1;
    int sign_b=(b>0)?+1:-1;
    shiftResult(a,b,x,y,(xLow-x)/b);
    if(x<xLow)shiftResult(a,b,x,y,sign_b);
    if(x>xHigh)return 0;
    long long lx1=x;
    shiftResult(a,b,x,y,(xHigh-x)/b);
    long long rx1=x;
    shiftResult(a,b,x,y,-(yLow-y)/a);
    if(y<yLow)shiftResult(a,b,x,y,-sign_a);
    if(y>yHigh)return 0;
    long long lx2=x;
    shiftResult(a,b,x,y,-(yHigh-y)/a);
    long long rx2=x;
    if(lx2>rx2)swap(lx2,rx2);
    long long lx=max(lx1,lx2);
    long long rx=min(rx1,rx2);
    if(lx>rx)return 0;
    return (rx-lx)/abs(b) +1;
  }
};
