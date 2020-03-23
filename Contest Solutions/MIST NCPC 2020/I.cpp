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
#define MOD 1000000007

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

const int mx = 1e5+123;
int n;
vi adj[mx];
vector<char> color;
vector<int> parent;
int cycle_start, cycle_end;

bool dfs(int v, int p) {
    color[v] = 1;
    for (int u : adj[v]) {
        if (color[u] == 0 ) {
            parent[u] = v;
            if (dfs(u, v))
                return true;
        } else if ( u != p && color[u] == 1) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
    }
    color[v] = 2;
    return false;
}

int find_cycle()
{
    color.assign(n+10, 0);
    parent.assign(n+10, -1);
    cycle_start = -1;

    for (int v = 1; v <= n; v++) {
        if (color[v] == 0 && dfs(v, 0))
            break;
    }

    vector<int> cycle;
    cycle.push_back(cycle_start);
    for (int v = cycle_end; v != cycle_start; v = parent[v])
        cycle.push_back(v);
    cycle.push_back(cycle_start);
    reverse(cycle.begin(), cycle.end());


    return sz ( cycle ) - 1;
}

int fact[mx], invFact[mx];
int nCr ( int n, int k )
{
    return modMul( fact[n], modMul( invFact[n-k], invFact[k] ) );
}


int main()
{
    optimize();

    fact[0] = 1;
    invFact[0] = 1;
    for ( int i = 1; i <= 1e5; i++ ) {
        fact[i] = modMul( fact[i-1], i );
        invFact[i] = modInverse( fact[i] );
    }

    int T;
    cin >> T;
    for ( int tc = 1; tc <= T; tc++ ) {
        for ( int i = 0; i <= 1e5; i++ ) {
            adj[i].clear();
        }

        map <pii, bool > vis;
        bool lop = 0, b = 0;

        int k;
        cin >> n >> k;
        for ( int i = 1; i <= n; i++ ) {
            int u, v;
            cin >> u >> v;
            adj[u].PB ( v );
            adj[v].PB ( u );

            if ( u == v ) lop = 1;
            if ( vis[{u,v}] ) b = 1;
            vis[{u,v}] = vis[{v,u}] = 1;
        }

        int x;
        if ( lop ) x = 1;
        else if ( b ) x = 2;
        else x = find_cycle();

        ll ans = modDiv( 1, nCr ( n, k ) );
        ans = modAdd( ans, modMul( k, modMul( modDiv( n-k, n  ), modMul( modDiv( x, n ), modDiv( nCr ( k, k-1 ), nCr ( n-1, k-1 ) ) ) ) ) );
        ans = modSub( 1, ans );

        cout << ans << endl;
    }


    return 0;
}
















