///The implementation for euler circuit and euler path is exactly same.
///The implementation for directed and undirected graph is exactly same.
/**
  1. Path traversing all the edges just once starting from one node and ending at that node is euler circuit.
  2. If the path does not end at the source node then that path is euler path.
**/
1. euler circuit/euler path for undirected graph
/**
  1. The graph must be a single component. So, you have to check it.
  2. All the nodes should have even degree. So, check it. But if just 2 nodes have odd degree then there will an eulerian path only. Choose any of these 2 nodes as source node in that case.
  3. If node u has a self loop then deg[u] += 2; i.e. the degree of node u is increased by 2.
**/
2. Euler circuit/euler path for directed graph
/**
  1. The graph -if converted to undirected must be a single component. So, you have to check it.
  2. in-degree and out-degree of all nodes should be equal. So, check it. But if just 2 nodes have unequal in-degree and out-degree then there will an eulerian path only if and only if one these node(source node to be exact) have out-degree==1+in-degree and the other have in degree==1+out-degree. Choose any of these 2 nodes as source node in that case.
  3. If node u has a self loop then in-degree[u]++; and out-degree[u]++;
**/
vector<pii> gvec[10005]; ///adjacency list; gvec[u] contains pairs (v, id) where v is node and id is the edge no.
bool bad[10005]; ///size of this array is the number of edges
vector<int> circuit; ///contains the path
void eularcircuit(int src) {
  stack<int> curr_path;
  circuit.clear();
  if(gvec[src].empty())return;
  int curr_v = src;
  while (1) {
    if (!gvec[curr_v].empty()) {
      auto it=gvec[curr_v].back();
      int next_v = it.F, id = it.S;
      gvec[curr_v].pop_back();
      if( bad[id] ) continue;
      bad[id] = 1;
      curr_path.push(curr_v);
      curr_v = next_v;
    }
    else {
      circuit.push_back(curr_v);
      if(curr_path.empty()) break;
      curr_v = curr_path.top();
      curr_path.pop();
    }
  }
  reverse(circuit.begin(),circuit.end());
}
int main() {
  int n, m; /// no. of nodes, no. of edges;
  cin >> n >> m;
  for( int i = 0; i < 10005; ++i ) gvec[i].clear();
  memset( bad, 0, sizeof(bad) );
  circuit.clear();
  for( int i = 0; i < m; ++i ) {
    int u, v;
    cin >> u >> v;
    gvec[u].PB( MP(v, i) ); ///Directed graph
    /** Undirected graph
      gvec[u].PB( MP(v, i) );
      gvec[v].PB( MP(u, i) );
    **/
  }
  eularcircuit( source );
}
