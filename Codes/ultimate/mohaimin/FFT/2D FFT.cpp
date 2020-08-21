/**
Rule of thumb for precision issues- (by Errichto)
Well written FFT has an error that depends mainly on the magnitude of numbers in the answer, so it works if the resulting polynomial doesn't have numbers bigger than 10^15 for doubles and 10^18 for long doubles. You can measure the error by finding max of abs(x−llround(x)) over all x in the answer. If it's smaller than 0.2, you're good and rounding will be fine.
**/
///No need to clear anything at the beginning of a test case
/// 2D FFT of a 2D polynomial ~ O(N*M*(lgN + lgM))
/// product of two 2D polynomials ~ O(N*M*(lgN + lgM))
struct FFT_2D {
  struct node {
    double x,y;
    node() {}
    node(double a, double b): x(a), y(b) {}
    node operator + (const node &a) const {return node(this->x+a.x,this->y+a.y);}
    node operator - (const node a) const {return node(this->x-a.x,this->y-a.y);}
    node operator * (const node a) const {return node(this->x*a.x-this->y*a.y,this->x*a.y+a.x*this->y);}
  };

  int M[2];
  vector<vector<node>> A, B;
  vector<node> w[2][2];
  vector<int>rev[2];
  long double pi;
  FFT_2D() {
    pi = 3.1415926535897932384;
  }
  void init(int n, int m) {
    M[0] = 1, M[1] = 1;
    while(M[0] < n) M[0] <<= 1;
    M[0] <<= 1;
    while(M[1] < m) M[1] <<= 1;
    M[1] <<= 1;
    A.resize(M[0], vector<node>(M[1]));
    B.resize(M[0], vector<node>(M[1]));
    for( int z = 0; z < 2; ++z ) {
      w[z][0].resize(M[z]);
      w[z][1].resize(M[z]);
      rev[z].resize(M[z]);
      for (int i=0; i<M[z]; i++) {
	int j=i,y=0;
	for (int x=1; x<M[z]; x<<=1,j>>=1) (y<<=1)+=j&1;
	rev[z][i]=y;
      }
      for (int i=0; i<M[z]; i++) {
	w[z][0][i] = node( cos(2*pi*i/M[z]),sin(2*pi*i/M[z]) );
	w[z][1][i] = node( cos(2*pi*i/M[z]),-sin(2*pi*i/M[z]) );
      }
    }
  }
  void ftransform_2D( vector<vector<node>> &A, int p ) {
    for( int z = 0; z < M[0]; z++ ) {
      for (int i=0; i<M[1]; i++)
        if (i<rev[1][i])
	  swap(A[z][i],A[z][rev[1][i]]);
      for (int i=1; i<M[1]; i<<=1)
	for (int j=0,t=M[1]/(i<<1); j<M[1]; j+=i<<1)
	  for (int k=0,l=0; k<i; k++,l+=t) {
	    node x=A[z][i+j+k]*w[1][p][l];
	    node y=A[z][j+k];
	    A[z][j+k]=y+x;
	    A[z][j+k+i]=y-x;
	  }
      if (p)
	for (int i=0; i<M[1]; i++)
	  A[z][i].x/=M[1], A[z][i].y/=M[1];
    }
    for( int z = 0; z < M[1]; z++ ) {
      for (int i=0; i<M[0]; i++)
	if (i<rev[0][i])
	  swap(A[i][z],A[rev[0][i]][z]);
      for (int i=1; i<M[0]; i<<=1)
	for (int j=0,t=M[0]/(i<<1); j<M[0]; j+=i<<1)
	  for (int k=0,l=0; k<i; k++,l+=t) {
	    node x=w[0][p][l]*A[i+j+k][z];
	    node y=A[j+k][z];
	    A[j+k][z]=y+x;
	    A[j+k+i][z]=y-x;
	  }
      if (p)
	for (int i=0; i<M[0]; i++)
	  A[i][z].x/=M[0];
    }
  }
  ///2degree polynomial P * 2degree polynomial Q = 2degree polynomial res
  ///Degree of P is x1,x2; Degree of Q is y1, y2; Degree of res is x1+y1, x2+y2;
  void multiply_2D( vector<vector<long long>> &P, vector<vector<long long>> &Q, vector<vector<long long>> &res ) {
    init( max(P.size(), Q.size()), max(P[0].size(), Q[0].size()) );
    for( int i = 0; i < M[0]; i++ )
      for( int j = 0; j < M[1]; j++ )
	A[i][j].x = A[i][j].y = B[i][j].x = B[i][j].y = 0;
    for( int i = 0; i < P.size(); i++ )
      for( int j = 0; j < P[i].size(); j++ )
	A[i][j].x = P[i][j];
    for( int i = 0; i < Q.size(); i++ )
      for( int j = 0; j < Q[i].size(); j++ )
	B[i][j].x = Q[i][j];
    ftransform_2D(A, 0);
    ftransform_2D(B, 0);
    for( int i = 0; i < M[0]; i++ )
      for( int j = 0; j < M[1]; j++ )
        A[i][j] = A[i][j]*B[i][j];
    ftransform_2D(A, 1);
    res.resize(M[0], vector<ll>(M[1]));
    for( int i = 0; i < M[0]; i++ )
      for( int j = 0; j < M[1]; j++ )
        res[i][j] = round(A[i][j].x);
  }
}fft_2D;

int main() {
  /// a*b = c
  /// Degree of a = (n1-1, n2-1), Degree of b = (m1-1, m2-1), Degree of c = (n1+m1-2, n2+m2-2);
  vector<vector<ll>> a, b, c;
  int n1, n2, m1, m2;
  cin >> n1 >> n2 >> m1 >> m2;
  a.resize(n1, vector<ll>(n2)), b.resize(m1, vector<ll>(m2)), c.resize(n1+m1-1, vector<ll>(n2+m2-1));
  for( int i = 0; i < n1; ++i )
    for( int j = 0; j < n2; ++j ) cin >> a[i][j];
  for( int i = 0; i < m1; ++i )
    for( int j = 0; j < m2; ++j ) cin >> b[i][j];
  fft_2D.multiply(a, b, c);  /// product of a and b is kept in c;
}

