const int INF = inf;
int a[123][123];

/// for set s1 and s2 what is maximum matching with minimum cost


int main()
{
    optimize();

    int T;
    scanf ( "%d", &T );
    for ( int tc = 1; tc <= T; tc++ ) {
        int n;
        scanf ( "%d", &n );
        for ( int i = 1; i <= n; i++ ) {
            for ( int j = 1; j <= n; j++ ) {
                scanf( "%d", &a[i][j] );
                a[i][j] *= -1; /// for max cost.
            }
        }
        int m = n;

        vector<int> u (n+1), v (m+1), p (m+1), way (m+1);
        for (int i=1; i<=n; ++i) {
            p[0] = i;
            int j0 = 0;
            vector<int> minv (m+1, INF);
            vector<char> used (m+1, false);
            do {
                used[j0] = true;
                int i0 = p[j0],  delta = INF,  j1;
                for (int j=1; j<=m; ++j)
                    if (!used[j]) {
                        int cur = a[i0][j]-u[i0]-v[j];
                        if (cur < minv[j])
                            minv[j] = cur,  way[j] = j0;
                        if (minv[j] < delta)
                            delta = minv[j],  j1 = j;
                    }
                for (int j=0; j<=m; ++j)
                    if (used[j])
                        u[p[j]] += delta,  v[j] -= delta;
                    else
                        minv[j] -= delta;
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        printf ( "Case %d: %d\n", tc, v[0] );

        /// v[0] is the cost.
        /// -v[0] for min cost
        /// v[0] for max cost

    }

    return 0;
}
