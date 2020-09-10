/*
   n rows/equations, m+1 columns, m variables
   calculates determinant, rank and ans[] -> value for variables
   returns {0, 1, INF} -> number of solutions
   gives truely row echelon form.(sort of Identity matrixish, but the independent column/variables may have non-zero values at the upper rows.)
*/
/*
///For "gaussian elimination modulo version"-
  1. add big mod function to the top.
  2. just do all the calculations in mod(determinant too. but not rank).
  3. I have add comments to the code to help with "step- 2".
  4. change all doubles to long long as all the calculations are done in long long. omit EPS.
*/
///Complexity: O(min(n, m) * n * m)
const double EPS = 1e-9;
#define INF 100000000
int Rank;  //Rank means number of non-zero rows in row-echelon form
double Det;

int gauss( vector<vector<double>> a, vector<double> &ans ) {
  int n = (int)a.size(), m = (int)a[0].size()-1;
  ans.clear(); ans.resize(m);
  vector<int> where(m, -1);
  Det = 1.0, Rank = 0;
  for(int col = 0, row = 0; col < m && row < n; ++col) {
    int sel = row;
    for(int i = row+1; i < n; ++i)
      if(abs(a[i][col]) > abs(a[sel][col])) sel = i;
    if(abs(a[sel][col]) < EPS) { Det = 0.0; continue; } ///For modulo version: if(!a[sel][col])
    for(int j = 0; j <= m; ++j) swap(a[sel][j], a[row][j]);
    if(row != sel) Det = -Det; ///For modulo version: add mod? (idk, i made this up. munim vai kept this line as it is. So change only if WA)
    Det *= a[row][col]; ///For modulo version: mod mul
    where[col] = row;

    double s = (1.0 / a[row][col]); ///For modulo version: mod inverse
    for(int j = 0; j <= m; ++j) a[row][j] *= s; ///For modulo version: mod mul
    for(int i = 0; i < n; ++i) if (i != row && abs(a[i][col]) > EPS) { ///For modulo version: if (i != row && a[i][col] > 0)
      double t = a[i][col];
      for(int j = 0; j <= m; ++j) a[i][j] -= a[row][j] * t; ///For modulo version: mod mul and mod sub
    }
    ++row, ++Rank;
  }

  for(int i = 0; i < m; ++i) ans[i] = (where[i] == -1) ? 0.0 : a[where[i]][m];
  for(int i = Rank; i < n; ++i) if(abs(a[i][m]) > EPS) return 0; ///For modulo version: if(a[i][m])
  for(int i = 0; i < m; ++i) if(where[i] == -1) return INF;
  return 1;
}
