/// the nodes must be 0-based! be aware!
///Complexity: O(n^3), where n = max(row, col); row represents left part, col represents right part;
template <class T>
pair<T, vector<pair<int, int>>> hungarian_method(const vector<vector<T>> &mat, bool minimize=true){
  if (!mat.size()) return {(T)0, {}};
  T i, j, a, b, d, n, m, row = mat.size(), col = mat[0].size();
  for (i = 0; i < row; i++) assert((int)mat[i].size() == col);
  n = row, m = max(n, col);
  vector <T> way(m + 1, 0), match(m + 1, 0), visited(m + 1, 0);
  vector <T> U(m + 1, 0), V(m + 1, 0), P(m + 1, 0), minv(m + 1, 0);
  for (i = 1; i <= n; i++){
    b = 0, P[0] = i;
    for (j = 0; j <= m; j++) minv[j] = numeric_limits<T>::max(), visited[j] = 0;
    do{
      T w = numeric_limits<T>::max();
      a = P[b], d = 0, visited[b] = 1;
      for (j = 1; j <= m; j++){
        if (!visited[j]){
          T v = 0;
          if (a >= 1 && a <= row && j >= 1 && j <= col) {
            v = (minimize ? mat[a - 1][j - 1] : -mat[a - 1][j - 1]);
          }
          T r = v - U[a] - V[j];
          if (r < minv[j]) minv[j] = r, way[j] = b;
          if (minv[j] < w) w = minv[j], d = j;
        }
      }
      for (j = 0, b = d; j <= m; j++){
        if (visited[j]) U[P[j]] += w, V[j] -= w;
        else minv[j] -= w;
      }
    } while (P[b]);
    do{
      d = way[b];
      P[b] = P[d], b = d;
    } while (b);
  }
  T res = minimize ? -V[0] : V[0];
  vector <pair<int, int>> matched_pairs;
  for (j = 1; j <= m; j++) match[P[j]] = j;
  for (i = 1; i <= m; i++){
    j = match[i];
    if (i >= 1 && i <= row && j >= 1 && j <= col){
      matched_pairs.push_back({i - 1, j - 1});
    }
  }
  assert((int)matched_pairs.size() == min(row, col));
  return {res, matched_pairs};
}

int main() {
  int n, m; /// rows -> no. of left nodes; col -> no. of right nodes;
  vector<vector<ll>> mat( n, vector<ll>(m) );
  /**
  Here mat[i][j] contains cost of i->j edge where node i belongs to left part, node j belongs to right part;
  if there is no edge from node i to node j then:
    1. For maximum weighted matching, set mat[i][j] = -inf/-infLL;
    2. For minimum weighted matching, set mat[i][j] = inf/infLL;
    (increase/decrease the value of inf/infLL to avoid overflow)
  **/
  /// minimum weighted matching:
  pair<ll, vector<pair<int,int>>> hung = hungarian_method( mat, true ); /// minimum weighted matching, vector of matched pair nodes;
  /** // maximum weighted matching:
  pair<ll, vector<pair<int,int>>> hung = hungarian_method( mat, false ); /// maximum weighted matching, vector of matched pair nodes;
  */
}
