/// Here l, r is range and p is optimal solution
struct node {
    int l, r, p;
    node(){}
    node ( int _l, int _r, int _p ) : l (_l), r (_r), p (_p) {

    }
};

node que[mx];

int dp[mx], n, c[mx][mx], a[mx];


/// This function  calculates the cost of (i, j).
int calc ( int j, int i )
{
    return c[j][i];
}


/// This function compares if i is better ans than j for k
bool cmp ( int i, int j, int k )
{
    int v1 = dp[i] + calc ( i, k ), v2 = dp[j] + calc ( j, k );
    return ( v1 <= v2 );
}


/// This function finds the lowest position where i is optimal solution in node cur
int find ( node cur, int i )
{
    int l = cur.l, r = cur.r+1;
    while ( l < r ) {
        int mid = ( l + r ) >> 1;
        if ( cmp ( i, cur.p, mid ) ) r = mid;
        else l = mid+1;
    }

    return r;
}


void solve ()
{
    int s = 1, t = 1;
    dp[0] = 0;
    que[1] = node ( 1, n, 0 ); /// Initializing optimal value of all index as 0.

    for ( int i = 1; i <= n; i++ ) {
        while ( s < t && que[s].r < i ) s++; /// Deleting ranges from front until we get the range where i index lies
        dp[i] = dp[que[s].p] + calc(que[s].p, i ); /// calculation dp[i]

        if ( cmp ( i, que[t].p, n ) ) { /// Checking if i is better than the current optimal value of last range
            while ( s <= t && cmp ( i, que[t].p, que[t].l ) ) t--; /// Deleting all range from back of deque where i is better.
            if ( s > t ) que[++t] = node ( i+1, n, i ); /// Creating new range when deque is empty.
            else {
                int pos = find( que[t], i ); /// Finding lowest position where i is optimal solution.
                que[t].r = pos-1;
                que[++t] = node ( pos, n, i ); /// Creating new range.
            }
        }
    }
}


int main()
{

    cin >> n;
    for ( int i = 1; i <= n; i++ ) cin >> a[i];

    for ( int i = 1; i <= n; i++ ) {
        for ( int j = i+1; j <= n; j++ ) {
            cin >> c[i][j];
        }
    }

    solve();
    cout << dp[n] << endl;

    return 0;
}
