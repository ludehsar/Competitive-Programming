///*** Complexity: O( sqrt(N) )***
long long SNOD(long long n=10){
  long long res=0;
  long long len=sqrtl(n);
  for(int i=1;i<=len;i++)res+=(n/i)-i;    //finding the ordered pair like a<b and a*b<n
  res*=2LL;   //converting pair count to single value
  res+=len;   //adding the equal values like (1,1), (2,2)..
  return res;
}
