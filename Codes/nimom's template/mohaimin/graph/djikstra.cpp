///O((V+E)logV)
///Works on negative edges(a bit slow) but not negative cycle
const int MAXN = 1e5+5;
vi adjlist[MAXN];
int dist[MAXN];
void djikstra( int source ) {
  for( int i = 0; i < MAXN; ++i ) dist[i] = inf;
  dist[source] = 0;
  priority_queue< pii, vector<pii>, greater<pii> > pq;
  pq.push(MP(0, source));
  while (!pq.empty()) {
    pii Front = pq.top(); pq.pop();
    int d = Front.first, u = Front.second;
    if (d > dist[u]) continue;
    for (int j = 0; j < adjlist[u].size(); j++) {
      pii v = adjlist[u][j];
      if (dist[u] + v.second < dist[v.first]) {
        dist[v.first] = dist[u] + v.second;
        pq.push(MP(dist[v.first], v.first));
      }
    }
  }
}
