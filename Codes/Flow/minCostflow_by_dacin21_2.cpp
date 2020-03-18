/**
// Push-Relabel implementation of the cost-scaling algorithm
// Runs in O( <max_flow> * log(V * max_edge_cost)) = O( V^3 * log(V * C))
// Really fast in practice, 3e4 edges are fine.
// Operates on integers, costs are multiplied by N!!
// Works on regular directed graphs.

// Can't operate on doubles. For this, use bellman ford/djikstra method.
//Whether or not it works on undirected or multi-edge or self-loop graphs is yet to be verified.

// To get the actual flow collect all the edges which have (f > 0) - this works just like
   the actual flow finding in normal max flow algorithms;

// Can't find nonMaxflow value upto K. The code is too complex for me to add this function.
   Maybe its not possible at all and you can only do it with the bellmanFord/Djikstra method.

**/



#include<bits/stdc++.h>
using namespace std;

#define optimize() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'

template<typename flow_t = int, typename cost_t = int>	///int/long long; int/long long;
struct mcSFlow{
    struct Edge{
        cost_t c;
        flow_t f;
        int to, rev;
        Edge(int _to, cost_t _c, flow_t _f, int _rev):c(_c), f(_f), to(_to), rev(_rev){}
    };
    static constexpr cost_t INFCOST = numeric_limits<cost_t>::max()/2;	///divide by slightly bigger number if overflow;
    cost_t eps;
    int N, S, T;
    vector<vector<Edge> > G;
    vector<unsigned int> isq, cur;
    vector<flow_t> ex;
    vector<cost_t> h;
    mcSFlow(int _N):eps(0), N(_N), G(_N){}
    void add_edge(int a, int b, cost_t cost, flow_t cap){
		assert(cap>=0);
        assert(a>=0&&a<N&&b>=0&&b<N);
        if(a==b){assert(cost>=0); return;}
        cost*=N;
        eps = max(eps, abs(cost));
        G[a].emplace_back(b, cost, cap, G[b].size());
        G[b].emplace_back(a, -cost, 0, G[a].size()-1);
    }
    void add_flow(Edge& e, flow_t f) {
        Edge &back = G[e.to][e.rev];
        if (!ex[e.to] && f)
            hs[h[e.to]].push_back(e.to);
        e.f -= f; ex[e.to] += f;
        back.f += f; ex[back.to] -= f;
    }
    vector<vector<int> > hs;
    vector<int> co;
    flow_t max_flow() {
        ex.assign(N, 0);
        h.assign(N, 0); hs.resize(2*N);
        co.assign(2*N, 0); cur.assign(N, 0);
        h[S] = N;
        ex[T] = 1;
        co[0] = N-1;
        for(auto &e:G[S]) add_flow(e, e.f);
        if(hs[0].size())
        for (int hi = 0;hi>=0;) {
            int u = hs[hi].back();
            hs[hi].pop_back();
            while (ex[u] > 0) { // discharge u
                if (cur[u] == G[u].size()) {
                    h[u] = 1e9;
                    for(unsigned int i=0;i<G[u].size();++i){
                        auto &e = G[u][i];
                        if (e.f && h[u] > h[e.to]+1){
                            h[u] = h[e.to]+1, cur[u] = i;
                        }
                    }
                    if (++co[h[u]], !--co[hi] && hi < N)
                        for(int i=0;i<N;++i)
                            if (hi < h[i] && h[i] < N){
                                --co[h[i]];
                                h[i] = N + 1;
                            }
                    hi = h[u];
                } else if (G[u][cur[u]].f && h[u] == h[G[u][cur[u]].to]+1)
                    add_flow(G[u][cur[u]], min(ex[u], G[u][cur[u]].f));
                else ++cur[u];
			}
            while (hi>=0 && hs[hi].empty()) --hi;
        }
        return -ex[S];
    }
    void push(Edge &e, flow_t amt){
        if(e.f < amt) amt=e.f;
        e.f-=amt; ex[e.to]+=amt;
        G[e.to][e.rev].f+=amt; ex[G[e.to][e.rev].to]-=amt;
    }
    void relabel(int vertex){
        cost_t newHeight = -INFCOST;
        for(unsigned int i=0;i<G[vertex].size();++i){
            Edge const&e = G[vertex][i];
            if(e.f && newHeight < h[e.to]-e.c){
                newHeight = h[e.to] - e.c;
                cur[vertex] = i;
            }
        }
        h[vertex] = newHeight - eps;
    }
    static constexpr int scale=2;
    pair<flow_t, cost_t> minCostMaxFlow(int _S, int _T){
    	S = _S, T = _T;
        cost_t retCost = 0;
        for(int i=0;i<N;++i)
            for(Edge &e:G[i])
                retCost += e.c*(e.f);
        //find max-flow
        flow_t retFlow = max_flow();
        h.assign(N, 0); ex.assign(N, 0);
        isq.assign(N, 0); cur.assign(N,0);
        queue<int> q;
        for(;eps;eps>>=scale){
            //refine
            fill(cur.begin(), cur.end(), 0);
            for(int i=0;i<N;++i)
                for(auto &e:G[i])
                    if(h[i] + e.c - h[e.to] < 0 && e.f) push(e, e.f);
            for(int i=0;i<N;++i){
                if(ex[i]>0){
                    q.push(i);
                    isq[i]=1;
                }
            }
            // make flow feasible
            while(!q.empty()){
                int u=q.front();q.pop();
                isq[u]=0;
                while(ex[u]>0){
                    if(cur[u] == G[u].size())
                        relabel(u);
                    for(unsigned int &i=cur[u], max_i = G[u].size();i<max_i;++i){
                        Edge &e=G[u][i];
                        if(h[u] + e.c - h[e.to] < 0){
                            push(e, ex[u]);
                            if(ex[e.to]>0 && isq[e.to]==0){
                                q.push(e.to);
                                isq[e.to]=1;
                            }
                            if(ex[u]==0) break;
                        }
                    }
                }
            }
            if(eps>1 && eps>>scale==0){
                eps = 1<<scale;
            }
        }
        for(int i=0;i<N;++i){
            for(Edge &e:G[i]){
                retCost -= e.c*(e.f);
            }
        }
        return make_pair(retFlow, retCost/2/N);
    }
    flow_t getFlow(Edge const &e){
        return G[e.to][e.rev].f;
    }
};


int main()
{
	optimize();
	int T;
	cin >> T;
	for( int test = 1; test <= T; ++test ) {
		int N, M, S, T;	/// Number of nodes; number of edges; source; sink;
		cin >> N >> M >> S >> T;
		mcSFlow<> fl(N+1); ///Add long long, long long if necessary;
		for( int i = 1; i <= M; ++i ) {
			int u, v, c, w; /// node; node; cost; capacity;
			cin >> u >> v >> c >> w;
			fl.add_edge(u, v, c, w);	///Directed graph;
		}
		cout << fl.minCostMaxFlow(S, T).first << " " << fl.minCostMaxFlow(S, T).second;	///flow; cost;
	}
}


















