/**
Push relabel with gap heuristic and highest labeling
Complexity : O(V^2 * sqrt(E))

2nd fastest max flow implementation

1. Works on directed graph
2. Works on undirected graph
3. Works on multi-edge(directed/undirected) graph
4. Works on self-loop(directed/undirected) graph

Can find the actual flow.

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

Status: Tested and OK
**/


#include <bits/stdc++.h>
using namespace std;

#define optimize() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'


template<typename flow_t = long long>
struct PushRelabel {
	struct Edge {
		int to, rev;
		flow_t f, c, per_cap;
	};
	vector<vector<Edge> > g;
	vector<flow_t> ec;
	vector<Edge*> cur;
	vector<vector<int> > hs;
	vector<int> H;
	PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}
	void add_edge(int s, int t, flow_t cap, flow_t rcap=0) {
		if (s == t) return;
		Edge a = {t, (int)g[t].size(), 0, cap, cap};
		Edge b = {s, (int)g[s].size(), 0, rcap, rcap};
		g[s].push_back(a);
		g[t].push_back(b);
	}
	void add_flow(Edge& e, flow_t f) {
		Edge &back = g[e.to][e.rev];
		if (!ec[e.to] && f)
			hs[H[e.to]].push_back(e.to);
		e.f += f; e.c -= f;
		ec[e.to] += f;
		back.f -= f; back.c += f;
		ec[back.to] -= f;
	}
	flow_t max_flow(int s, int t) {
		int v = g.size();
		H[s] = v;
		ec[t] = 1;
		vector<int> co(2*v);
		co[0] = v-1;
		for(int i=0;i<v;++i) cur[i] = g[i].data();
		for(auto &e:g[s]) add_flow(e, e.c);
		if(hs[0].size())
		for (int hi = 0;hi>=0;) {
			int u = hs[hi].back();
			hs[hi].pop_back();
			while (ec[u] > 0) // discharge u
				if (cur[u] == g[u].data() + g[u].size()) {
					H[u] = 1e9;
					for(auto &e:g[u])
						if (e.c && H[u] > H[e.to]+1)
							H[u] = H[e.to]+1, cur[u] = &e;
						if (++co[H[u]], !--co[hi] && hi < v)
						for(int i=0;i<v;++i)
							if (hi < H[i] && H[i] < v){
								--co[H[i]];
								H[i] = v + 1;
							}
					hi = H[u];
				} else if (cur[u]->c && H[u] == H[cur[u]->to]+1)
					add_flow(*cur[u], min(ec[u], cur[u]->c));
				else ++cur[u];
			while (hi>=0 && hs[hi].empty()) --hi;
		}
		return -ec[s];
	}
	vector<pair<pair<int,int>,long long>> getActualFlow()
    	{
    		vector<pair<pair<int,int>, long long>> vec;
    		for( int i = 0; i < g.size(); ++i ) {
			for( int j = 0; j < g[i].size(); ++j ) {
				if( g[i][j].f > 0 ) {
					vec.push_back( make_pair(make_pair(i, g[i][j].to), g[i][j].f) );
				}
			}
    		}
    		return vec;
    	}
};


int main()
{
	optimize();
	int T;	///no. of test cases;
	cin >> T;
	for( int test = 1; test <= T; ++test ) {
		int N, M, s, t;	///no. of nodes; no. of edges; source; sink;
		cin >> N >> M >> s >> t;
		PushRelabel<> fl(N+1);	///total no. of nodes is N;
		int u, v, w;
		for (int i = 1; i <= M; ++i) {
			cin >> u >> v >> w;
			fl.add_edge(u, v, w); /// Directed graph
			///fl.add_edge(u, v, w, w); /// unDirected graph
		}
		cout << "Case " << test << ":" << endl;
		cout << fl.max_flow(s, t) << endl;	///value of maxFlow;
		vector<pair<pair<int,int>,long long>> vec = fl.getActualFlow();		///gets actual flow;
		for( auto xx : vec ) {
			cout << xx.first.first << " " << xx.first.second << " " << xx.second << endl;	///node; node; flow;
		}
	}
	return 0;
}
