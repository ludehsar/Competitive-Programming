// calculates 32 times faster for modulo 2
/*
   n rows/equations, m+1 columns, m variables
   calculates determinant, rank and ans[] -> value for variables
   returns {0, 1, INF} -> number of solutions
   gives truely row echelon form.(sort of Identity matrixish, but the independent column/variables may have non-zero values at the upper rows.)
   Complexity: O(min(n, m) * n * m / 32)
   It's actually O(min(n, m) * n * MAX / 32) because of the implementation since C++ bitset needs to be of constant size
*/

const double EPS = 1e-9;
#define INF 100000000
#define MAX 105
int Rank; //Rank means number of non-zero rows in row echelon form

int Det;
int gauss(vector < bitset<MAX> > a, bitset<MAX> &ans, int n, int m) { // number of variables must be defined!
  ans.reset(); //reset all bits;
  vector<int> where(m, -1);
  Det = 1, Rank = 0;
  for(int col = 0, row = 0; col < m && row < n; ++col) {
    int sel = row;
    for(int i = row; i < n; ++i) if(a[i][col]) { sel = i; break; }
    if(!a[sel][col]) { Det = 0; continue; }
    swap(a[sel], a[row]);
    if(row != sel) Det = -Det; ///add mod? (idk, i made this up. munim vai kept this line as it is. So change only if WA)
    Det &= a[row][col];
    where[col] = row;

    for(int i = 0; i < n; ++i) if (i != row && a[i][col] > 0) a[i] ^= a[row];
    ++row, ++Rank;
  }

  for(int i = 0; i < m; ++i) ans[i] = (where[i] == -1) ? 0 : a[where[i]][m];
  for(int i = Rank; i < n; ++i) if(a[i][m]) return 0;
  for(int i = 0; i < m; ++i) if(where[i] == -1) return INF;
  return 1;
}
