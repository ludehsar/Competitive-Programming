/// Works on directed and undirected graphs;
/// Works on directed + undirected graphs. i.e. mixed graphs;
/// Whether or not it works on multi-edge or self-loop graphs is yet to be verified;
/// can find non-maxflow-mincost, can find actual mincost-flow;
/// Operates on integers. to use it for doubles just change the data-type from long long/int to double accordingly. Its easy.
/// Complexity: it varies somewhere between O(V^3 * E) and O(V^2 * E^2). But the complexity maybe lower due to using spfa algorithm.

namespace mcmf{
  const int MAX = 1000020; /// max(MAX_NODES, MAX_EDGES*cc)+20, cc = 2 if directed, cc = 4 if undirected;
  const long long INF = 1LL << 60; /// increase/decrease this value as per problem necessity; be careful to avoid overflow;
  long long cap[MAX], flow[MAX], cost[MAX], dis[MAX];
  int n, m, s, t, Q[MAX*10], adj[MAX], adj_from[MAX], link[MAX], last[MAX], from[MAX], visited[MAX];
  long long K;
  bool K2 = false;
  void init(int nodes){
    K2 = false; K = 0;
    m = 0, n = nodes;
    for (int i = 0; i <= n; i++) last[i] = -1;
  }
  void addEdge(int u, int v, long long c, long long w){
    adj[m] = v, adj_from[m] = u, cap[m] = c, flow[m] = 0, cost[m] = +w, link[m] = last[u], last[u] = m++;
    adj[m] = u, adj_from[m] = v, cap[m] = 0, flow[m] = 0, cost[m] = -w, link[m] = last[v], last[v] = m++;
  }
  void flow_limit( ll K_ ) { /// non-maxflow upto K.
    K2 = true;
    K = K_;
  }
  bool spfa(){
    int i, j, x, f = 0, l = 0;
    for (i = 0; i <= n; i++) visited[i] = 0, dis[i] = INF;
    dis[s] = 0, Q[l++] = s;
    while (f < l){
      i = Q[f++];
      for (j = last[i]; j != -1; j = link[j]){
        if (flow[j] < cap[j]){
          x = adj[j];
          if (dis[x] > dis[i] + cost[j]){
            dis[x] = dis[i] + cost[j], from[x] = j;
            if (!visited[x]){
              visited[x] = 1;
              if (f && rand() & 7) Q[--f] = x;
              else Q[l++] = x;
            }
          }
        }
      }
      visited[i] = 0;
    }
    return (dis[t] != INF);
  }
  pair <long long, long long> MinCostFlow(int source, int sink){
    s = source, t = sink;
    int i, j;
    long long mincost = 0, maxflow = 0;
    while (1){
      long long aug = INF;
      if (K2 == true) {assert( maxflow <= K );
        if( maxflow == K ) break;
        aug = K - maxflow;
      }
      if( !spfa() ) break;
      for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i]){
        aug = min(aug, cap[j] - flow[j]);
      }
      for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i]){
        flow[j] += aug, flow[j ^ 1] -= aug;
      }
      maxflow += aug, mincost += aug * dis[t];
    }
    return make_pair(mincost, maxflow);
  }
  vector<pair<pair<int,int>,pair<long long, long long>>> getActual_mincost_and_Flow() {
    vector<pair<pair<int,int>,pair<long long, long long>>> vec;
    for( int i = 0; i < m; ++i ) {
      if( flow[i] > 0 ) {
        vec.PB( MP( MP(adj_from[i], adj[i]), MP(flow[i]*cost[i], flow[i]) ) );
      }
    }
    return vec;
  }
}

int main() {
  int T;
  cin >> T;
  for( int test = 1; test <= T; ++test ) {
    int N, M, s, t; /// no. of nodes; no. of edges; source; sink;
    cin >> N >> M >> s >> t;
    mcmf::init(N);
    for( int i = 1; i <= M; ++i ) {
      int u, v, cap, cost; ///node, node, capacity, cost;
      cin >> u >> v >> cap >> cost;
      ///Directed:
      mcmf::addEdge( u, v, cap, cost );
      /** //Undirected:
      mcmf::addEdge( u, v, cap, cost );
      mcmf::addEdge( v, u, cap, cost );
      **/
    }
    ///mcmf::flow_limit(10); //non-maxflow upto a specific value;
    pair<long long, long long> ans = mcmf::MinCostFlow(s, t);
    cout << ans.first << " " << ans.second << endl;	/// mincost, flow;

    ///Actual mincost and minflow
    vector<pair<pair<int,int>,pair<long long,long long>>> vec = mcmf::getActual_mincost_and_Flow();
    cout << vec.size() << endl;
    for( auto xx : vec ) {
      cout << xx.F.F << " " << xx.F.S << " " << xx.S.F << " " << xx.S.S << endl; ///node, node, mincost, flow;
    }
  }
}
