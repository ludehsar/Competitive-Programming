const int mx = 1e3+123;
long long dp[mx][mx], c[mx];
int opt[mx][mx];

int main()
{
    optimize();

    ll m, n;
    while ( cin >> m >> n ) {
        mem ( dp, 0 );
        c[n+1] = m;

        for ( int i = 1; i <= n; i++ ) cin >> c[i];

        for ( int i = 0; i <= n+1; i++ ) {
            for ( int l = 0; l+i <= n+1; l++ ) {
                int r = l + i;

                if ( i < 2 ) {
                    dp[l][r] = 0;
                    opt[l][r] = l;
                    continue;
                }

                int ml = opt[l][r-1];
                int mr = opt[l+1][r];

                dp[l][r] = inf;
                for ( int k = ml; k <= mr; k++ ) {
                    int d = dp[l][k] + dp[k][r] + c[r] - c[l];
                    if ( dp[l][r] > d ) {
                        dp[l][r] = d;
                        opt[l][r] = k;
                    }
                }
            }
        }

        cout << dp[0][n+1] << endl;
    }

    return 0;
}
