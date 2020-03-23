///   ***   ---   |||         In the name of ALLAH        |||   ---   ***   ///



#include<bits/stdc++.h>
using namespace std;


typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef pair<int,int> pii;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef vector<pii> vii;
typedef vector<pll> vll;
typedef double dl;

#define endl '\n'
#define PB push_back
#define F first
#define S second
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()
#define sz(x) (int)x.size()

const double PI = acos(-1);
const double eps = 1e-9;
const int inf = 2000000000;
const ll infLL = 9000000000000000000;
#define MOD 998244353

#define mem(a,b) memset(a, b, sizeof(a) )
#define sqr(a) ((a) * (a))

#define optimize() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define fraction() cout.unsetf(ios::floatfield); cout.precision(10); cout.setf(ios::fixed,ios::floatfield);
#define file() freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);

#define dbg(args...) do {cerr << #args << " : "; faltu(args); } while(0)
void faltu () {            cerr << endl;}
template < typename T, typename ... hello>void faltu( T arg, const hello &... rest) {cerr << arg << ' ';faltu(rest...);}

ll gcd ( ll a, ll b ) { return __gcd ( a, b ); }
ll lcm ( ll a, ll b ) { return a * ( b / gcd ( a, b ) ); }

inline void normal(ll &a) { a %= MOD; (a < 0) && (a += MOD); }
inline ll modMul(ll a, ll b) { a %= MOD, b %= MOD; normal(a), normal(b); return (a*b)%MOD; }
inline ll modAdd(ll a, ll b) { a %= MOD, b %= MOD; normal(a), normal(b); return (a+b)%MOD; }
inline ll modSub(ll a, ll b) { a %= MOD, b %= MOD; normal(a), normal(b); a -= b; normal(a); return a; }
inline ll modPow(ll b, ll p) { ll r = 1; while(p) { if(p&1) r = modMul(r, b); b = modMul(b, b); p >>= 1; } return r; }
inline ll modInverse(ll a) { return modPow(a, MOD-2); }
inline ll modDiv(ll a, ll b) { return modMul(a, modInverse(b)); }

int getK ( int m )
{
    for ( int i = 30; i >= 0; i-- ) {
        if ( (m-1) % ( 1 << i ) == 0 ) return i;
    }
}

int generator (int p) {
    vector<int> fact;
    int phi = p-1,  n = phi;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (int res=2; res<=p; ++res) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= (int)modPow( res, phi / fact[i]) != 1;
        if (ok)  return res;
    }
    return -1;
}

const int mod = MOD;
const int K = getK ( mod );
const int root = modPow( generator( mod ), ( mod-1 ) / ( 1 << K ) );
const int root_1 = modInverse( root );
const int root_pw = 1 << K;


void fft(vector<int> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }

    if (invert) {
        int n_1 = modInverse(n);
        for (int & x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] = modMul( fa[i], fb[i] );
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = fa[i];
    }
    return result;
}

const int mx = 2e5+123;
ll fact[mx], invFact[mx], minPow[mx], nPow[mx], cat[mx];

ll nCr ( ll n, ll k )
{
    return modMul( fact[n], modMul( invFact[n-k], invFact[k] ) );
}

int main()
{
    optimize();

    fact[0] = 1;
    minPow[0] = 1;
    invFact[0] = 1;
    cat[0] = 1;

    for ( int i = 1; i <= 2e5; i++ ) {
        fact[i] = modMul ( i, fact[i-1] );
        invFact[i] = modInverse( fact[i] );
        minPow[i] = minPow[i-1] * ( -1 );
    }

    for ( int i = 1; i <= 1e5; i++ ) cat[i] = modMul( modInverse( i+1 ), nCr ( 2LL*i, i ) );

    int T;
    cin >> T;
    for ( int tc = 1; tc <= T; tc++ ) {
        int n, k;
        cin >> n >> k;

        vi a, b;
        for ( int i = 0; i <= n; i++ ) a.PB ( modMul( minPow[i], invFact[i] ) );
        for ( int i = 0; i <= n; i++ ) b.PB ( modMul( modPow( i, n ), invFact[i] ) );

        vi res = multiply( a, b );

        ll ans = 0;
        for ( int i = 1; i <= k; i++ ) {
            ans ^= ( modMul( cat[n], modMul( fact[i], res[i] ) ) );
        }

        cout << "Case " << tc << ": " << ans << endl;
    }

    return 0;
}
















