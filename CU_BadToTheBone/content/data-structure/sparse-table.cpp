int st[MAXN][K];

void preprocess() {
  for (int i = 1; i <= N; i++) st[i][0] = array[i];
  for (int j = 1; j <= K; j++) {
    for (int i = 1; i + (1 << j) <= N; i++) {
        st[i][j] = min(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
    }
  }
}

int getMinimum(int L, int R) {
  int j = log2(R - L + 1);
  return min(st[L][j], st[R - (1 << j) + 1][j]);
}
