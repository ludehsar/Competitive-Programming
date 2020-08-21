///***Double Hashing***
///***Complexity: O(N)
struct simpleHash{
  vector<long long>p;
  vector<long long>h;
  long long base, len, mod = (long long)1e9+7;
  simpleHash(){}
  simpleHash(string &str, long long b){
    base = b; len = str.size();  //0 base index str
    p.resize(len,1);
    h.resize(len+1,0);
    for(int i=1; i<len; i++) p[i] = ( p[i-1]*base )%mod;
    for(int i=1; i<=len; i++) h[i] = (h[i-1]*base + (str[i-1]-'a' + 3) )%mod;
  }
  long long rangeHash(int l,int r){   //l and r inclusive and also 0 based
    return ( h[r+1]-( (h[l] * p[r-l+1]) % mod )+ mod) % mod;
  }
};
struct doubleHashing{
  simpleHash h1,h2;
  doubleHashing(string &str){
    h1 = simpleHash(str, 149);
    h2 = simpleHash(str, 223);
  }
  long long rangeHash(int l,int r){   //l and r inclusive and also 0 based
    return ( h1.rangeHash(l,r)<<32LL) ^ h2.rangeHash(l,r);
  }
};
