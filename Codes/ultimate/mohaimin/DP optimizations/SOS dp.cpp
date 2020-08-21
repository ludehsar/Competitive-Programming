///O(N*2^N)
int dp[1<<N];
for(int i = 0; i<(1<<N); ++i) dp[i] = A[i];
for(int i = 0;i < N; ++i) {
  for(int mask = 0; mask < (1<<N); ++mask) {
    if(mask & (1<<i)) dp[mask] += dp[mask^(1<<i)];  ///checkBit, ResetBit;
  }
}

///O(3^N) (Very much Easier to modify)
int dp[1<<N];
// iterate over all the masks
for (int mask = 0; mask < (1<<N); mask++) {
  dp[mask] = A[0];
  // iterate over all the subsets of the mask
  for(int i = mask; i > 0; i = (i-1) & mask) {
    dp[mask] += A[i];
  }
}
