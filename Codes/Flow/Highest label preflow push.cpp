/**
Highest Label Preflow Push
Complexity : O(V^2 * sqrt(E))

Fastest max flow implementation

1. Works on directed graph
2. Works on undirected graph
3. Works on multi-edge(directed/undirected) graph
4. Works on self-loop(directed/undirected) graph

Can't find the actual flow.
Can't find the minimum cut sets.

Status: Tested and OK
**/


#include<bits/stdc++.h>
#define optimize() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
using namespace std;

template <class flow_t>	///int/long long;
struct HighestLabelPreflowPush {
    struct Edge {
        int v, rev;
        flow_t cap, tot;
        Edge(int a, flow_t b, int c) : v(a), rev(c), cap(b), tot(b) {}
    };

    const flow_t maxf = numeric_limits<flow_t>::max();
    int ht, S, T, N, H, labelcnt;

    vector<flow_t> exflow;
    vector< vector<Edge> > G;
    vector< vector<int> > hq, gap;
    vector<int> h, cnt;

    HighestLabelPreflowPush(int NN) : exflow(NN), G(NN), hq(NN), gap(NN) {}

    void addEdge(int u, int v, flow_t cap) {
        G[u].emplace_back(v, cap, G[v].size());
        G[v].emplace_back(u, 0, G[u].size() - 1);
    }

    void update(int u, int newh) {
        ++labelcnt;
        if (h[u] != H)
            --cnt[h[u]];
        h[u] = newh;
        if (newh == H)
            return;
        ++cnt[ht = newh];
        gap[newh].push_back(u);
        if (exflow[u] > 0)
            hq[newh].push_back(u);
    }

    void globalRelabel() {
        queue<int> q;
        for (int i = 0; i <= H; i++) hq[i].clear(), gap[i].clear();
        h.assign(H, H);
        cnt.assign(H, 0);
        q.push(T);
        labelcnt = ht = h[T] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (Edge& e : G[u]) {
                if (h[e.v] == H && G[e.v][e.rev].cap) {
                    update(e.v, h[u] + 1);
                    q.push(e.v);
                }
            }
            ht = h[u];
        }
    }

    void push(int u, Edge& e) {
        if (exflow[e.v] == 0)
            hq[h[e.v]].push_back(e.v);
        flow_t df = min(exflow[u], e.cap);
        e.cap -= df;
        G[e.v][e.rev].cap += df;
        exflow[u] -= df;
        exflow[e.v] += df;
    }

    void discharge(int u) {
        int nxth = H;
        if (h[u] == H)
            return;
        for (Edge& e : G[u])
            if (e.cap) {
                if (h[u] == h[e.v] + 1) {
                    push(u, e);
                    if (exflow[u] <= 0)
                        return;
                } else if (nxth > h[e.v] + 1)
                    nxth = h[e.v] + 1;
            }
        if (cnt[h[u]] > 1)
            update(u, nxth);
        else
            for (; ht >= h[u]; gap[ht--].clear()) {
                for (int& j : gap[ht]) update(j, H);
            }
    }

    flow_t maxFlow(int s, int t, int n) {
        S = s, T = t, N = n, H = N + 1;
        fill( exflow.begin(), exflow.end(), 0 );
        exflow[S] = maxf;
        exflow[T] = -maxf;
        globalRelabel();
        for (Edge& e : G[S]) push(S, e);
        for (; ~ht; --ht) {
            while (!hq[ht].empty()) {
                int u = hq[ht].back();
                hq[ht].pop_back();
                discharge(u);
                if (labelcnt > (N << 2))
                    globalRelabel();
            }
        }
        return exflow[T] + maxf;
    }
};


int main() {
    optimize();
    int T;
    cin >> T;
    for( int test = 1; test <= T; ++test ) {
		int N, M, s, t; ///no. of nodes; no. of edges; source; sink;
        cin >> N >> M >> s >> t;
		HighestLabelPreflowPush<int> hlpp(N+2); ///int to long long for flow of long long; total no. of nodes+2(nodes+1 does not work);
		for( int i = 1; i <= M; ++i ) {
			int u, v, w;
			cin >> u >> v >> w;
			hlpp.addEdge(u, v, w);	///For directed graph

			/**
				For undirected graph:
				hlpp.addEdge(u, v, w);
				hlpp.addEdge(v, u, w);
			**/
		}
		cout << hlpp.maxFlow(s, t, N) << endl;	///source; sink; number of nodes;
    }
    return 0;
}
