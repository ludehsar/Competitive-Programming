/**
Dinic algorithm with scaling and not scaling.
Complexity with scaling : O(VE * lg(U)). here, U is the maximum capacity
Complexity without scaling : O((V^2)E)
//////
Complexity in bipartite graph matching: O(E*sqrt(V)).
Complexity in unit graph: O(E*sqrt(V)). (but, Chilli says it is wrong and actual complexity is O(E*min(V^(2/3), E^(1/2))) ).
A unit network is a network in which all the edges have unit capacity, and for any vertex except s and t either incoming or outgoing edge is unique. That's exactly the case with the network we build to solve the maximum matching problem with flows. So, Dinic gives similar performance to hopcroft karp algorithm incase of maximum bipartite matching as it has the same time complexity.
//////
1. Works on directed graph
2. Works on undirected graph
3. Works on multi-edge(directed/undirected) graph
4. Works on self-loop(directed/undirected) graph

Can find the actual flow.
Can find the non-maxflow upto a certain value

//////
Implement it on your own. very easy. just a simple O(n) dfs.

Can find minimum cut sets(A and B).
A contains source itself and the nodes that are reachable from source using non-saturated edges.
B contains sink and the nodes that are not reachable from source using non-saturated edges.
Value of minimum cut capacity is summation of the per_cap of all edges u->v such that u belongs to set A, v belongs to set B.
Value of minimum cut flow is = (summation of the flow of all edges u->v such that u belongs to set A, v belongs to set B) - (summation of the flow of all edges v->u such that v belongs to set B, u belongs to set A)
Value of minimum cut capacity == maxflow.

To find the minimum cut sets(A and B) first find the maxflow. Then, we apply dfs from the source. This dfs will be such that- only 
the nodes of set A will eventually be marked visited. Suppose we have reached in node u, that means u belongs to set A. Now,
If (flow of edge u->v) < (per_cap of edge u->v) then v belongs to set A.
else if(flow of edge u->v) == (per_cap of edge u->v) then v belongs to set B.

To find the minimum cut sets with minimum cardinality, first multiply (E+1) with all the edges. Then add 1 to all the edges. Then run the maxflow algorithm.
//////
**/
#include <bits/stdc++.h>
using namespace std;
#define optimize() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
template <class flow_t> struct Dinic { //int/long long;
  const static bool SCALING = true; // non-scaling = V^2E, Scaling=VElog(U) with higher constant
  long long lim = 1;
  const flow_t INF = numeric_limits<flow_t>::max(); //reduce this a bit to avoid overflow maybe?
  flow_t K;
  bool K2 = false;
  struct edge {
    int to, rev;
    flow_t cap, flow, per_cap;
  };
  int s, t;
  vector<int> level, ptr;
  vector< vector<edge> > adj;
  Dinic(int NN) : s(NN-2), t(NN-1), level(NN), ptr(NN), adj(NN) {}
  void flow_limit( flow_t val ) { //non-maxflow upto K.
    K2 = true;
    K = val;
  }
  void addEdge(int a, int b, flow_t cap, bool isDirected = true) {
    adj[a].push_back({b, (int)adj[b].size(), cap, 0, cap});
    adj[b].push_back({a, (int)adj[a].size() - 1, isDirected ? 0 : cap, 0, isDirected ? 0 : cap});
  }
  bool bfs() {
    queue<int> q({s});
    fill( level.begin(), level.end(), -1 );
    level[s] = 0;
    while (!q.empty() && level[t] == -1) {
      int v = q.front();
      q.pop();
      for (auto e : adj[v]) {
        if (level[e.to] == -1 && e.flow < e.cap && (!SCALING || e.cap - e.flow >= lim)) {
          q.push(e.to);
          level[e.to] = level[v] + 1;
        }
      }
    }
    return level[t] != -1;
  }
  flow_t dfs(int v, flow_t flow) {
    if (v == t || !flow) return flow;
      for (; ptr[v] < adj[v].size(); ptr[v]++) {
        edge &e = adj[v][ptr[v]];
        if (level[e.to] != level[v] + 1) continue;
        if (flow_t pushed = dfs(e.to, min(flow, e.cap - e.flow))) {
          e.flow += pushed;
          adj[e.to][e.rev].flow -= pushed;
          return pushed;
        }
      }
    return 0;
  }
  flow_t max_flow(int source, int sink) {
    s = source, t = sink;
    long long flow = 0;
    for (lim = SCALING ? (1LL << 30) : 1; lim > 0; lim >>= 1) { //Here, lim = SCALING?(U):1 ; Here U is an int/long long strictly greater than the max capacity ;
      while (bfs()) {
        fill( ptr.begin(), ptr.end(), 0 );
        while (flow_t pushed = dfs(s, ((K2==true)?K:INF))) {
          flow += pushed;
          if(K2) {
            K -= pushed;
            if( K == 0 ) break;
          }
        }
        if( K2 && (K == 0) ) break;
      }
    }
    return flow;
  }
  vector<pair<pair<int,int>,long long>> getActualFlow() {
    vector<pair<pair<int,int>, long long>> vec;
    for( int i = 0; i < adj.size(); ++i ) {
      for( int j = 0; j < adj[i].size(); ++j ) {
        if( adj[i][j].flow > 0 ) {
          vec.push_back( make_pair(make_pair(i, adj[i][j].to), adj[i][j].flow) );
        }
      }
    }
    return vec;
  }
};
int main() {
  optimize();
  int T;
  cin >> T;
  for( int test = 1; test <= T; ++test ) {
    int N, M, s, t;  // no. of nodes; no. of edges; source; sink;
    cin >> N >> M >> s >> t;
    Dinic<int> fl(N+1);	//for long long change int to long long; no. of nodes+1;
    for( int i = 1; i <= M; ++i ) {
      int u, v, w;			
      cin >> u >> v >> w;
      fl.addEdge(u, v, w);  //Directed graph;
      //fl.addEdge(u, v, w, false); //Undirected graph;
    }
    //fl.flow_limit(10);  //non-maxflow upto a specific value;
    cout << fl.max_flow(s, t) << endl;
    
    ///Actual flow
    vector<pair<pair<int,int>,long long>> vec = fl.getActualFlow();
    cout << vec.size() << endl;
    for( auto xx : vec ) {
      cout << xx.first.first << " " << xx.first.second << " " << xx.second << endl;  //node; node; flow;
    }
  }
  return 0;
}
