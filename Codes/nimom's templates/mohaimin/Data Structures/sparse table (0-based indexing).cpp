//1. range sum query (copied from cp-algorithms)
const int MAXN = 1e5+5;
long long arr[MAXN];
const int LOG = log2(MAXN) + 1;
long long sp[MAXN][LOG+1];
int N; //size of arr
void init() { //O(NlogN)
  for( int i = 0; i < N; ++i ) sp[i][0] = arr[i];
    for( int j = 1; j <= LOG; ++j )
      for( int i = 0; i + (1 << j) <= N; ++i )
        sp[i][j] = sp[i][j-1] + sp[i + (1 << (j - 1))][j - 1];
}
long long query( int L, int R )	{ //O(logN)
  long long sum = 0;
  for( int j = LOG; j >= 0; --j ) {
    if((1 << j) <= R - L + 1) {
      sum += sp[L][j];
      L += 1 << j;
    }
  }
  return sum;
}
//2. rmq (copied from cp-algorithms)
const int MAXN = 1e5+5;
long long arr[MAXN];
const int LOG = log2(MAXN) + 1;
long long sp[MAXN][LOG+1];
int prelog[MAXN];
int N;  //size of arr
void init_log() { //O(MAXN)
  prelog[1] = 0;
  for( int i = 2; i < MAXN; ++i ) prelog[i] = prelog[i/2] + 1;
}
void init() {  //O(NlogN)
  for( int i = 0; i < N; ++i ) sp[i][0] = arr[i];
    for( int j = 1; j <= LOG; ++j )
      for( int i = 0; i + (1 << j) <= N; ++i )
        sp[i][j] = min(sp[i][j-1], sp[i + (1 << (j - 1))][j - 1]);
}
long long query(int L, int R) {  //O(1)
  int j = prelog[R - L + 1];
  long long minimum = min(sp[L][j], sp[R - (1 << j) + 1][j]);
  return minimum;
}
//3. 2D rmq
const int MAXN = 1005;
const int MAXM = 1005;
long long arr[MAXN][MAXM];
const int LOGN = log2(MAXN) + 1;
const int LOGM = log2(MAXM) + 1;
long long sp[MAXN][MAXM][LOGN + 1][LOGM + 1];
int prelog[max(MAXN, MAXM)];
int N, M;  //size of arr is N*M
void init_log()	{ //O(MAXN)
  prelog[1] = 0;
  for( int i = 2; i < max(MAXN, MAXM); ++i ) prelog[i] = prelog[i/2] + 1;
}
void init() {  //O(N*M*logN*logM)
  for( int i = 0; i < N; ++i )
    for( int j = 0; j < M; ++j ) sp[i][j][0][0] = arr[i][j];
  for( int k = 1; k <= LOGN; ++k ) {
    for( int i = 0; i + (1 << k) <= N; ++i ) {
      for( int j = 0; j < M; ++j ) {
        sp[i][j][k][0] = min(sp[i][j][k - 1][0] , sp[i + (1 << (k - 1))][j][k - 1][0]);
      }
    }
  }
  for( int l = 1; l <= LOGM; ++l ) {
    for( int k = 0; k <= LOGN; ++k ) {
      for( int i = 0; i + (1 << k) <= N; ++i ) {
        for( int j = 0; j + (1 << l) <= M; ++j ) {
          sp[i][j][k][l] = min(sp[i][j][k][l - 1] , sp[i][j + (1 << (l - 1))][k][l - 1]);
        }
      }
    }
  }
}
long long query( int r1, int c1, int r2, int c2 ) { //O(1)
  int a = prelog[(r2 - r1) + 1];
  int b = prelog[(c2 - c1) + 1];
  return min(min(sp[r1][c1][a][b], sp[r2 - (1 << a) + 1][c1][a][b]), min(sp[r1][c2 - (1 << b) + 1][a][b], sp[r2 - (1 << a) + 1][c2 - (1 << b) + 1][a][b]));
}
