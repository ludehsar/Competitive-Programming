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


const int mx = 2e6+123;
int F[mx], a[mx], mask_val[mx], penal[mx];
vi pen[mx];

int main()
{
    optimize();

    int T;
    cin >> T;
    for ( int tc = 1; tc <= T; tc++ ) {
        for ( int i = 0; i <= 2e6; i++ ) {
            pen[i].clear();
            a[i] = F[i] = 0;
        }

        int n, m;
        cin >> n >> m;

        for ( int i = 1; i <= n; i++ ) {
            string p;
            cin >> p >> penal[i];

            int mask = 0;
            for ( int i = 1; i < sz ( p ); i++ ) mask = mask ^ ( 1 << (int)( p[i] - 'A' ) );
            if ( p[0] == '?' ) {
                for ( int i = 0; i < m; i++ ) {
                    mask = mask ^ ( 1 << i );
                }
            }

            mask_val[i] = mask;
            pen[mask].PB ( penal[i] );
            F[mask]++;
            a[mask]++;
        }

        for ( int i = m-1; i >= 0; i-- ) {
            for ( int mask = ( 1 << m )-1; mask >= 0; mask-- ) {
                if ( mask & ( 1 << i ) ) {
                    F[mask^(1<<i)] += F[mask];
                }
            }

        }

        for ( int i = 0; i < ( 1 << m ); i++ ) sort ( all ( pen[i] ) );

        cout << "Case " << tc << ":";
        for ( int i = 1; i <= n; i++ ) {
            int rank = lower_bound( all ( pen[mask_val[i]] ), penal[i] ) - pen[mask_val[i]].begin();
            rank += F[mask_val[i]];
            rank -= a[mask_val[i]];
            rank++;
            cout  << " " << rank;
        }

        cout << endl;

    }


    return 0;
}
















