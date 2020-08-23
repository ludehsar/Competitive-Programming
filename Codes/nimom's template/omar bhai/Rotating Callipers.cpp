///***Complexity: O(N)
struct RotatingCalipers{
  long double res=1e18;
  int len;
  /*this is just a variation of rotating calipers finding the minimum distance of two parallel line in which the polygon can pass through*/
  RotatingCalipers(vector<pair<int,int> >&hull){ //convex hull.
    len=hull.size();
    for(int i=0,j=i+1;i<len;i++){
      pair<int,int>&p1=hull[i];
      pair<int,int>&p2=hull[(i+1)%len];
      while(area(p1, p2, hull[j%len]) < area(p1, p2, hull[(j+1)%len]))j+=1;
      res=min(res, dist(p1, p2, hull[j%len]));
    }
  }
  //Cartesian Distance betweet point p1 & p2
  typedef pair<long double , long double > pld;
  long double dist(pld p1,pld p2){
    long double xDist=p1.first-p2.first;
    long double yDist=p1.second-p2.second;
    return sqrtl((xDist*xDist)+(yDist*yDist));
  }
  typedef pair<long long ,long long > pll;
  //returns area*2.0 enclosed by p1 ,p2 ,p3 points
  long long area(pll p1, pll p2, pll p3){
    return llabs(p1.first*p2.second + p2.first*p3.second + p3.first*p1.second
       -p1.second*p2.first-p2.second*p3.first-p3.second*p1.first);
  }
  //distance from p3 to line going through p1 & p2
  long double dist(pld p1, pld p2, pld p3){
    long double up=(p2.second-p1.second)*p3.first
              -(p2.first-p1.first)*p3.second
              +p2.first*p1.second
              -p1.first*p2.second;
    long double down=sqrtl(
          (p2.second-p1.second)*(p2.second-p1.second)
          +(p2.first-p1.first)*(p2.first-p1.first));
    return fabsl(up/down);
  }
};
