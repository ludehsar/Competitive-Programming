///*** Finding the x that satisfies all the congruence equation***
///*** Complexity: O(N log(N) )***
/*
  basically chinese remainder theorem is solved using extended euclid algorithm.
  the problems can be converted to a diophantine equation of ax+by=c format.
  x=a1(mod n1)
  x=a2(mod n2)
  we can rewrite these equations as follow:
  x=a1+n1*k1
  x=a2+n2*k2
  from the above we can write
  a1+n1*k1 = a2+n2*k2
  or, n1*(-k1) + n2*k2 = a1-a2 [which is a diophantine equation. so the solution will exists if and only if (a1-a2)%gcd(n1,n2)==0]
  [changing the equation we get :: x = a1 + x'*[(a2-a1)/d]*n1 where d is the gcd of n1 and n2, x' is the value we get from extended euclid]
*/
struct ChineseRemainderTheorem{
  long long ans,lcm;
  bool haveSolution;
  ChineseRemainderTheorem(){}
  ChineseRemainderTheorem(vector<long long>&a,vector<long long>&n){
    haveSolution=true;
    ans=a[0];
    lcm=n[0];
    for(int i=1;i<n.size();i++){
      long long x,y;
      long long gcd=extendedEuclid(lcm,n[i],x,y);
      if((a[i]-ans)%gcd){
        haveSolution=false;
        return;
      }
      ans=(ans + ( ( x * ((a[i]-ans )/gcd) ) %(n[i]/gcd) ) * lcm);
      lcm=LCM(lcm,n[i],gcd);
      ans=((ans%lcm)+lcm)%lcm;
    }
    //so ans variable holds the required result that will satisfy all the congruence equations.
  }
  long long extendedEuclid(long long a,long long b,long long &x,long long &y){
    if(!b){
      x=1; y=0;
      return a;
    }
    long long x0,y0;
    long long gcd=extendedEuclid(b,a%b,x0,y0);
    x=y0;
    y=x0-(a/b)*y0;
    return gcd;
  }
  long long LCM(long long x,long long y,long long gcd){
    return (x/gcd)*y;
  }
};
