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


const int mx = 1e5+123;
vi t[3*mx];
int d[mx];

void init ( int id, int b, int e )
{
    if ( b == e ) {
        t[id].clear();
        t[id].PB ( d[b] );
        return;
    }

    int mid = ( b + e ) >> 1;

    init ( id*2, b, mid );
    init ( id*2+1, mid+1, e );

    t[id].clear();
    merge( all ( t[id*2] ), all ( t[id*2+1] ), back_inserter( t[id] ) );
}


int ask ( int id, int b, int e, int i, int j, int A, int B )
{
    if ( b > j || e < i ) return 0;
    if ( b >= i && e <= j ) {
        int l = upper_bound( all ( t[id] ), A-1 ) - t[id].begin();
        int r = upper_bound( all ( t[id] ), B ) - t[id].begin();

        return r-l;
    }

    int mid = ( b + e ) >> 1;

    int q1 = ask ( id*2, b, mid, i, j, A, B );
    int q2 = ask ( id*2+1, mid+1, e, i, j, A, B );

    return q1 + q2;
}


vector<int> sort_cyclic_shifts(string const& s)
{
    int n = s.size();
    const int alphabet = 256;

    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }

    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}


vector<int> suffix_array_construction(string s)
{
    s += "$";
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

vector<int> lcp_construction(string const& s, vector<int> const& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[p[i]] = i;

    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}


int st[mx][25], a[mx];

void preprocess ( int n )
{
    for ( int i = 1; i <= n; i++ ) st[i][0] = a[i];

    for ( int i = 1; i <= 24; i++ ) {
        for ( int j = 1; j + ( 1 << (i-1) ) <= n; j++ ) {
            st[j][i] = min ( st[j][i-1], st[j+(1<<(i-1))][i-1] );
        }
    }
}

int query ( int l, int r )
{
    int lg = log2( r - l + 1 );
    return min ( st[l][lg], st[r-(1<<lg)+1][lg] );
}
int pid[mx];

int main()
{
    optimize();

    int T;
    cin >> T;

    for ( int  tc = 1; tc <= T; tc++ ) {

        string s;
        cin >> s;

        vector<int> p = suffix_array_construction( s );
        vector<int> lcp = lcp_construction( s, p );


        int cnt = 0;
        for ( auto u : p ) {
            d[++cnt] = u+1;
            pid[u+1] = cnt;
        }
        cnt = 0;
        for ( auto u : lcp ) a[++cnt] = u;

        int n = sz ( s );

        init ( 1, 1, n );
        preprocess( n-1 );

        int q;
        cin >> q;
        while ( q-- ) {
            int A, B, C, D;
            cin >> A >> B >> C >> D;

            int b = 1, e = pid[C];
            int len = D - C + 1;

            int l = pid[C], r = pid[C];
            while ( b <= e ) {
                int mid = ( b + e ) >> 1;

                int k1 = mid, k2 = pid[C];
                if ( k1 > k2 ) swap( k1, k2 );

                if ( ( k1 <= k2-1 && query( k1, k2-1 ) >= len ) || k1 == k2 ) {
                    if ( k1 < k2 ) l = min ( l, mid );
                    e = mid - 1;
                }
                else b = mid + 1;
            }

            b = pid[C], e = n;
            while ( b <= e ) {
                int mid = ( b + e ) >> 1;

                int k1 = mid, k2 = pid[C];
                if ( k1 > k2 ) swap( k1, k2 );

                if ( ( k1 <= k2-1 && query( k1, k2-1 ) >= len ) || k1 == k2 ) {
                    if ( k1 < k2 ) r = max ( r, mid );
                    b = mid + 1;
                }
                else e = mid - 1;
            }

            cout << ask ( 1, 1, n, l, r, A, B-len+1 ) << endl;
        }
    }

    return 0;
}
