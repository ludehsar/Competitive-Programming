struct matrix {
  matrix() {}
  vector<vector<ll>> mat;
  matrix(int n, int m) : mat(n, vector<ll>(m)) {}
};
matrix operator * (matrix a, matrix b) { /// pass by reference if TLE
  int n = a.mat.size();
  int m = a.mat[0].size();
  assert(b.mat.size() == m);
  int k = b.mat[0].size();
  matrix ans (n, k);
  for (int i=0; i<n; i++)
    for (int j=0; j<k; j++)
      for (int l=0; l<m; l++)
        ans.mat[i][j] = (ans.mat[i][j] + a.mat[i][l]*b.mat[l][j])%MOD;
  return ans;
}
matrix power( matrix b, ll p ) { /// pass by reference if TLE
  matrix res = I, x = b;
  while(p) {
    if ( p&1LL ) res = res*x;
    x = x*x;
    p >>= 1LL;
  }
  return res;
}
