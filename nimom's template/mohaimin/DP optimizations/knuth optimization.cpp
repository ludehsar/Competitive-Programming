/// *** Very easy. You should be able to implement it on your own without looking at the implementation below even for a single moment;

/// Original recurrence: dp[i][j] = min(dp[i][k] + dp[k][j]) + C[i][j] for i < k < j ( *** dp[i][k-1]+dp[k+1][j] is also possible; dp[i][k]+dp[k+1][j] is also possible; max instead of min is also possible )
/// Sufficient condition: opt[i][j-1] <= opt[i][j] <= opt[i+1][j] where opt[i][j] = smallest k that gives optimal answer
/// 1 <= i < j <= n;
/// *** 1-based indexing
/// Original Complexity: O(n^3), Optimized Complexity: O(n^2)
/// Again, knuth optimization can be applied if it satisfies the following two conditions:
    1. Quadrangle inequality: C[a][c]+C[b][d] <= C[a][d]+C[b][c], a <= b <= c <= d
    2. Monotonicity: C[b][c] <= C[a][d], a <= b <= c <= d
/// To eliminate the possibility of overflow reduce the value of infLL;
/// The implementation below is for min. for max modify the code slightly.

int n;
int dp[500][500];
int C[500][500]; /// precompute C function.
int opt[500][500];

int main() {
  for( int i = 1; i <= n; ++i ) {
    dp[i][i] = C[i][i];
    opt[i][i] = i;
  }
  for( int len = 2; len <= n; ++len ) {
    for( int i = 1, j = len; j <= n; ++i, ++j ) {
      pair<ll, int> best = MP(infLL, -1); ///take -infLL for max;
      for( int k = opt[i][j-1]; k <= opt[i+1][j]; ++k ) {
        ///take < for max; take dp[i][k]+dp[k][j] if required;
        if( best.F > dp[i][k-1]+dp[k+1][j]+C[i][j] ) best = MP( dp[i][k-1]+dp[k+1][j]+C[i][j], k );
      }
      dp[i][j] = best.F;
      opt[i][j] = best.S;
    }
  }
  cout << dp[1][n] << endl;
}
