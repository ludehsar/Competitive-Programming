///O(NlogN)
///Doubles are never used as in FFT. Always long long is used(modulo or not).

#define MOD 1000000007

#define OR 0
#define AND 1
#define XOR 2
struct FWHT {
  void walsh_transform(vector<ll> &p, bool inv, int flag) {
    int n = p.size(); assert((n&(n-1))==0);
    for (int len=1; 2*len<=n; len <<= 1) {
      for (int i = 0; i < n; i += len+len){
        for (int j = 0; j < len; j++) {  ///Don't forget to include p[i+j] = (p[i+j]+MOD)%MOD, p[i+len+j] = (p[i+len+j]+MOD)%MOD at the end of this for loop(inside of course) when required.
          ll u = p[i+j], v = p[i+len+j];
          if( (flag == XOR) ) p[i+j]=u+v, p[i+len+j]=u-v;
          if( (flag == AND) && !inv ) p[i+j]=v, p[i+len+j]=u+v;
          if( (flag == OR) && !inv ) p[i+j]=u+v, p[i+len+j]=u;
          if( (flag == AND) && inv ) p[i+j]= -u+v, p[i+len+j]=u;
          if( (flag == OR) && inv ) p[i+j]=v, p[i+len+j]=u-v;
        }
      }
    }
    if(inv && (flag == XOR)) for(int i=0;i<n;i++) p[i]/=n; ///Don't forget modular inverse n when required
  }
  /// For i = 0 to n - 1, j = 0 to n - 1
  /// v[i flag j] += a[i] * b[j]
  vector<ll> convo(vector<ll> &a, vector<ll> &b, int flag = XOR) {
    int n = 1, sz = max(a.size(), b.size());
    while(n<sz) n*=2;
    a.resize(n); b.resize(n); vector<ll>res(n, 0);
    walsh_transform(a, 0, flag); walsh_transform(b, 0, flag);
    for(int i=0;i<n;i++)  res[i] = a[i] * b[i]; /// Don't forget modular multiplication when required.
    walsh_transform(res, 1, flag);
    return res;
  }
  ///compute A^k where A?A == A convolution A
  vector<ll> pow(vector<ll> &A, ll k, int flag = XOR) {
    int n = 1, sz = A.size();
    while(n<sz) n *= 2;
    A.resize(n);
    walsh_transform(A, 0, flag);
    for(int i=0; i<n; i++) A[i]=expo(A[i], k, MOD); ///MOD = infLL if there is no modulo required.(trix, modern problems require modern solutions.)
    walsh_transform(A, 1, flag);
    return A;
  }
}fwht;

int main() {
  vector<ll> vec(6);
  vector<ll> temp = vec;
  vector<ll> store1 = fwht.convo(temp, temp, XOR); ///size of store1 will always be a power of 2.
  temp = vec;
  vector<ll> store2 = fwht.pow(temp, 4, XOR); ///size of store2 will always be a power of 2.
}
