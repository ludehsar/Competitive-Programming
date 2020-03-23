///The implementation for euler circuit and euler path is exactly same.
//http://www.graph-magics.com/articles/euler.php

/**
	1. Path traversing all the edges just once starting from one node and ending at that node is euler circuit.
	2. If the path does not end at the source node then that path is euler path.
**/

///euler circuit/euler path for undirected graph
/**
	1. The graph must be a single component. So, you have to check it.
	2. All the nodes should have even degree. So, check it. But if just 2 nodes have odd degree
	then there will an eulerian path only. Choose any of these 2 nodes as source node in that case.
**/
multiset<int> gset[10005];	//gset contains the graph info as adjacency list
vector<int> circuit;	//contains the path
void eularcircuit_U(int src)
{
	stack<int> curr_path;

	circuit.clear();
	if(gset[src].empty())return;
	int curr_v = src;

	while (1) {
		if (!gset[curr_v].empty()) {
			curr_path.push(curr_v);
			auto it=gset[curr_v].begin();
			int next_v = *it;
			gset[curr_v].erase(gset[curr_v].lower_bound(next_v));
			gset[next_v].erase(gset[next_v].lower_bound(curr_v));
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

/// Euler circuit/euler path for directed graph
/**
	1. The graph -if converted to undirected must be a single component. So, you have to check it.
	2. in-degree and out-degree of all nodes should be equal. So, check it. But if just 2 nodes have unequal in-degree
	and out-degree then there will an eulerian path only if and only if one these node(source node to be exact) have
	out-degree==1+in-degree and the other have in-degree==1+out-degree. Choose any of these
	2 nodes as source node in that case.
**/
vector<int> gvec[10005]; //gvec contains the graph info as adjacency list
vector<int> circuit;	// contains the path
void eularcircuit_D(int src)
{
	stack<int> curr_path;

	circuit.clear();
	if(gvec[src].empty())return;
	int curr_v = src;

	while (1) {
		if (!gvec[curr_v].empty()) {
			curr_path.push(curr_v);
			int next_v = gvec[curr_v].back();
			gvec[curr_v].pop_back();
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
