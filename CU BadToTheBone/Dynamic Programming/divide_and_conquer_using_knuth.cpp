const int mx = 5e3+123;
ll dp[mx][mx], a[mx], cost[mx][mx], opt[mx][mx];

int main()
{
    optimize();

    int t;
    cin >> t;
    for ( int tc = 1; tc <= t; tc++ ) {
        int n, k;
        cin >> n >> k;
        for ( int i = 1; i <= n; i++ ) cin >> a[i];

        for ( int i = 1; i <= n; i++ ) {
            cost[i][i] = a[i];
            for ( int j = i+1; j <= n; j++ ) {
                cost[i][j] = cost[i][j-1] | a[j];
            }
        }

        for ( int i = 1; i <= n; i++ ) {
            dp[1][i] = cost[1][i];
            opt[1][i] = 1;
        }

        for ( int i = 1; i <= k; i++ ) opt[i][n+1] = n;

        int pre = -1;
        for ( int i = 2; i <= k; i++ ) {
            for ( int j = n; j >= 1; j-- ) {

                int ml = opt[i-1][j];
                int mr = opt[i][j+1];

                if ( pre > mr ) return 0;
                pre = ml;

                dp[i][j] = 0;
                for ( int k = ml; k <= mr; k++ ) {
                    ll d = dp[i-1][k] + cost[k+1][j];

                    if ( d > dp[i][j] ) {
                        dp[i][j] = d;
                        opt[i][j] = k;
                    }
                }
            }
        }

        cout << dp[k][n] << endl;
    }

    return 0;
}
