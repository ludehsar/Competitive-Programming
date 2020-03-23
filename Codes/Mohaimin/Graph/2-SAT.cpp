///2_SAT


///Complexity: O(N)
///https://cp-algorithms.com/graph/2SAT.html
///While practicing, its better to revise the concept of 2SAT from cp-algorithms and steven halim.
/**
	1. p xor q == (p or q) and (not_p or not_q)
	   not_(p xor q) == (not_p or q) and (p or not_q)

	2. For any or relation (p or b) we will add directed edges:-
	   not_p -> b, not_b -> p

	3. The node for x is 2*x. Node for not_x is 2*x+1.

	4. If any node x and its inverse not_x is in same SCC then the problem is not 2-satisfiable. Otherwise it is.
	
	5. To find the actual assignment-
	   any node x will be given true if its component is situated to the left of the component of its inverse not_x- in the topological ordering.
**/

///After making the implication graph, if the graph is undirected, then instead of using the SCC method we can directly use the DSU method to find the strongly connected components which is a little bit simpler, and helps to solve faster in some problems. (in undirected graphs, if two nodes are in same component then they are said to be strongly connected)

int nds; ///no. of nodes (x and not_x). we will use [2,nds] for denoting nodes.
vector<vector<int>> g, gt; ///g is the implication graph. gt is the reverse implication graph
vector<bool> used;
vector<int> order, comp;
vector<bool> assignment;	///contains the solution.

void dfs1(int u)
{
    used[u] = true;
    for (auto v : g[u]) {
        if (!used[v]) dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u, int cl)
{
    comp[u] = cl;
    for (auto v : gt[u]) {
        if (comp[v] == -1) dfs2(v, cl);
    }
}

bool solve_2SAT()
{
    used.assign(nds+1, false);
    for (int i = 2; i <= nds; ++i) {
        if (!used[i]) dfs1(i);
    }

    comp.assign(nds+1, -1);
    for (int i = 0, j = 0; i < nds-1; ++i) {
        int u = order[nds - i - 2];
        if (comp[u] == -1) dfs2(u, j++);
    }

    assignment.assign( (nds+1)/2, false );
    for (int i = 2; i <= nds; i += 2) {
        if (comp[i] == comp[i + 1])
            return false;
        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
}
