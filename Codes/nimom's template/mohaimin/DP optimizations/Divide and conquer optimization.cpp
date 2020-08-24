/// Original Recurrence: dp[i][j] = min(dp[i-1][k] + C[k][j]) for k < j ( *** C[k+1][j] instead of C[k][j] is also possible; max instead of min is also possible )
/// Sufficient condition: opt[i][j] <= opt[i][j+1] where opt[i][j] = smallest k that gives optimal answer for dp[i][j]
/// 1 <= i <= n, 1 <= j <= m
/// Again, divide and conquer optimization can be applied if it satisfies the following condition: (approved by cgy4ever)
    1. Quadrangle inequality: C[a][c]+C[b][d] <= C[a][d]+C[b][c], a <= b <= c <= d
/// Original complexity: O(n*m^2), Optimized complexity: O(n*m*lg(m))
/// ** 1-based indexing.
/// the implementation is for min. for max modify the code slightly.
/// to eliminate possibility of overflow reduce the value of infLL

long long C(int i, int j);	/// precompute C function beforehand;
ll dp[MAXN][MAXM];	///See if you can optimize memory by declaring dp[2][MAXM];

void compute(int idx, int l, int r, int optl, int optr) {
  if (l > r) return;
  int mid = (l + r) >> 1;
  pair<long long, int> best = {infLL, -1};	/// take -infLL for max answer.
  for (int k = optl; k <= min(mid-1, optr); k++) {
	/// take < for max answer; take C(k+1, mid) if required;
	if( best.F > dp[idx-1][k] + C(k, mid) ) best = MP(dp[idx-1][k] + C(k, mid), k);	/// watch out for possible dp[2][MAXM] memory optimization!
  }
  dp[idx][mid] = best.first;
  int opt = best.second;
  compute(idx, l, mid - 1, optl, opt);
  compute(idx, mid + 1, r, opt, optr);
}

int main() {
  int n, m;
  dp[0][0] = 0;
  for( int i = 1; i <= m; ++i ) dp[0][i] = infLL;	///take -infLL for max answer;
  for( int i = 1; i <= n; ++i ) compute( i, i, m, i-1, m ); /// apparently compute( i, 1, m, 0, m ) also works, i don't know why.
  cout << dp[n][m] << endl;
}
