const int mx = 5e3+123;
int n, num[mx], dp[mx], c[mx][mx], a[mx];

/// Here l, r is range and p is optimal solution
struct node {
    int l, r, p;
    node(){}
    node ( int _l, int _r, int _p ) : l (_l), r (_r), p (_p) {

    }
};

node que[mx];

/// This function compares if i is better ans than j for k
bool cmp ( int i, int j, int k )
{
    int v1 = dp[i] + c[i+1][k], v2 = dp[j] + c[j+1][k];
    if ( v1 == v2 ) return num[i] <= num[j];
    return ( v1 < v2 );
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

int solve (  int mid )
{
    int s = 1, t = 1;
    dp[0] = num[0] = 0;
    que[1] = node ( 1, n, 0 ); /// Initilaising optimal value of all index as 0.

    for ( int i = 1; i <= n; i++ ) {
        while ( s < t && que[s].r < i ) s++; /// Deleting ranges from front until we get the range where i index lies
        dp[i] = dp[que[s].p] + c[que[s].p+1][i] + mid; /// calculating dp[i] with slop mid
        num[i] = num[que[s].p] + 1; /// calculating num[i].

        if ( cmp ( i, que[t].p, n ) ) { /// Checking if i is better than the current optimal value of last range
            while ( s <= t && cmp ( i, que[t].p, que[t].l ) ) t--; /// Deleting all range from back of queue where i is better.
            if ( s > t ) que[++t] = node ( i+1, n, i ); /// Creating new range when deque is empty.
            else {
                int pos = find( que[t], i ); /// Finding lowest position where i is optimal solution.
                que[t].r = pos-1;
                que[++t] = node ( pos, n, i ); /// Creating new range.
            }
        }
    }

    return num[n];
}

int main()
{
    int k;
    cin >> n >> k;
    for ( int i = 1; i <= n; i++ ) cin >> a[i];

    for ( int i = 1; i <= n; i++ ) {
        for ( int j = i; j <= n; j++ ) cin >> c[i][j];
    }

    int l = 0, r = 3e7+123, ans = 0;

    /// Binary search on slop
    while ( l <= r ) {
        int mid = ( l + r ) >> 1;
        if ( solve ( mid ) <= k ) {
            ans = dp[n] - ( k * mid ); /// As mid is added in dp[n], k times.
            r = mid-1;
        }

        else l = mid+1;
    }

    cout << ans << endl;


    return 0;
}
